#!/usr/bin/env python3
"""
Xiangqi Historical PGN Dataset Processor & PST Generator (Zero-Dependency Pure Python)

Scans 58,000+ master games from the CCPD dataset, tracks piece movements and square frequencies,
and generates Piece-Square Tables (PST) compatible with the Koi chess engine.

Usage:
    python3 scripts/build_pst_tables.py --dataset-dir Dataset --output-dir output
"""

import os
import sys
import glob
import time
import json
import argparse
import multiprocessing as mp
from typing import List, Dict, Any, Tuple, Optional, Set

# Add scripts directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from xiangqi_board import XiangqiBoard
from frequency_tracker import FrequencyTracker, PHASES, PIECE_TYPES
from pst_generator import PSTGenerator
import exporters

def load_invalid_game_paths(audit_file: str, dataset_dir: Optional[str] = None) -> Set[str]:
    """Loads paths of games flagged with transcription/illegal move errors in the audit JSON report."""
    if not audit_file or not os.path.exists(audit_file):
        return set()

    with open(audit_file, "r", encoding="utf-8") as f:
        audit_data = json.load(f)

    invalid_paths: Set[str] = set()
    errors = []
    audit_dataset_dir = ""

    if isinstance(audit_data, dict):
        errors = audit_data.get("errors", [])
        audit_dataset_dir = audit_data.get("datasetDir", "")
    elif isinstance(audit_data, list):
        errors = audit_data

    for err in errors:
        raw_file = err.get("file", "") if isinstance(err, dict) else (err if isinstance(err, str) else "")
        if not raw_file:
            continue
        invalid_paths.add(raw_file)
        invalid_paths.add(os.path.normpath(raw_file))
        invalid_paths.add(os.path.abspath(raw_file))
        invalid_paths.add(os.path.realpath(raw_file))
        if audit_dataset_dir:
            try:
                invalid_paths.add(os.path.relpath(raw_file, audit_dataset_dir))
            except ValueError:
                pass
        if dataset_dir:
            try:
                invalid_paths.add(os.path.relpath(raw_file, dataset_dir))
            except ValueError:
                pass

    return invalid_paths


def is_file_invalid(filepath: str, invalid_paths: Set[str], dataset_dir: Optional[str] = None) -> bool:
    """Checks if a game file path matches any invalid game recorded in the audit."""
    if not invalid_paths:
        return False
    if filepath in invalid_paths:
        return True
    if os.path.normpath(filepath) in invalid_paths:
        return True
    if os.path.abspath(filepath) in invalid_paths:
        return True
    if os.path.realpath(filepath) in invalid_paths:
        return True
    if dataset_dir:
        try:
            if os.path.relpath(filepath, dataset_dir) in invalid_paths:
                return True
        except ValueError:
            pass
    return False


