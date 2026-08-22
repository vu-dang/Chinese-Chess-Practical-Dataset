"""
Unit Tests for Xiangqi Board, Move Parsing, and PST Generation (Zero-Dependency)
"""

import unittest
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))

from xiangqi_board import XiangqiBoard, Piece
from frequency_tracker import FrequencyTracker
from pst_generator import PSTGenerator, LEGAL_MASKS

class TestXiangqiBoard(unittest.TestCase):
    def test_initial_board_setup(self):
        board = XiangqiBoard()
        # Red King at (9, 4), Black King at (0, 4)
        red_king = board.grid[9][4]
        black_king = board.grid[0][4]
        self.assertIsNotNone(red_king)
        self.assertEqual(red_king.type, "K")
        self.assertEqual(red_king.color, "w")
        self.assertIsNotNone(black_king)
        self.assertEqual(black_king.type, "K")
        self.assertEqual(black_king.color, "b")

        # Total 32 pieces
        self.assertEqual(len(board.pieces), 32)

    def test_coordinate_mapping(self):
        # Red: File 1 -> col 8, File 9 -> col 0
        self.assertEqual(XiangqiBoard.file_to_col(1, is_red=True), 8)
        self.assertEqual(XiangqiBoard.file_to_col(9, is_red=True), 0)
        self.assertEqual(XiangqiBoard.file_to_col(5, is_red=True), 4)

        # Black: File 1 -> col 0, File 9 -> col 8
        self.assertEqual(XiangqiBoard.file_to_col(1, is_red=False), 0)
        self.assertEqual(XiangqiBoard.file_to_col(9, is_red=False), 8)
        self.assertEqual(XiangqiBoard.file_to_col(5, is_red=False), 4)

    def test_basic_moves(self):
        board = XiangqiBoard()

        # 1. 炮二平五 (Red Cannon on file 2 -> col 7 moves horizontally to file 5 -> col 4)
        m = board.parse_move("炮二平五", is_red=True)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(piece.type, "C")
        self.assertEqual(src, (7, 7))
        self.assertEqual(dst, (7, 4))
        board.apply_move(piece, src, dst, cap)
        self.assertIsNone(board.grid[7][7])
        self.assertEqual(board.grid[7][4].type, "C")

        # 1... 馬８進７ (Black Horse on file 8 -> col 7 jumps to file 7 -> col 6, row 0 -> 2)
        m = board.parse_move("馬８進７", is_red=False)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(piece.type, "N")
        self.assertEqual(src, (0, 7))
        self.assertEqual(dst, (2, 6))
        board.apply_move(piece, src, dst, cap)

        # 2. 馬二進三 (Red Horse on file 2 -> col 7 jumps to file 3 -> col 6, clearing (9, 7))
        m = board.parse_move("馬二進三", is_red=True)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(piece.type, "N")
        self.assertEqual(src, (9, 7))
        self.assertEqual(dst, (7, 6))
        board.apply_move(piece, src, dst, cap)

        # 2... 車９進１ (Black Rook on file 9 -> col 8 advances 1 step to row 1)
        m = board.parse_move("車９進１", is_red=False)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(piece.type, "R")
        self.assertEqual(src, (0, 8))
        self.assertEqual(dst, (1, 8))
        board.apply_move(piece, src, dst, cap)

        # 3. 車一平二 (Red Rook on file 1 -> col 8 moves to file 2 -> col 7)
        m = board.parse_move("車一平二", is_red=True)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(piece.type, "R")
        self.assertEqual(src, (9, 8))
        self.assertEqual(dst, (9, 7))
        board.apply_move(piece, src, dst, cap)

        # 3... 卒７進１ (Black Pawn on file 7 -> col 6 advances 1 step: row 3 -> 4)
        m = board.parse_move("卒７進１", is_red=False)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(piece.type, "P")
        self.assertEqual(src, (3, 6))
        self.assertEqual(dst, (4, 6))
        board.apply_move(piece, src, dst, cap)

    def test_front_rear_disambiguation(self):
        # Setup board with two Red Rooks on the same column (col 4 / file 5): at row 2 and row 7
        fen = "4k4/9/4R4/9/9/9/9/4R4/9/4K4 w - - 0 1"
        board = XiangqiBoard(fen)

        # "前車退一" (Front rook at row 2 retreats 1 step to row 3)
        m = board.parse_move("前車退一", is_red=True)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(src, (2, 4))
        self.assertEqual(dst, (3, 4))

        # "後車進二" (Rear rook at row 7 advances 2 steps to row 5)
        m = board.parse_move("後車進二", is_red=True)
        self.assertIsNotNone(m)
        piece, src, dst, cap = m
        self.assertEqual(src, (7, 4))
        self.assertEqual(dst, (5, 4))


class TestFrequencyTrackerAndPST(unittest.TestCase):
    def test_frequency_accumulation_and_symmetry(self):
        tracker = FrequencyTracker(mode="destination", symmetrize=True)

        # Record a move for Red Chariot landing on (1, 1) (Red perspective)
        tracker.record_move("R", "w", (1, 1), full_move=5, weight=10.0)

        # Symmetrized table should have 5.0 at (1, 1) and 5.0 at (1, 7)
        table = tracker.get_symmetrized_table("opening", "R")
        self.assertEqual(table[1][1], 5.0)
        self.assertEqual(table[1][7], 5.0)

    def test_pst_generator_constraints(self):
        tracker = FrequencyTracker(mode="destination", symmetrize=True)
        # Populate advisor frequencies
        tracker.record_move("A", "w", (8, 4), full_move=10, weight=100.0)
        tracker.record_move("A", "w", (7, 3), full_move=10, weight=50.0)

        gen = PSTGenerator(method="log_zscore")
        freq_dict = {pt: tracker.get_symmetrized_table("all", pt) for pt in ["R", "N", "C", "P", "A", "B", "K"]}
        pst_tables = gen.generate_all_tables(freq_dict)

        # Advisor PST should be 0 on illegal squares outside palace diagonals
        advisor_pst = pst_tables["A"]
        self.assertEqual(advisor_pst[0][0], 0)  # corner off-board
        self.assertEqual(advisor_pst[5][4], 0)  # river center
        # Legal palace squares should be symmetric
        self.assertEqual(advisor_pst[7][3], advisor_pst[7][5])
        self.assertEqual(advisor_pst[9][3], advisor_pst[9][5])


if __name__ == "__main__":
    unittest.main()
