/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: Midgame | Mode: activated_occupancy
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: midgame)
const int CHARIOT_PST[10][9] = {
    {  7,   9,   9,   7,   5,   7,   9,   9,   7}, // Enemy back rank
    {  6,   9,   9,  10,   5,  10,   9,   9,   6},
    {  7,  10,   9,   8,   8,   8,   9,  10,   7},
    { 10,  11,  11,  11,  11,  11,  11,  11,  10},
    {  8,  10,   9,  10,  10,  10,   9,  10,   8}, // Enemy river bank
    {  8,  11,  11,  11,  10,  11,  11,  11,   8}, // Own river bank
    {  8,  11,  10,  11,  10,  11,  10,  11,   8},
    {  8,  10,   8,  10,   7,  10,   8,  10,   8},
    {  9,  10,   9,  10,   5,  10,   9,  10,   9},
    {  8,  12,  10,  10,   0,  10,  10,  12,   8} // Own back rank
};

// Horse (Knight) PST (Phase: midgame)
const int HORSE_PST[10][9] = {
    {  0,   0,  -1,  -1,  -4,  -1,  -1,   0,   0}, // Enemy back rank
    {  0,   2,   3,   1,  -1,   1,   3,   2,   0},
    {  2,   1,   4,   1,   2,   1,   4,   1,   2},
    {  4,   3,   5,   4,   4,   4,   5,   3,   4},
    {  1,   3,   2,   5,   4,   5,   2,   3,   1}, // Enemy river bank
    {  1,   6,   5,   6,   3,   6,   5,   6,   1}, // Own river bank
    {  2,   3,   4,   4,   6,   4,   4,   3,   2},
    {  6,   3,   8,   4,   3,   4,   8,   3,   6},
    {  4,   1,   3,   4,   4,   4,   3,   1,   4},
    { -1,   4,   2,   3,  -2,   3,   2,   4,  -1} // Own back rank
};

// Cannon PST (Phase: midgame)
const int CANNON_PST[10][9] = {
    { 14,  12,  10,   3,  -2,   3,  10,  12,  14}, // Enemy back rank
    {  7,  11,   9,   9,   2,   9,   9,  11,   7},
    {  6,  12,  11,   5,   8,   5,  11,  12,   6},
    { 16,  15,  17,  13,  17,  13,  17,  15,  16},
    { 11,  11,   8,  10,  17,  10,   8,  11,  11}, // Enemy river bank
    { 11,  14,  14,  10,  16,  10,  14,  14,  11}, // Own river bank
    {  5,  12,  10,  10,  11,  10,  10,  12,   5},
    { 18,  15,  19,  21,  22,  21,  19,  15,  18},
    { 12,  12,  16,  13,  12,  13,  16,  12,  12},
    {  5,   7,  12,  11,  -4,  11,  12,   7,   5} // Own back rank
};

// Soldier (Pawn) PST (Phase: midgame)
const int SOLDIER_PST[10][9] = {
    { 13,  14,  15,  14,  13,  14,  15,  14,  13}, // Enemy back rank
    { 15,  15,  16,  16,  15,  16,  16,  15,  15},
    { 16,  16,  17,  16,  16,  16,  17,  16,  16},
    { 17,  17,  18,  18,  18,  18,  18,  17,  17},
    { 18,  18,  19,  18,  19,  18,  19,  18,  18}, // Enemy river bank
    { 20,   0,  20,   0,  20,   0,  20,   0,  20}, // Own river bank
    {  0,   0,  11,   0,   0,   0,  11,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// Advisor (Guard) PST (Phase: midgame)
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

// Elephant (Minister) PST (Phase: midgame)
const int ELEPHANT_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   2,   0,   0,   0,   2,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  2,   0,   0,   0,  15,   0,   0,   0,   2},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0} // Own back rank
};

// General (King) PST (Phase: midgame)
const int GENERAL_PST[10][9] = {
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy back rank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Enemy river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,   1,   0,   0,   0,   0},
    {  0,   0,   0,   6,   8,   6,   0,   0,   0},
    {  0,   0,   0,  10,  10,  10,   0,   0,   0} // Own back rank
};

} // namespace koi
