/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: All | Mode: activated_occupancy
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: all)
const int CHARIOT_PST[10][9] = {
    {  6,   8,   7,   6,   4,   6,   7,   8,   6}, // Enemy back rank
    {  5,   8,   7,   8,   4,   8,   7,   8,   5},
    {  5,   8,   7,   7,   6,   7,   7,   8,   5},
    {  8,   9,   9,  10,   9,  10,   9,   9,   8},
    {  7,   8,   7,   9,   8,   9,   7,   8,   7}, // Enemy river bank
    {  7,  10,   9,  10,   8,  10,   9,  10,   7}, // Own river bank
    {  7,   9,   8,   9,   9,   9,   8,   9,   7},
    {  7,   8,   7,   8,   6,   8,   7,   8,   7},
    {  9,   8,   7,   9,   3,   9,   7,   8,   9},
    {  6,  12,   8,   8,   0,   8,   8,  12,   6} // Own back rank
};

// Horse (Knight) PST (Phase: all)
const int HORSE_PST[10][9] = {
    { -1,  -1,  -2,  -2,  -4,  -2,  -2,  -1,  -1}, // Enemy back rank
    { -1,   1,   2,   0,  -2,   0,   2,   1,  -1},
    {  0,   1,   2,   1,   1,   1,   2,   1,   0},
    {  2,   3,   4,   3,   3,   3,   4,   3,   2},
    {  0,   1,   1,   4,   3,   4,   1,   1,   0}, // Enemy river bank
    { -1,   4,   4,   5,   3,   5,   4,   4,  -1}, // Own river bank
    {  0,   1,   2,   2,   4,   2,   2,   1,   0},
    {  6,   1,   8,   2,   2,   2,   8,   1,   6},
    {  2,  -1,   2,   3,   3,   3,   2,  -1,   2},
    { -3,   3,   1,   1,  -3,   1,   1,   3,  -3} // Own back rank
};

// Cannon PST (Phase: all)
const int CANNON_PST[10][9] = {
    { 10,   8,   5,   0,  -4,   0,   5,   8,  10}, // Enemy back rank
    {  4,   7,   4,   4,  -1,   4,   4,   7,   4},
    {  1,   7,   6,   2,   4,   2,   6,   7,   1},
    { 11,  12,  13,   8,  13,   8,  13,  12,  11},
    {  6,   7,   3,   6,  12,   6,   3,   7,   6}, // Enemy river bank
    {  6,  11,   9,   6,  11,   6,   9,  11,   6}, // Own river bank
    {  2,   8,   6,   6,   8,   6,   6,   8,   2},
    { 15,  10,  16,  17,  22,  17,  16,  10,  15},
    {  8,   8,  12,   9,   8,   9,  12,   8,   8},
    {  1,   3,   8,   8,   1,   8,   8,   3,   1} // Own back rank
};

// Soldier (Pawn) PST (Phase: all)
const int SOLDIER_PST[10][9] = {
    {  9,  10,  11,  11,   9,  11,  11,  10,   9}, // Enemy back rank
    { 11,  13,  14,  15,  12,  15,  14,  13,  11},
    { 12,  13,  15,  14,  14,  14,  15,  13,  12},
    { 15,  15,  16,  16,  16,  16,  16,  15,  15},
    { 16,  15,  17,  16,  17,  16,  17,  15,  16}, // Enemy river bank
    { 19,   0,  20,   0,  18,   0,  20,   0,  19}, // Own river bank
    {  0,   0,   7,   0,   6,   0,   7,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Advisor (Guard) PST (Phase: all)
const int ADVISOR_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   3,   0,   3,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Elephant (Minister) PST (Phase: all)
const int ELEPHANT_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   1,   0,   0,   0,   1,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// General (King) PST (Phase: all)
const int GENERAL_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   1,   0,   0,   0,   0},
    {  0,   0,   0,   6,   7,   6,   0,   0,   0},
    {  0,   0,   0,   9,  10,   9,   0,   0,   0} // Own back rank
};

} // namespace koi
