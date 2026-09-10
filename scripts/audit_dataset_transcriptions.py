#!/usr/bin/env python3
"""
Xiangqi Dataset Transcription Error Audit Tool (Zero-Dependency Pure Python)

Scans all games (.pgn and .json) in the Chinese-Chess-Practical-Dataset,
steps through every move on a 10x9 Xiangqi board simulator, detects transcription
and illegal move errors, and outputs a structured audit report.

Usage:
    python3 scripts/audit_dataset_transcriptions.py
    python3 scripts/audit_dataset_transcriptions.py --category 對局
    python3 scripts/audit_dataset_transcriptions.py --sample 1000
    python3 scripts/audit_dataset_transcriptions.py --output output/dataset_transcription_audit.json
"""

import os
import sys
import glob
import json
import time
import re
import argparse
from typing import List, Dict, Any, Optional, Tuple
import multiprocessing as mp

# Add scripts directory to module path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xiangqi_board import XiangqiBoard, Piece

def validate_pgn_content(content: str, filepath: str) -> Optional[Dict[str, Any]]:
    """
    Simulates a single PGN game.
    Returns None if 100% valid, or a Dict detailing the first invalid move.
    """
    lines = content.split("\n")
    
    title = os.path.splitext(os.path.basename(filepath))[0]
    red_player = ""
    black_player = ""
    event = ""
    date = ""
    fen_initial = None
    move_lines = []

    for line in lines:
        line = line.strip()
        if not line:
            continue
        if line.startswith("["):
            if line.startswith("[FEN") and "\"" in line:
                fen_initial = line.split("\"")[1]
            elif line.startswith("[Red") and "\"" in line:
                red_player = line.split("\"")[1]
            elif line.startswith("[Black") and "\"" in line:
                black_player = line.split("\"")[1]
            elif line.startswith("[Event") and "\"" in line:
                event = line.split("\"")[1]
            elif line.startswith("[Date") and "\"" in line:
                date = line.split("\"")[1]
        else:
            move_lines.append(line)

    board = XiangqiBoard(fen_initial or XiangqiBoard.INITIAL_FEN)
    current_color = board.active_color  # "w" or "b"

    # Tokenize move text
    full_text = " ".join(move_lines)
    full_text = re.sub(r"(1-0|0-1|1/2-1/2|\*)", "", full_text)
    raw_tokens = full_text.split()
    moves: List[str] = []
    for tok in raw_tokens:
        tok = tok.strip()
        if re.match(r"^\d+\.+$", tok):
            continue
        if re.match(r"^\d+\.", tok):
            tok = re.sub(r"^\d+\.+", "", tok)
        if tok and len(tok) >= 4:
            moves.append(tok)

    for i, raw_move in enumerate(moves):
        is_red = (current_color == "w")
        parsed = board.parse_move(raw_move, is_red=is_red)
        if not parsed:
            return {
                "file": filepath,
                "event": event,
                "date": date,
                "red": red_player,
                "black": black_player,
                "moveNumber": i + 1,
                "turn": "Red" if is_red else "Black",
                "moveText": raw_move,
                "fen": fen_initial or XiangqiBoard.INITIAL_FEN,
                "reason": f"Move '{raw_move}' could not be legally parsed or applied for {'Red' if is_red else 'Black'}."
            }
        board.apply_move(*parsed)
        current_color = "b" if is_red else "w"

    return None

def process_file_worker(filepath: str) -> Tuple[str, bool, Optional[Dict[str, Any]]]:
    """Worker process to read and validate a file."""
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
        return filepath, False, {
            "file": filepath,
            "reason": "Could not decode file with supported encodings."
        }

    err = validate_pgn_content(content, filepath)
    if err:
        return filepath, False, err
    return filepath, True, None

def audit_dataset(
    dataset_dir: str,
    category: Optional[str] = None,
    sample_size: Optional[int] = None,
    output_file: Optional[str] = None,
    num_workers: Optional[int] = None
) -> Dict[str, Any]:
    """Runs a complete multi-core audit of the dataset."""
    if category:
        target_dir = os.path.join(dataset_dir, category)
        pattern = os.path.join(target_dir, "**/*.pgn")
    else:
        pattern = os.path.join(dataset_dir, "**/*.pgn")

    files = sorted(glob.glob(pattern, recursive=True))
    if sample_size and sample_size < len(files):
        files = files[:sample_size]

    total_files = len(files)
    print(f"Scanning {total_files} game files in: {dataset_dir} (Category: {category or 'All'})")

    if not num_workers:
        num_workers = max(1, mp.cpu_count() - 1)

    start_time = time.time()
    valid_count = 0
    errors: List[Dict[str, Any]] = []

    with mp.Pool(num_workers) as pool:
        for idx, (filepath, is_valid, err) in enumerate(pool.imap_unordered(process_file_worker, files, chunksize=100)):
            if is_valid:
                valid_count += 1
            else:
                if err:
                    errors.append(err)

            if (idx + 1) % 5000 == 0 or (idx + 1) == total_files:
                elapsed = time.time() - start_time
                rate = (idx + 1) / elapsed if elapsed > 0 else 0
                print(f"Progress: {idx + 1}/{total_files} ({(idx + 1) / total_files * 100:.1f}%) | "
                      f"Valid: {valid_count} | Errors: {len(errors)} | {rate:.1f} games/s")

    elapsed_total = time.time() - start_time
    pass_rate = (valid_count / total_files * 100) if total_files > 0 else 0

    results = {
        "datasetDir": dataset_dir,
        "category": category or "All",
        "totalGames": total_files,
        "validGames": valid_count,
        "invalidGames": len(errors),
        "passRate": round(pass_rate, 2),
        "elapsedSeconds": round(elapsed_total, 2),
        "gamesPerSecond": round(total_files / elapsed_total, 1) if elapsed_total > 0 else 0,
        "errors": errors
    }

    print("\n" + "=" * 55)
    print("           DATASET AUDIT SUMMARY")
    print("=" * 55)
    print(f"Total Games Scanned: {total_files:,}")
    print(f"Valid Games:         {valid_count:,} ({pass_rate:.2f}%)")
    print(f"Transcription Errors:{len(errors):,}")
    print(f"Time Elapsed:        {elapsed_total:.2f}s ({results['gamesPerSecond']} games/s)")
    print("=" * 55)

    if output_file:
        os.makedirs(os.path.dirname(os.path.abspath(output_file)), exist_ok=True)
        with open(output_file, "w", encoding="utf-8") as f:
            json.dump(results, f, ensure_ascii=False, indent=2)
        print(f"Saved detailed audit report to: {output_file}")

    return results

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Audit Xiangqi dataset for transcription errors.")
    default_dataset = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "Dataset")
    parser.add_argument("--dataset-dir", default=default_dataset, help="Path to Dataset directory")
    parser.add_argument("--category", default=None, help="Filter by subcategory (e.g. 對局, 開局, 殘局)")
    parser.add_argument("--sample", type=int, default=None, help="Limit number of games to sample")
    parser.add_argument("--output", default="output/dataset_transcription_audit.json", help="Path to output report")
    parser.add_argument("--workers", type=int, default=None, help="Number of worker processes")
    args = parser.parse_args()

    audit_dataset(
        dataset_dir=args.dataset_dir,
        category=args.category,
        sample_size=args.sample,
        output_file=args.output,
        num_workers=args.workers
    )
