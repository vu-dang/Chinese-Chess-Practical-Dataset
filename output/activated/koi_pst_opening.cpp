/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: Opening | Mode: activated_occupancy
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: opening)
const int CHARIOT_PST[10][9] = {
    {  3,   7,   6,   5,   4,   5,   6,   7,   3}, // Enemy back rank
    {  4,   8,   6,   8,   4,   8,   6,   8,   4},
    {  4,   8,   7,   7,   4,   7,   7,   8,   4},
    {  6,   9,   9,   9,   7,   9,   9,   9,   6},
    {  7,   8,   7,   8,   6,   8,   7,   8,   7}, // Enemy river bank
    {  6,  10,   9,   9,   7,   9,   9,  10,   6}, // Own river bank
    {  7,   8,   7,   8,   6,   8,   7,   8,   7},
    {  8,   8,   6,   7,   4,   7,   6,   8,   8},
    { 10,   9,   8,  10,   4,  10,   8,   9,  10},
    {  6,  12,   8,   8,   0,   8,   8,  12,   6} // Own back rank
};

// Horse (Knight) PST (Phase: opening)
const int HORSE_PST[10][9] = {
    { -2,  -1,  -2,  -2,  -4,  -2,  -2,  -1,  -2}, // Enemy back rank
    { -2,   0,   1,  -1,  -2,  -1,   1,   0,  -2},
    {  0,  -1,   2,   0,   1,   0,   2,  -1,   0},
    {  3,   1,   4,   2,   3,   2,   4,   1,   3},
    { -1,   1,   0,   3,   1,   3,   0,   1,  -1}, // Enemy river bank
    { -2,   5,   2,   5,   1,   5,   2,   5,  -2}, // Own river bank
    {  0,   1,   2,   2,   4,   2,   2,   1,   0},
    {  6,   1,   8,   2,   1,   2,   8,   1,   6},
    {  2,  -2,   2,   4,   4,   4,   2,  -2,   2},
    { -2,   4,   0,   2,  -4,   2,   0,   4,  -2} // Own back rank
};

// Cannon PST (Phase: opening)
const int CANNON_PST[10][9] = {
    {  5,   5,   6,   0,  -3,   0,   6,   5,   5}, // Enemy back rank
    {  1,   8,   3,   4,  -1,   4,   3,   8,   1},
    {  1,   9,   6,   6,   4,   6,   6,   9,   1},
    { 10,  14,  14,   7,  12,   7,  14,  14,  10},
    {  4,   8,   6,   5,  11,   5,   6,   8,   4}, // Enemy river bank
    {  6,  14,   9,   6,  10,   6,   9,  14,   6}, // Own river bank
    { -1,  10,   6,   6,   4,   6,   6,  10,  -1},
    { 17,   9,  17,  17,  22,  17,  17,   9,  17},
    { 10,  10,  12,   6,  10,   6,  12,  10,  10},
    {  1,   7,   7,   5,  -4,   5,   7,   7,   1} // Own back rank
};

// Soldier (Pawn) PST (Phase: opening)
const int SOLDIER_PST[10][9] = {
    { 11,  12,  13,  13,  11,  13,  13,  12,  11}, // Enemy back rank
    { 12,  13,  14,  14,  14,  14,  14,  13,  12},
    { 13,  14,  15,  15,  15,  15,  15,  14,  13},
    { 15,  15,  17,  16,  16,  16,  17,  15,  15},
    { 16,  16,  18,  16,  18,  16,  18,  16,  16}, // Enemy river bank
    { 18,   0,  20,   0,  18,   0,  20,   0,  18}, // Own river bank
    {  0,   0,  11,   0,  11,   0,  11,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Advisor (Guard) PST (Phase: opening)
const int ADVISOR_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Elephant (Minister) PST (Phase: opening)
const int ELEPHANT_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   4,   0,   0,   0,   4,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  6,   0,   0,   0,  15,   0,   0,   0,   6},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// General (King) PST (Phase: opening)
const int GENERAL_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   6,   8,   6,   0,   0,   0},
    {  0,   0,   0,  10,   8,  10,   0,   0,   0} // Own back rank
};

} // namespace koi