def parse_game_file(filepath: str, tracker: FrequencyTracker) -> bool:
    """Parses a single PGN game file and records frequencies."""
    content = ""
    for enc in ["big5", "cp950", "gb18030", "utf-8"]:
        try:
            with open(filepath, "r", encoding=enc, errors="ignore") as f:
                content = f.read()
            if content:
                break
        except Exception:
            continue

    if not content:
        return False

    board = XiangqiBoard()
    lines = content.split("\n")
    result_str = "*"
    
    # Result weights
    red_weight = 1.0
    black_weight = 1.0

    move_lines = []
    for line in lines:
        line = line.strip()
        if not line:
            continue
        if line.startswith("[Result"):
            if "\"" in line:
                result_str = line.split("\"")[1].strip()
        elif line.startswith("[FEN"):
            if "\"" in line:
                board.set_fen(line.split("\"")[1])
        elif not line.startswith("["):
            move_lines.append(line)

    if tracker.weight_outcomes:
        if result_str == "1-0":
            red_weight, black_weight = 1.0, 0.0
        elif result_str == "0-1":
            red_weight, black_weight = 0.0, 1.0
        elif result_str in ["1/2-1/2", "0.5-0.5", "draw"]:
            red_weight, black_weight = 0.5, 0.5

    # Process moves
    move_count = 0
    full_move = 1

    for line in move_lines:
        if "." in line:
            parts = line.split(".", 1)[1].strip().split()
        else:
            parts = line.strip().split()

        # Handle Red move
        if len(parts) >= 1 and parts[0] not in ["1-0", "0-1", "1/2-1/2", "*"]:
            parsed = board.parse_move(parts[0], is_red=True)
            if parsed:
                piece, src, dst, cap = parsed
                if tracker.mode in ["destination", "blended"]:
                    w = red_weight if tracker.weight_outcomes else 1.0
                    w_factor = 0.7 if tracker.mode == "blended" else 1.0
                    tracker.record_move(piece.type, "w", dst, full_move, weight=w * w_factor)

                board.apply_move(piece, src, dst, cap)
                move_count += 1

                if tracker.mode in ["activated_occupancy", "all_occupancy", "blended"]:
                    w_factor = 0.3 if tracker.mode == "blended" else 1.0
                    tracker.record_occupancy(list(board.pieces.values()), full_move, red_weight * w_factor, black_weight * w_factor)
            else:
                return False

        # Handle Black move
        if len(parts) >= 2 and parts[1] not in ["1-0", "0-1", "1/2-1/2", "*"]:
            parsed = board.parse_move(parts[1], is_red=False)
            if parsed:
                piece, src, dst, cap = parsed
                if tracker.mode in ["destination", "blended"]:
                    w = black_weight if tracker.weight_outcomes else 1.0
                    w_factor = 0.7 if tracker.mode == "blended" else 1.0
                    tracker.record_move(piece.type, "b", dst, full_move, weight=w * w_factor)

                board.apply_move(piece, src, dst, cap)
                move_count += 1

                if tracker.mode in ["activated_occupancy", "all_occupancy", "blended"]:
                    w_factor = 0.3 if tracker.mode == "blended" else 1.0
                    tracker.record_occupancy(list(board.pieces.values()), full_move, red_weight * w_factor, black_weight * w_factor)
            else:
                return False

        full_move += 1

    tracker.total_games += 1
    tracker.total_plies += move_count
    return True


def worker_task(file_chunk: List[str], mode: str, weight_outcomes: bool, symmetrize: bool) -> FrequencyTracker:
    """Worker process that accumulates stats for a chunk of PGN files."""
    tracker = FrequencyTracker(mode=mode, weight_outcomes=weight_outcomes, symmetrize=symmetrize)
    for f in file_chunk:
        parse_game_file(f, tracker)
    return tracker


