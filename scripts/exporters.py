"""
Exporters for Xiangqi Frequency & PST Tables (Zero-Dependency Pure Python)

Exports to:
- Koi C++ Source / Header (KoiSearch.cpp compatible)
- JSON (structured metadata, frequencies, and PST values)
- CSV (matrix and tabular records)
- Markdown Visual Heatmaps (ASCII/formatted boards for documentation)
"""

import os
import json
import csv
from typing import Dict, Any, List

PIECE_NAMES_CPP = {
    "R": "CHARIOT_PST",
    "N": "HORSE_PST",
    "C": "CANNON_PST",
    "P": "SOLDIER_PST",
    "A": "ADVISOR_PST",
    "B": "ELEPHANT_PST",
    "K": "GENERAL_PST",
}

PIECE_DESCRIPTIONS = {
    "R": "Chariot (Rook)",
    "N": "Horse (Knight)",
    "C": "Cannon",
    "P": "Soldier (Pawn)",
    "A": "Advisor (Guard)",
    "B": "Elephant (Minister)",
    "K": "General (King)",
}

def export_koi_cpp(pst_dict: Dict[str, List[List[int]]], output_file: str, phase: str = "all", mode: str = "destination") -> None:
    """Exports PST tables in C++ syntax matching KoiSearch.cpp formatting."""
    os.makedirs(os.path.dirname(os.path.abspath(output_file)), exist_ok=True)
    
    with open(output_file, "w", encoding="utf-8") as f:
        f.write("/*\n")
        f.write(" * Koi Engine Piece-Square Tables (PST)\n")
        f.write(" * Derived from 58,000+ Master Games (CCPD Dataset)\n")
        f.write(f" * Phase: {phase.capitalize()} | Mode: {mode}\n")
        f.write(" *\n")
        f.write(" * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.\n")
        f.write(" */\n\n")
        f.write("namespace koi {\n\n")

        for ptype, var_name in PIECE_NAMES_CPP.items():
            if ptype not in pst_dict:
                continue
            table = pst_dict[ptype]
            desc = PIECE_DESCRIPTIONS.get(ptype, ptype)
            f.write(f"// {desc} PST (Phase: {phase})\n")
            f.write(f"const int {var_name}[10][9] = {{\n")
            for r in range(10):
                row_vals = ", ".join(f"{table[r][c]:3d}" for c in range(9))
                comma = "," if r < 9 else ""
                comment = ""
                if r == 0: comment = " // Enemy back rank"
                elif r == 4: comment = " // Enemy river bank"
                elif r == 5: comment = " // Own river bank"
                elif r == 9: comment = " // Own back rank"
                f.write(f"    {{{row_vals}}}{comma}{comment}\n")
            f.write("};\n\n")

        f.write("} // namespace koi\n")


def export_json(all_pst_data: Dict[str, Any], output_file: str) -> None:
    """Exports full nested PST data and metadata to JSON."""
    os.makedirs(os.path.dirname(os.path.abspath(output_file)), exist_ok=True)
    with open(output_file, "w", encoding="utf-8") as f:
        json.dump(all_pst_data, f, indent=2)


def export_csv(pst_dict: Dict[str, List[List[int]]], output_file: str) -> None:
    """Exports PST tables to CSV."""
    os.makedirs(os.path.dirname(os.path.abspath(output_file)), exist_ok=True)
    with open(output_file, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["Piece", "Row", "Col0", "Col1", "Col2", "Col3", "Col4", "Col5", "Col6", "Col7", "Col8"])
        for ptype, table in pst_dict.items():
            for r in range(10):
                writer.writerow([ptype, r] + [int(table[r][c]) for c in range(9)])


def export_markdown_heatmaps(pst_by_phase: Dict[str, Dict[str, List[List[int]]]], output_file: str, mode: str = "destination") -> None:
    """Exports formatted Markdown visual boards showing PST heatmaps for each piece and phase."""
    os.makedirs(os.path.dirname(os.path.abspath(output_file)), exist_ok=True)
    
    with open(output_file, "w", encoding="utf-8") as f:
        f.write("# Xiangqi Piece-Square Tables (PST) Heatmaps\n\n")
        f.write(f"> Generated from CCPD Historical Dataset (58k+ Master Matches) | Mode: `{mode}`\n\n")
        f.write("Orientation: **Row 0 = Enemy Back Rank**, **Row 9 = Own Back Rank**\n\n")

        for phase, piece_dict in pst_by_phase.items():
            f.write(f"## Phase: {phase.upper()}\n\n")
            for ptype, table in piece_dict.items():
                desc = PIECE_DESCRIPTIONS.get(ptype, ptype)
                f.write(f"### {desc} (`{ptype}`)\n\n")
                f.write("| Rank | c0 | c1 | c2 | c3 | c4 (Center) | c5 | c6 | c7 | c8 | Context |\n")
                f.write("|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---|\n")
                for r in range(10):
                    row_str = " | ".join(f"{table[r][c]:+3d}" if table[r][c] != 0 else "  0 " for c in range(9))
                    ctx = ""
                    if r == 0: ctx = "Enemy Back Rank"
                    elif r == 4: ctx = "Enemy River Bank"
                    elif r == 5: ctx = "Own River Bank (River Boundary)"
                    elif r == 7: ctx = "Own Palace Top"
                    elif r == 8: ctx = "Own Palace Center"
                    elif r == 9: ctx = "Own Back Rank"
                    f.write(f"| **r{r}** | {row_str} | *{ctx}* |\n")
                f.write("\n---\n\n")
