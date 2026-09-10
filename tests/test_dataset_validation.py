"""
Unit Tests for Xiangqi Dataset Move Validation and Transcription Error Auditing
"""

import unittest
import os
import sys
import glob
import json

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))
from xiangqi_board import XiangqiBoard
from audit_dataset_transcriptions import validate_pgn_content

DATASET_DIR = os.path.join(os.path.dirname(__file__), "..", "Dataset")

class TestDatasetValidation(unittest.TestCase):
    def test_sample_games_across_all_categories(self):
        """
        Samples games from each category in Dataset/ and verifies that the board
        simulator steps through legal moves without crashing.
        """
        categories = ["對局", "開局", "中局", "殘局", "全盤戰術", "殺局_殺法_練習題"]
        total_tested = 0
        total_valid = 0

        for cat in categories:
            cat_dir = os.path.join(DATASET_DIR, cat)
            if not os.path.isdir(cat_dir):
                continue

            pgns = sorted(glob.glob(f"{cat_dir}/**/*.pgn", recursive=True))[:50]
            for pgn_file in pgns:
                total_tested += 1
                content = ""
                for enc in ["big5", "cp950", "gb18030", "utf-8"]:
                    try:
                        with open(pgn_file, "r", encoding=enc, errors="ignore") as f:
                            content = f.read()
                        if content:
                            break
                    except Exception:
                        pass

                self.assertTrue(bool(content), f"Failed reading {pgn_file}")
                err = validate_pgn_content(content, pgn_file)
                if err is None:
                    total_valid += 1

        self.assertGreater(total_tested, 0, "No PGN files tested.")
        # Ensure at least 85% of sampled historical games parse cleanly without error
        pass_rate = total_valid / total_tested
        self.assertGreater(
            pass_rate,
            0.85,
            f"Pass rate ({pass_rate * 100:.1f}%) is below minimum threshold."
        )

    def test_detects_illegal_move_transcription(self):
        """
        Ensures that validate_pgn_content accurately flags an illegal move
        in a synthesized PGN string.
        """
        pgn_with_error = """[Event "Test Transcription Error"]
[Round "1"]
1. 炮二平五 馬８進７
2. 馬二進三 車９平８
3. 炮八進九 卒７進１
"""
        # "炮八進九" is illegal because Cannon on row 7 cannot advance 9 rows (7 - 9 = -2 out of board)
        err = validate_pgn_content(pgn_with_error, "test_game.pgn")
        self.assertIsNotNone(err, "Should have detected illegal move")
        self.assertEqual(err["turn"], "Red")
        self.assertEqual(err["moveText"], "炮八進九")

    def test_zhong_zhen_json_dataset(self):
        """
        Validates that zhong_zhen_games.json contains games that can be verified.
        """
        json_file = os.path.join(DATASET_DIR, "zhong_zhen_games.json")
        if not os.path.exists(json_file):
            return

        with open(json_file, "r", encoding="utf-8") as f:
            data = json.load(f)

        self.assertIsInstance(data, list)
        self.assertGreater(len(data), 0)

if __name__ == "__main__":
    unittest.main()
