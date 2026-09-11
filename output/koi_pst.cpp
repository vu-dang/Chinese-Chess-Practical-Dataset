/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: All | Mode: destination
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: all)
const int CHARIOT_PST[10][9] = {
    {  7,  10,   8,   8,   5,   8,   8,  10,   7}, // Enemy back rank
    {  6,   9,   8,   9,   6,   9,   8,   9,   6},
    {  6,   9,   8,   8,   8,   8,   8,   9,   6},
    {  9,  11,  10,  11,  10,  11,  10,  11,   9},
    {  8,   9,   9,  10,   9,  10,   9,   9,   8}, // Enemy river bank
    {  7,  11,  10,  10,   9,  10,  10,  11,   7}, // Own river bank
    {  7,  10,   9,  10,   9,  10,   9,  10,   7},
    {  7,   8,   7,   8,   6,   8,   7,   8,   7},
    { 10,   9,   7,  10,   4,  10,   7,   9,  10},
    {  6,  12,   8,   8,   0,   8,   8,  12,   6} // Own back rank
};

// Horse (Knight) PST (Phase: all)
const int HORSE_PST[10][9] = {
    { -1,   0,  -1,  -1,  -3,  -1,  -1,   0,  -1}, // Enemy back rank
    {  0,   2,   3,   1,   0,   1,   3,   2,   0},
    {  2,   2,   4,   3,   4,   3,   4,   2,   2},
    {  3,   4,   5,   4,   5,   4,   5,   4,   3},
    {  1,   3,   2,   5,   5,   5,   2,   3,   1}, // Enemy river bank
    {  0,   5,   4,   6,   4,   6,   4,   5,   0}, // Own river bank
    {  1,   2,   4,   3,   6,   3,   4,   2,   1},
    {  5,   2,   8,   3,   2,   3,   8,   2,   5},
    {  2,   0,   2,   3,   4,   3,   2,   0,   2},
    { -3,   4,   1,   1,  -4,   1,   1,   4,  -3} // Own back rank
};

// Cannon PST (Phase: all)
const int CANNON_PST[10][9] = {
    { 12,  12,  10,   6,  -4,   6,  10,  12,  12}, // Enemy back rank
    {  8,  10,   8,   8,   5,   8,   8,  10,   8},
    {  6,  11,  11,   8,  11,   8,  11,  11,   6},
    { 16,  16,  15,  13,  18,  13,  15,  16,  16},
    { 10,  11,   9,  11,  15,  11,   9,  11,  10}, // Enemy river bank
    { 10,  14,  12,  11,  15,  11,  12,  14,  10}, // Own river bank
    {  6,  11,  10,  10,  12,  10,  10,  11,   6},
    { 17,  13,  18,  19,  22,  19,  18,  13,  17},
    { 12,  13,  14,  13,  12,  13,  14,  13,  12},
    {  4,   7,   9,   9,   3,   9,   9,   7,   4} // Own back rank
};

// Soldier (Pawn) PST (Phase: all)
const int SOLDIER_PST[10][9] = {
    { 15,  15,  16,  16,  15,  16,  16,  15,  15}, // Enemy back rank
    { 15,  17,  18,  18,  17,  18,  18,  17,  15},
    { 16,  17,  18,  18,  18,  18,  18,  17,  16},
    { 18,  18,  19,  18,  19,  18,  19,  18,  18},
    { 19,  18,  20,  18,  19,  18,  20,  18,  19}, // Enemy river bank
    { 19,   0,  20,   0,  20,   0,  20,   0,  19}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
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
    {  0,   0,   0,   2,   0,   2,   0,   0,   0},
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
    {  0,   0,   2,   0,   0,   0,   2,   0,   0}, // Own river bank
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
    {  0,   0,   0,   0,   2,   0,   0,   0,   0},
    {  0,   0,   0,   7,   9,   7,   0,   0,   0},
    {  0,   0,   0,   9,  10,   9,   0,   0,   0} // Own back rank
};

} // namespace koi
