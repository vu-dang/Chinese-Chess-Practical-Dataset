/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: Opening | Mode: destination
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: opening)
const int CHARIOT_PST[10][9] = {
    {  4,  10,   7,   7,   4,   7,   7,  10,   4}, // Enemy back rank
    {  5,   8,   7,   8,   5,   8,   7,   8,   5},
    {  5,   8,   7,   8,   5,   8,   7,   8,   5},
    {  7,  10,  10,  10,   8,  10,  10,  10,   7},
    {  7,   9,   8,   9,   7,   9,   8,   9,   7}, // Enemy river bank
    {  7,  10,  10,  10,   8,  10,  10,  10,   7}, // Own river bank
    {  7,   9,   7,   8,   7,   8,   7,   9,   7},
    {  8,   8,   7,   7,   5,   7,   7,   8,   8},
    { 11,   9,   8,  10,   4,  10,   8,   9,  11},
    {  6,  12,   8,   9,   0,   9,   8,  12,   6} // Own back rank
};

// Horse (Knight) PST (Phase: opening)
const int HORSE_PST[10][9] = {
    { -3,  -1,  -3,  -1,  -4,  -1,  -3,  -1,  -3}, // Enemy back rank
    { -2,   0,   1,   0,  -2,   0,   1,   0,  -2},
    {  2,  -1,   3,   0,   3,   0,   3,  -1,   2},
    {  3,   1,   5,   2,   5,   2,   5,   1,   3},
    { -1,   2,   1,   4,   2,   4,   1,   2,  -1}, // Enemy river bank
    { -1,   5,   2,   6,   2,   6,   2,   5,  -1}, // Own river bank
    {  1,   2,   3,   2,   6,   2,   3,   2,   1},
    {  6,   2,   8,   2,   1,   2,   8,   2,   6},
    {  3,  -1,   2,   4,   5,   4,   2,  -1,   3},
    { -2,   5,   1,   2,  -4,   2,   1,   5,  -2} // Own back rank
};

// Cannon PST (Phase: opening)
const int CANNON_PST[10][9] = {
    {  8,   9,  10,   6,  -4,   6,  10,   9,   8}, // Enemy back rank
    {  4,  11,   7,   8,   5,   8,   7,  11,   4},
    {  8,  13,  12,  11,  11,  11,  12,  13,   8},
    { 14,  17,  16,  11,  17,  11,  16,  17,  14},
    {  8,  12,  10,   9,  14,   9,  10,  12,   8}, // Enemy river bank
    {  9,  16,  13,  10,  13,  10,  13,  16,   9}, // Own river bank
    {  3,  13,  10,  10,   8,  10,  10,  13,   3},
    { 18,  13,  19,  19,  22,  19,  19,  13,  18},
    { 13,  14,  15,  10,  13,  10,  15,  14,  13},
    {  5,  11,  10,   7,  -3,   7,  10,  11,   5} // Own back rank
};

// Soldier (Pawn) PST (Phase: opening)
const int SOLDIER_PST[10][9] = {
    { 12,  12,  13,  13,  12,  13,  13,  12,  12}, // Enemy back rank
    { 12,  13,  15,  14,  15,  14,  15,  13,  12},
    { 14,  14,  16,  15,  15,  15,  16,  14,  14},
    { 15,  15,  17,  16,  17,  16,  17,  15,  15},
    { 17,  16,  19,  17,  18,  17,  19,  16,  17}, // Enemy river bank
    { 19,   0,  20,   0,  19,   0,  20,   0,  19}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
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
    {  0,   0,   5,   0,   0,   0,   5,   0,   0}, // Own river bank
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
    {  0,   0,   0,   0,   1,   0,   0,   0,   0},
    {  0,   0,   0,   6,   9,   6,   0,   0,   0},
    {  0,   0,   0,  10,   8,  10,   0,   0,   0} // Own back rank
};

} // namespace koi
