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
    {  7,   8,   9,   9,   9,   9,   9,   8,   7},
    { 11,  11,  11,  12,  12,  12,  11,  11,  11},
    {  9,   9,   9,  11,  11,  11,   9,   9,   9}, // Enemy river bank
    {  8,  10,  11,  11,  11,  11,  11,  10,   8}, // Own river bank
    {  8,  10,  10,  11,  11,  11,  10,  10,   8},
    {  6,   8,   8,   9,   8,   9,   8,   8,   6},
    {  5,   7,   6,   7,   3,   7,   6,   7,   5},
    {  5,   7,   5,   6,   0,   6,   5,   7,   5} // Own back rank
};

// Horse (Knight) PST (Phase: endgame)
const int HORSE_PST[10][9] = {
    {  1,   1,   1,   1,  -2,   1,   1,   1,   1}, // Enemy back rank
    {  1,   4,   6,   3,   2,   3,   6,   4,   1},
    {  3,   4,   6,   5,   6,   5,   6,   4,   3},
    {  3,   6,   7,   8,   6,   8,   7,   6,   3},
    {  3,   4,   4,   8,   8,   8,   4,   4,   3}, // Enemy river bank
    {  2,   5,   7,   6,   7,   6,   7,   5,   2}, // Own river bank
    {  1,   3,   5,   5,   7,   5,   5,   3,   1},
    {  2,   3,   5,   5,   3,   5,   5,   3,   2},
    {  0,   0,   2,   2,  -1,   2,   2,   0,   0},
    { -4,   0,   0,   0,  -4,   0,   0,   0,  -4} // Own back rank
};

// Cannon PST (Phase: endgame)
const int CANNON_PST[10][9] = {
    { 17,  16,   8,   6,  -4,   6,   8,  16,  17}, // Enemy back rank
    { 12,  10,   8,   7,   5,   7,   8,  10,  12},
    {  3,   5,   4,   4,   9,   4,   4,   5,   3},
    { 18,  16,  12,  18,  22,  18,  12,  16,  18},
    { 13,  12,   5,  16,  20,  16,   5,  12,  13}, // Enemy river bank
    { 12,  14,  12,  15,  21,  15,  12,  14,  12}, // Own river bank
    { 10,  11,   8,  14,  18,  14,   8,  11,  10},
    { 13,  14,  13,  19,  19,  19,  13,  14,  13},
    { 14,  15,  14,  20,  15,  20,  14,  15,  14},
    {  3,   5,   8,  13,   9,  13,   8,   5,   3} // Own back rank
};

// Soldier (Pawn) PST (Phase: endgame)
const int SOLDIER_PST[10][9] = {
    { 11,  12,  13,  14,  11,  14,  13,  12,  11}, // Enemy back rank
    { 12,  15,  18,  18,  17,  18,  18,  15,  12},
    { 14,  16,  18,  18,  18,  18,  18,  16,  14},
    { 17,  18,  19,  20,  20,  20,  19,  18,  17},
    { 19,  18,  19,  18,  20,  18,  19,  18,  19}, // Enemy river bank
    { 19,   0,  16,   0,  19,   0,  16,   0,  19}, // Own river bank
    {  0,   0,   6,   0,   8,   0,   6,   0,   0},
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
    {  0,   0,   0,   0,   1,   0,   0,   0,   0},
    {  0,   0,   0,   7,   8,   7,   0,   0,   0},
    {  0,   0,   0,   9,  10,   9,   0,   0,   0} // Own back rank
};

} // namespace koi