def main():
    parser = argparse.ArgumentParser(description="Generate Koi Piece-Square Tables (PST) from Xiangqi PGN dataset.")
    parser.add_argument("--dataset-dir", type=str, default="Dataset", help="Directory containing PGN dataset files.")
    parser.add_argument("--output-dir", type=str, default="output", help="Directory to save generated tables.")
    parser.add_argument("--mode", type=str, default="destination", choices=["destination", "activated_occupancy", "all_occupancy", "blended"],
                        help="Frequency tracking mode: 'destination' (recommended, target squares only), 'activated_occupancy' (unmoved pieces ignored), 'all_occupancy', 'blended'.")
    parser.add_argument("--method", type=str, default="log_zscore", choices=["log_zscore", "minmax"],
                        help="PST statistical scaling method.")
    parser.add_argument("--amplitude-scale", type=float, default=1.0, help="Scaling factor for PST bonus amplitudes.")
    parser.add_argument("--weight-outcomes", action="store_true", help="Weight games by match result (Win=1.0, Draw=0.5, Loss=0.0).")
    parser.add_argument("--symmetrize", action="store_true", default=True, help="Enforce horizontal left-right symmetry (default: True).")
    parser.add_argument("--workers", type=int, default=max(1, os.cpu_count() or 4), help="Number of parallel worker processes.")
    parser.add_argument("--limit", type=int, default=None, help="Process only first N games (for debugging).")
    parser.add_argument("--format", type=str, default="all", choices=["all", "cpp", "json", "csv", "markdown"], help="Output format.")
    parser.add_argument("--audit-file", type=str, default="output/dataset_transcription_audit.json",
                        help="Path to dataset transcription audit JSON report to exclude invalid games (default: output/dataset_transcription_audit.json).")
    parser.add_argument("--no-exclude-invalid", action="store_true",
                        help="Disable excluding invalid games identified in the audit file.")

    args = parser.parse_args()

    audit_status = "Disabled (--no-exclude-invalid)" if args.no_exclude_invalid else (args.audit_file or "None")

    print("=" * 70)
    print(" 🌟 Xiangqi Historical PGN Frequency Tracker & PST Table Generator 🌟")
    print("=" * 70)
    print(f"Dataset Directory : {args.dataset_dir}")
    print(f"Output Directory  : {args.output_dir}")
    print(f"Audit Exclusions  : {audit_status}")
    print(f"Tracking Mode     : {args.mode}")
    print(f"PST Method        : {args.method} (amplitude_scale={args.amplitude_scale})")
    print(f"Weight Outcomes   : {args.weight_outcomes}")
    print(f"Symmetrize        : {args.symmetrize}")
    print(f"Worker Processes  : {args.workers}")
    print("-" * 70)

    start_time = time.time()

    # Discover PGN files
    print(f"🔍 Discovering PGN files in '{args.dataset_dir}'...")
    all_files = glob.glob(os.path.join(args.dataset_dir, "**", "*.pgn"), recursive=True)
    if not all_files:
        print(f"❌ Error: No .pgn files found in '{args.dataset_dir}'.")
        sys.exit(1)

    total_discovered = len(all_files)
    print(f"✅ Discovered {total_discovered:,} total PGN files.")

    # Filter out invalid games identified in audit report
    excluded_count = 0
    audit_applied = False
    if args.audit_file and not args.no_exclude_invalid:
        if os.path.exists(args.audit_file):
            print(f"📋 Loading invalid games audit from '{args.audit_file}'...")
            invalid_paths = load_invalid_game_paths(args.audit_file, args.dataset_dir)
            valid_files = [f for f in all_files if not is_file_invalid(f, invalid_paths, args.dataset_dir)]
            excluded_count = total_discovered - len(valid_files)
            print(f"🚫 Excluded {excluded_count:,} invalid games based on audit report.")
            print(f"✅ Retained {len(valid_files):,} valid games for PST compilation.")
            all_files = valid_files
            audit_applied = True
        else:
            print(f"ℹ️ Audit file '{args.audit_file}' not found. No invalid games excluded.")

    if args.limit:
        all_files = all_files[:args.limit]
        print(f"⏱️ Limit active: processing first {len(all_files):,} games.")

    # Split files into chunks for workers
    chunk_size = max(1, len(all_files) // args.workers)
    chunks = [all_files[i:i + chunk_size] for i in range(0, len(all_files), chunk_size)]

    print(f"🚀 Processing games with {len(chunks)} parallel worker pools...")

    pool = mp.Pool(processes=args.workers)
    results = []
    for chunk in chunks:
        res = pool.apply_async(worker_task, (chunk, args.mode, args.weight_outcomes, args.symmetrize))
        results.append(res)

    pool.close()
    pool.join()

    # Merge results
    global_tracker = FrequencyTracker(mode=args.mode, weight_outcomes=args.weight_outcomes, symmetrize=args.symmetrize)
    for res in results:
        tracker = res.get()
        global_tracker.merge(tracker)

    elapsed = time.time() - start_time
    print(f"\n🎉 Successfully processed {global_tracker.total_games:,} games ({global_tracker.total_plies:,} plies) in {elapsed:.2f}s!")
    print(f"⚡ Throughput: {global_tracker.total_games / max(0.001, elapsed):.1f} games/sec ({global_tracker.total_plies / max(0.001, elapsed):.1f} plies/sec)")
    print("-" * 70)

    # Generate PST Tables
    print("📊 Generating Koi Piece-Square Tables (PST)...")
    pst_gen = PSTGenerator(method=args.method)

    pst_by_phase: Dict[str, Dict[str, List[List[int]]]] = {}
    for phase in PHASES:
        freq_dict = {ptype: global_tracker.get_symmetrized_table(phase, ptype) for ptype in PIECE_TYPES}
        pst_by_phase[phase] = pst_gen.generate_all_tables(freq_dict, amplitude_scale=args.amplitude_scale)

    os.makedirs(args.output_dir, exist_ok=True)

    # Exporting
    if args.format in ["all", "cpp"]:
        cpp_file = os.path.join(args.output_dir, "koi_pst.cpp")
        exporters.export_koi_cpp(pst_by_phase["all"], cpp_file, phase="all", mode=args.mode)
        print(f"💾 Exported Koi C++ Tables    : {cpp_file}")

        for ph in ["opening", "midgame", "endgame"]:
            ph_cpp = os.path.join(args.output_dir, f"koi_pst_{ph}.cpp")
            exporters.export_koi_cpp(pst_by_phase[ph], ph_cpp, phase=ph, mode=args.mode)

    if args.format in ["all", "json"]:
        json_file = os.path.join(args.output_dir, "pst_tables.json")
        json_payload = {
            "metadata": {
                "total_games": global_tracker.total_games,
                "total_plies": global_tracker.total_plies,
                "mode": args.mode,
                "method": args.method,
                "amplitude_scale": args.amplitude_scale,
                "weight_outcomes": args.weight_outcomes,
                "symmetrize": args.symmetrize,
                "audit_file": args.audit_file if audit_applied else None,
                "excluded_invalid_games": excluded_count,
                "generated_at": time.strftime("%Y-%m-%d %H:%M:%S")
            },
            "frequencies": global_tracker.to_dict()["tables"],
            "pst_tables": {
                phase: {ptype: pst_by_phase[phase][ptype] for ptype in PIECE_TYPES}
                for phase in PHASES
            }
        }
        exporters.export_json(json_payload, json_file)
        print(f"💾 Exported Full JSON Data    : {json_file}")

    if args.format in ["all", "csv"]:
        csv_file = os.path.join(args.output_dir, "pst_tables.csv")
        exporters.export_csv(pst_by_phase["all"], csv_file)
        print(f"💾 Exported CSV Tables        : {csv_file}")

    if args.format in ["all", "markdown"]:
        md_file = os.path.join(args.output_dir, "heatmaps.md")
        exporters.export_markdown_heatmaps(pst_by_phase, md_file, mode=args.mode)
        print(f"💾 Exported Markdown Heatmaps : {md_file}")

    # Print preview for pieces
    print("\n" + "=" * 70)
    print(" 📋 Sample PST Preview (Overall Phase, Red Perspective)")
    print("   (Row 0 = Enemy Back Rank, Row 4 = Enemy River, Row 5 = Own River, Row 9 = Own Back Rank)")
    print("=" * 70)

    for ptype in ["R", "N", "C", "P", "A", "B"]:
        desc = exporters.PIECE_DESCRIPTIONS.get(ptype, ptype)
        table = pst_by_phase["all"][ptype]
        print(f"\n--- {desc} ({exporters.PIECE_NAMES_CPP.get(ptype)}) ---")
        for r in range(10):
            row_str = " ".join(f"{table[r][c]:3d}" for c in range(9))
            label = ""
            if r == 0: label = "<- Enemy Back Rank"
            elif r == 4: label = "<- Enemy River Bank"
            elif r == 5: label = "<- Own River Bank"
            elif r == 9: label = "<- Own Back Rank"
            print(f"r{r}: [ {row_str} ] {label}")

    print("\n✅ Done!")

if __name__ == "__main__":
    main()
