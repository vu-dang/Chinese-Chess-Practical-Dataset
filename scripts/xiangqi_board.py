"""
Xiangqi (Chinese Chess) Board Representation & Move Notation Parser

Handles:
- 10x9 board state simulation
- FEN parsing and serialization
- Chinese move notation parsing (traditional & simplified characters, full-width digits, prefixes)
- Unique piece tracking to support unmoved vs activated piece status
"""

from typing import List, Tuple, Optional, Dict, Any

class Piece:
    def __init__(self, piece_id: int, piece_type: str, color: str, row: int, col: int):
        self.id = piece_id
        self.type = piece_type  # 'K', 'A', 'B', 'N', 'R', 'C', 'P'
        self.color = color      # 'w' (Red) or 'b' (Black)
        self.row = row
        self.col = col
        self.move_count = 0

    @property
    def char(self) -> str:
        return self.type.upper() if self.color == 'w' else self.type.lower()

    def __repr__(self):
        return f"Piece({self.char}#{self.id} at ({self.row},{self.col}), moves={self.move_count})"


class XiangqiBoard:
    INITIAL_FEN = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1"

    # Digits mapping
    RED_NUMS = {
        "一": 1, "二": 2, "三": 3, "四": 4, "五": 5, "六": 6, "七": 7, "八": 8, "九": 9,
        "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9,
        "１": 1, "２": 2, "３": 3, "４": 4, "５": 5, "６": 6, "７": 7, "８": 8, "９": 9,
    }
    BLACK_NUMS = {
        "１": 1, "２": 2, "３": 3, "４": 4, "５": 5, "６": 6, "７": 7, "８": 8, "９": 9,
        "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9,
        "一": 1, "二": 2, "三": 3, "四": 4, "五": 5, "六": 6, "七": 7, "八": 8, "九": 9,
    }

    # Piece names mapping
    RED_PIECES = {
        "帥": "K", "将": "K", "將": "K",
        "仕": "A", "士": "A",
        "相": "B", "象": "B",
        "馬": "N", "傌": "N", "马": "N",
        "車": "R", "俥": "R", "车": "R",
        "炮": "C", "砲": "C", "包": "C",
        "兵": "P", "卒": "P",
    }
    BLACK_PIECES = {
        "將": "K", "将": "K", "帥": "K",
        "士": "A", "仕": "A",
        "象": "B", "相": "B",
        "馬": "N", "傌": "N", "马": "N",
        "車": "R", "俥": "R", "车": "R",
        "炮": "C", "砲": "C", "包": "C",
        "卒": "P", "兵": "P",
    }

    def __init__(self, fen: Optional[str] = None):
        self.grid: List[List[Optional[Piece]]] = [[None for _ in range(9)] for _ in range(10)]
        self.pieces: Dict[int, Piece] = {}
        self.next_piece_id = 1
        self.active_color = "w"
        self.half_move_count = 0
        self.full_move_count = 1
        self.set_fen(fen or self.INITIAL_FEN)

    def set_fen(self, fen: str) -> None:
        parts = fen.strip().split()
        if not parts:
            return
        rows = parts[0].split("/")
        self.grid = [[None for _ in range(9)] for _ in range(10)]
        self.pieces.clear()
        self.next_piece_id = 1

        for r, row_str in enumerate(rows[:10]):
            c = 0
            for ch in row_str:
                if c >= 9:
                    break
                if ch.isdigit():
                    c += int(ch)
                else:
                    color = "w" if ch.isupper() else "b"
                    ptype = ch.upper()
                    piece = Piece(self.next_piece_id, ptype, color, r, c)
                    self.pieces[piece.id] = piece
                    self.grid[r][c] = piece
                    self.next_piece_id += 1
                    c += 1

        if len(parts) > 1:
            self.active_color = parts[1]
        if len(parts) > 4:
            try:
                self.half_move_count = int(parts[4])
            except ValueError:
                pass
        if len(parts) > 5:
            try:
                self.full_move_count = int(parts[5])
            except ValueError:
                pass

    @staticmethod
    def file_to_col(file_num: int, is_red: bool) -> int:
        """Converts Xiangqi 1-based file (1..9) to 0-based col (0..8)."""
        if is_red:
            return 9 - file_num
        return file_num - 1

    @staticmethod
    def col_to_file(col: int, is_red: bool) -> int:
        """Converts 0-based col (0..8) to Xiangqi 1-based file (1..9)."""
        if is_red:
            return 9 - col
        return col + 1

    def find_pieces(self, piece_type: str, color: str) -> List[Piece]:
        return [p for p in self.pieces.values() if p.type == piece_type and p.color == color]

    def parse_move(self, move_str: str, is_red: bool) -> Optional[Tuple[Piece, Tuple[int, int], Tuple[int, int], Optional[Piece]]]:
        """
        Parses a 4-character Chinese move notation into:
        (moved_piece, (from_row, from_col), (to_row, to_col), captured_piece_or_None)
        """
        move_str = move_str.strip()
        if len(move_str) != 4:
            return None

        c1, c2, c3, c4 = move_str[0], move_str[1], move_str[2], move_str[3]
        action = c3  # '進', '退', '平'
        if action not in ["進", "退", "平"]:
            return None

        target_pieces_map = self.RED_PIECES if is_red else self.BLACK_PIECES
        num_map = self.RED_NUMS if is_red else self.BLACK_NUMS
        side_color = "w" if is_red else "b"

        # 1. Identify Candidate Pieces
        candidates: List[Piece] = []

        if c1 in ["前", "後", "中"]:
            ptype = target_pieces_map.get(c2)
            if not ptype:
                return None
            matching_pieces = self.find_pieces(ptype, side_color)
            
            # Group by file
            by_file: Dict[int, List[Piece]] = {}
            for p in matching_pieces:
                by_file.setdefault(p.col, []).append(p)

            # Sort by rank:
            # For Red (moving towards row 0): smaller row = front ("前"), larger row = rear ("後")
            # For Black (moving towards row 9): larger row = front ("前"), smaller row = rear ("後")
            for col, plist in by_file.items():
                if len(plist) >= 2:
                    plist.sort(key=lambda p: p.row)
                    if is_red:
                        # Red: [0] is front, [-1] is rear
                        if c1 == "前": candidates.append(plist[0])
                        elif c1 == "後": candidates.append(plist[-1])
                        elif c1 == "中" and len(plist) >= 3: candidates.append(plist[1])
                    else:
                        # Black: [-1] is front, [0] is rear
                        if c1 == "前": candidates.append(plist[-1])
                        elif c1 == "後": candidates.append(plist[0])
                        elif c1 == "中" and len(plist) >= 3: candidates.append(plist[1])

            # If no single file has multiple pieces, sort all candidates by rank
            if not candidates and matching_pieces:
                matching_pieces.sort(key=lambda p: p.row)
                if is_red:
                    if c1 == "前": candidates.append(matching_pieces[0])
                    elif c1 == "後": candidates.append(matching_pieces[-1])
                else:
                    if c1 == "前": candidates.append(matching_pieces[-1])
                    elif c1 == "後": candidates.append(matching_pieces[0])

        else:
            ptype = target_pieces_map.get(c1)
            if not ptype:
                return None
            orig_file = num_map.get(c2)
            if orig_file is None:
                return None
            src_col = self.file_to_col(orig_file, is_red)
            if not (0 <= src_col < 9):
                return None

            for r in range(10):
                p = self.grid[r][src_col]
                if p and p.type == ptype and p.color == side_color:
                    candidates.append(p)

        if not candidates:
            return None

        # 2. Calculate Destination Square for each candidate
        if c4 not in num_map:
            return None

        valid_moves = []
        for piece in candidates:
            sr, sc = piece.row, piece.col
            pt = piece.type
            tr, tc = None, None

            if pt in ["R", "C", "P", "K"]:  # Orthogonal pieces
                if action == "平":
                    dst_file = num_map[c4]
                    tc = self.file_to_col(dst_file, is_red)
                    tr = sr
                elif action == "進":
                    steps = num_map[c4]
                    tr = sr - steps if is_red else sr + steps
                    tc = sc
                elif action == "退":
                    steps = num_map[c4]
                    tr = sr + steps if is_red else sr - steps
                    tc = sc

            elif pt in ["N", "B", "A"]:  # Diagonal / Stepping pieces
                dst_file = num_map[c4]
                tc = self.file_to_col(dst_file, is_red)
                col_diff = abs(tc - sc)
                row_diff = 0

                if pt == "N" and col_diff in (1, 2):
                    row_diff = 2 if col_diff == 1 else 1
                elif pt == "B" and col_diff == 2:
                    row_diff = 2
                elif pt == "A" and col_diff == 1:
                    row_diff = 1

                if row_diff > 0:
                    if action == "進":
                        tr = sr - row_diff if is_red else sr + row_diff
                    elif action == "退":
                        tr = sr + row_diff if is_red else sr - row_diff

            if tr is not None and tc is not None and (0 <= tr < 10) and (0 <= tc < 9):
                # Basic piece-specific sanity
                if pt == "K" and not (3 <= tc <= 5 and ((7 <= tr <= 9) if is_red else (0 <= tr <= 2))):
                    continue
                if pt == "A" and not (3 <= tc <= 5 and ((7 <= tr <= 9) if is_red else (0 <= tr <= 2))):
                    continue
                if pt == "B" and not (((5 <= tr <= 9) if is_red else (0 <= tr <= 4))):
                    continue
                
                # Check destination not occupied by friendly piece
                dest_piece = self.grid[tr][tc]
                if dest_piece and dest_piece.color == side_color:
                    continue

                valid_moves.append((piece, (sr, sc), (tr, tc), dest_piece))

        if len(valid_moves) == 1:
            return valid_moves[0]
        elif len(valid_moves) > 1:
            # If multiple valid moves, choose the one with legal move obstruction/path check or first
            return valid_moves[0]

        return None

    def apply_move(self, piece: Piece, from_pos: Tuple[int, int], to_pos: Tuple[int, int], captured: Optional[Piece] = None) -> None:
        """Applies a move on the board and updates piece states."""
        sr, sc = from_pos
        tr, tc = to_pos

        if captured and captured.id in self.pieces:
            del self.pieces[captured.id]

        self.grid[sr][sc] = None
        self.grid[tr][tc] = piece
        piece.row = tr
        piece.col = tc
        piece.move_count += 1

        self.half_move_count += 1
        if piece.color == "b":
            self.full_move_count += 1
        self.active_color = "b" if piece.color == "w" else "w"
