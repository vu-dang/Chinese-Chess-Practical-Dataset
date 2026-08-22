"""
Xiangqi Frequency Tracker (Zero-Dependency Pure Python)

Accumulates piece square occurrences across 58k+ Xiangqi matches with support for:
- Modes: 'destination' (move targets only), 'activated_occupancy' (ignoring unmoved pieces), 'all_occupancy', 'blended'
- Phase segmentation: Opening (1-15), Midgame (16-35), Endgame (36+), All
- Outcome weighting: Red Win, Black Win, Draw
- Red/Black perspective normalization into a unified 10x9 grid
- Horizontal symmetry folding (c <-> 8-c)
"""

from typing import Dict, List, Optional, Tuple, Any

PIECE_TYPES = ["R", "N", "C", "P", "A", "B", "K"]
PHASES = ["opening", "midgame", "endgame", "all"]

def make_grid(val: float = 0.0) -> List[List[float]]:
    return [[val for _ in range(9)] for _ in range(10)]

class FrequencyTracker:
    def __init__(self, mode: str = "destination", weight_outcomes: bool = False, symmetrize: bool = True):
        self.mode = mode  # 'destination', 'activated_occupancy', 'all_occupancy', 'blended'
        self.weight_outcomes = weight_outcomes
        self.symmetrize = symmetrize

        # Data structure: counts[phase][piece_type] -> 10x9 list of floats
        self.counts: Dict[str, Dict[str, List[List[float]]]] = {
            phase: {ptype: make_grid(0.0) for ptype in PIECE_TYPES}
            for phase in PHASES
        }
        self.total_games = 0
        self.total_plies = 0

    def get_phase(self, full_move_num: int) -> str:
        if full_move_num <= 15:
            return "opening"
        elif full_move_num <= 35:
            return "midgame"
        else:
            return "endgame"

    def normalize_coord(self, row: int, col: int, color: str) -> Tuple[int, int]:
        """
        Normalizes a board coordinate to standard Red-perspective (10x9 grid):
        - For Red: r = row, c = col
        - For Black: r = 9 - row, c = 8 - col (mirrors board vertically and horizontally to align side files)
        """
        if color == "w":
            return row, col
        else:
            return 9 - row, 8 - col

    def record_move(self, piece_type: str, color: str, to_pos: Tuple[int, int], full_move: int, weight: float = 1.0):
        """Records a move landing destination."""
        norm_r, norm_c = self.normalize_coord(to_pos[0], to_pos[1], color)
        phase = self.get_phase(full_move)

        if 0 <= norm_r < 10 and 0 <= norm_c < 9:
            self.counts[phase][piece_type][norm_r][norm_c] += weight
            self.counts["all"][piece_type][norm_r][norm_c] += weight

    def record_occupancy(self, pieces: List[Any], full_move: int, red_weight: float = 1.0, black_weight: float = 1.0):
        """Records current board square occupancy based on active tracking mode."""
        phase = self.get_phase(full_move)

        for p in pieces:
            if self.mode == "activated_occupancy" and p.move_count == 0:
                continue  # Ignore unmoved stationary starting pieces

            weight = red_weight if p.color == "w" else black_weight
            norm_r, norm_c = self.normalize_coord(p.row, p.col, p.color)

            if 0 <= norm_r < 10 and 0 <= norm_c < 9:
                self.counts[phase][p.type][norm_r][norm_c] += weight
                self.counts["all"][p.type][norm_r][norm_c] += weight

    def merge(self, other: "FrequencyTracker"):
        """Merges another FrequencyTracker into this instance (used for parallel multiprocessing)."""
        self.total_games += other.total_games
        self.total_plies += other.total_plies
        for phase in PHASES:
            for ptype in PIECE_TYPES:
                for r in range(10):
                    for c in range(9):
                        self.counts[phase][ptype][r][c] += other.counts[phase][ptype][r][c]

    def get_symmetrized_table(self, phase: str, piece_type: str) -> List[List[float]]:
        """Returns the 10x9 table for a piece and phase, optionally folded horizontally."""
        raw = self.counts[phase][piece_type]
        result = make_grid(0.0)
        for r in range(10):
            for c in range(9):
                if self.symmetrize:
                    result[r][c] = (raw[r][c] + raw[r][8 - c]) / 2.0
                else:
                    result[r][c] = raw[r][c]
        return result

    def to_dict(self) -> Dict[str, Any]:
        """Serializes frequency tables into JSON-serializable dictionary."""
        result = {
            "total_games": self.total_games,
            "total_plies": self.total_plies,
            "mode": self.mode,
            "symmetrized": self.symmetrize,
            "tables": {}
        }
        for phase in PHASES:
            result["tables"][phase] = {}
            for ptype in PIECE_TYPES:
                result["tables"][phase][ptype] = self.get_symmetrized_table(phase, ptype)
        return result
