/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: Endgame | Mode: destination
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: endgame)
const int CHARIOT_PST[10][9] = {
    {  9,  11,  10,   9,   7,   9,  10,  11,   9}, // Enemy back rank
    {  7,   9,   9,  10,   8,  10,   9,   9,   7},
    {  6,   8,   9,   8,   9,   8,   9,   8,   6},
    { 11,  11,  11,  12,  12,  12,  11,  11,  11},
    {  9,   9,   9,  11,  11,  11,   9,   9,   9}, // Enemy river bank
    {  8,  10,  11,  11,  11,  11,  11,  10,   8}, // Own river bank
    {  8,  10,  10,  11,  11,  11,  10,  10,   8},
    {  6,   8,   8,   9,   8,   9,   8,   8,   6},
    {  5,   6,   6,   7,   3,   7,   6,   6,   5},
    {  5,   6,   5,   6,   0,   6,   5,   6,   5} // Own back rank
};

// Horse (Knight) PST (Phase: endgame)
const int HORSE_PST[10][9] = {
    {  1,   1,   1,   1,  -2,   1,   1,   1,   1}, // Enemy back rank
    {  1,   4,   6,   2,   2,   2,   6,   4,   1},
    {  3,   4,   6,   5,   6,   5,   6,   4,   3},
    {  4,   6,   7,   8,   6,   8,   7,   6,   4},
    {  3,   4,   4,   8,   8,   8,   4,   4,   3}, // Enemy river bank
    {  2,   5,   7,   6,   7,   6,   7,   5,   2}, // Own river bank
    {  1,   3,   5,   5,   7,   5,   5,   3,   1},
    {  2,   3,   5,   5,   3,   5,   5,   3,   2},
    {  0,   0,   2,   2,  -1,   2,   2,   0,   0},
    { -3,   0,   0,   0,  -4,   0,   0,   0,  -3} // Own back rank
};

// Cannon PST (Phase: endgame)
const int CANNON_PST[10][9] = {
    { 18,  17,  10,   7,  -4,   7,  10,  17,  18}, // Enemy back rank
    { 13,  11,   9,   8,   6,   8,   9,  11,  13},
    {  5,   6,   5,   5,   9,   5,   5,   6,   5},
    { 18,  16,  13,  18,  22,  18,  13,  16,  18},
    { 14,  12,   6,  16,  20,  16,   6,  12,  14}, // Enemy river bank
    { 13,  14,  13,  16,  21,  16,  13,  14,  13}, // Own river bank
    { 11,  11,   9,  14,  19,  14,   9,  11,  11},
    { 14,  15,  14,  19,  20,  19,  14,  15,  14},
    { 16,  16,  15,  20,  16,  20,  15,  16,  16},
    {  5,   7,  10,  15,  10,  15,  10,   7,   5} // Own back rank
};

// Soldier (Pawn) PST (Phase: endgame)
const int SOLDIER_PST[10][9] = {
    { 16,  16,  17,  17,  16,  17,  17,  16,  16}, // Enemy back rank
    { 17,  18,  19,  19,  19,  19,  19,  18,  17},
    { 17,  18,  19,  19,  19,  19,  19,  18,  17},
    { 19,  19,  20,  20,  20,  20,  20,  19,  19},
    { 20,  19,  19,  19,  20,  19,  19,  19,  20}, // Enemy river bank
    { 20,   0,  18,   0,  19,   0,  18,   0,  20}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Advisor (Guard) PST (Phase: endgame)
const int ADVISOR_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   5,   0,   5,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Elephant (Minister) PST (Phase: endgame)
const int ELEPHANT_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   4,   0,   0,   0,   4,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   4,   0,   0,   0,   4,   0,   0} // Own back rank
};

// General (King) PST (Phase: endgame)
const int GENERAL_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   2,   0,   0,   0,   0},
    {  0,   0,   0,   7,   8,   7,   0,   0,   0},
    {  0,   0,   0,   9,  10,   9,   0,   0,   0} // Own back rank
};

} // namespace koi
