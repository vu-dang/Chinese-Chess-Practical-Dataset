"""
Xiangqi Piece-Square Table (PST) Generator (Zero-Dependency Pure Python)

Converts empirical frequency distributions into calibrated evaluation bonus/penalty
tables directly compatible with the Koi engine (KoiSearch.cpp).

PST Coordinate Convention (Red perspective, matching Koi getPSTValue):
- row 0: Deep enemy back rank
- row 4: Opponent river bank
- row 5: Own river bank
- row 9: Own back rank
- col 0..8: Left-to-right columns
"""

import math
from typing import Dict, List, Optional, Tuple, Any

def make_bool_grid(val: bool = False) -> List[List[bool]]:
    return [[val for _ in range(9)] for _ in range(10)]

def make_int_grid(val: int = 0) -> List[List[int]]:
    return [[val for _ in range(9)] for _ in range(10)]

# Standard legal square masks (True = legal square, False = illegal/impossible square)
LEGAL_MASKS: Dict[str, List[List[bool]]] = {
    "A": make_bool_grid(False),
    "B": make_bool_grid(False),
    "K": make_bool_grid(False),
    "P": make_bool_grid(False),
    "R": make_bool_grid(True),
    "N": make_bool_grid(True),
    "C": make_bool_grid(True),
}

# Advisor: restricted to palace diagonals
for r, c in [(7, 3), (7, 5), (8, 4), (9, 3), (9, 5)]:
    LEGAL_MASKS["A"][r][c] = True

# Elephant: restricted to 7 eye points on home side
for r, c in [(5, 2), (5, 6), (7, 0), (7, 4), (7, 8), (9, 2), (9, 6)]:
    LEGAL_MASKS["B"][r][c] = True

# King: restricted to 3x3 palace
for r in range(7, 10):
    for c in range(3, 6):
        LEGAL_MASKS["K"][r][c] = True

# Soldier: enemy side (rows 0-4) + home advanced (row 5) + initial slots (row 6)
for r in range(0, 5):
    for c in range(9):
        LEGAL_MASKS["P"][r][c] = True
for c in [0, 2, 4, 6, 8]:
    LEGAL_MASKS["P"][5][c] = True
    LEGAL_MASKS["P"][6][c] = True


# Default target amplitude per piece (aligning with Koi evaluation scale)
DEFAULT_AMPLITUDES = {
    "R": {"min": 0, "max": 12},     # Chariot: mild positional bonus (0 to 12)
    "N": {"min": -4, "max": 8},     # Horse: penalty on rims, bonus on active center outposts
    "C": {"min": -4, "max": 22},    # Cannon: central file and river patrol bonus
    "P": {"min": 0, "max": 20},     # Soldier: 0 on home ranks, scaling up to +20 deep in enemy palace
    "A": {"min": 0, "max": 15},     # Advisor: palace center (+15) vs corners (+5 to +10)
    "B": {"min": 0, "max": 15},     # Elephant: center eye (+15) vs edges (+5)
    "K": {"min": 0, "max": 10},     # General: king safety in palace
}


class PSTGenerator:
    def __init__(self, method: str = "log_zscore", custom_amplitudes: Optional[Dict[str, Dict[str, int]]] = None):
        self.method = method  # 'log_zscore' or 'minmax'
        self.amplitudes = custom_amplitudes or DEFAULT_AMPLITUDES

    def generate_table(self, piece_type: str, freq_matrix: List[List[float]], amplitude_scale: float = 1.0) -> List[List[int]]:
        """
        Converts a 10x9 raw frequency matrix into an integer PST table.
        """
        mask = LEGAL_MASKS.get(piece_type, make_bool_grid(True))
        amp_cfg = self.amplitudes.get(piece_type, {"min": 0, "max": 20})
        target_min = int(round(amp_cfg["min"] * amplitude_scale))
        target_max = int(round(amp_cfg["max"] * amplitude_scale))

        pst = make_int_grid(0)

        # Collect legal entries
        legal_coords = []
        legal_freqs = []
        for r in range(10):
            for c in range(9):
                if mask[r][c]:
                    legal_coords.append((r, c))
                    legal_freqs.append(freq_matrix[r][c])

        if not legal_freqs or all(f == 0 for f in legal_freqs):
            return pst

        if self.method == "log_zscore":
            eps = 1e-6
            log_freqs = [math.log(max(f, 0) + eps) for f in legal_freqs]
            mean_val = sum(log_freqs) / len(log_freqs)
            variance = sum((x - mean_val) ** 2 for x in log_freqs) / len(log_freqs)
            std_val = math.sqrt(variance)
            if std_val < 1e-6:
                std_val = 1.0

            z_scores = [(x - mean_val) / std_val for x in log_freqs]
            z_min = min(z_scores)
            z_max = max(z_scores)

            for i, (r, c) in enumerate(legal_coords):
                if abs(z_max - z_min) > 1e-6:
                    norm = (z_scores[i] - z_min) / (z_max - z_min)
                    score = target_min + norm * (target_max - target_min)
                else:
                    score = (target_min + target_max) / 2.0
                pst[r][c] = int(round(score))

        elif self.method == "minmax":
            f_min = min(legal_freqs)
            f_max = max(legal_freqs)

            for i, (r, c) in enumerate(legal_coords):
                if abs(f_max - f_min) > 1e-6:
                    norm = (legal_freqs[i] - f_min) / (f_max - f_min)
                    score = target_min + norm * (target_max - target_min)
                else:
                    score = (target_min + target_max) / 2.0
                pst[r][c] = int(round(score))

        # Enforce exact 0 on illegal squares
        for r in range(10):
            for c in range(9):
                if not mask[r][c]:
                    pst[r][c] = 0

        # Enforce left-right symmetry in final integer table
        for r in range(10):
            for c in range(5):
                val = (pst[r][c] + pst[r][8 - c]) // 2
                pst[r][c] = val
                pst[r][8 - c] = val

        return pst

    def generate_all_tables(self, frequency_dict: Dict[str, List[List[float]]], amplitude_scale: float = 1.0) -> Dict[str, List[List[int]]]:
        """
        Generates PST tables for all pieces given a dictionary of frequency matrices.
        """
        result = {}
        for ptype, freq_matrix in frequency_dict.items():
            result[ptype] = self.generate_table(ptype, freq_matrix, amplitude_scale)
        return result
