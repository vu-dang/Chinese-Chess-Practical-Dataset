/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: Midgame | Mode: destination
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: midgame)
const int CHARIOT_PST[10][9] = {
    {  8,  11,  10,   9,   6,   9,  10,  11,   8}, // Enemy back rank
    {  7,  10,  10,  11,   7,  11,  10,  10,   7},
    {  8,  11,  11,  10,  10,  10,  11,  11,   8},
    { 11,  12,  12,  12,  12,  12,  12,  12,  11},
    {  9,  11,  10,  11,  11,  11,  10,  11,   9}, // Enemy river bank
    {  9,  12,  12,  12,  11,  12,  12,  12,   9}, // Own river bank
    {  8,  11,  11,  11,  11,  11,  11,  11,   8},
    {  8,  10,   9,  10,   8,  10,   9,  10,   8},
    {  8,  10,   9,  10,   6,  10,   9,  10,   8},
    {  8,  10,   9,  10,   0,  10,   9,  10,   8} // Own back rank
};

// Horse (Knight) PST (Phase: midgame)
const int HORSE_PST[10][9] = {
    {  0,   0,  -1,   0,  -4,   0,  -1,   0,   0}, // Enemy back rank
    {  0,   3,   5,   3,   1,   3,   5,   3,   0},
    {  3,   2,   5,   3,   6,   3,   5,   2,   3},
    {  4,   5,   6,   6,   7,   6,   6,   5,   4},
    {  2,   4,   4,   7,   6,   7,   4,   4,   2}, // Enemy river bank
    {  2,   7,   6,   8,   5,   8,   6,   7,   2}, // Own river bank
    {  3,   4,   6,   5,   8,   5,   6,   4,   3},
    {  4,   4,   7,   4,   4,   4,   7,   4,   4},
    {  4,   2,   4,   4,   5,   4,   4,   2,   4},
    { -1,   5,   3,   3,  -4,   3,   3,   5,  -1} // Own back rank
};

// Cannon PST (Phase: midgame)
const int CANNON_PST[10][9] = {
    { 16,  15,  14,   9,  -2,   9,  14,  15,  16}, // Enemy back rank
    { 11,  12,  12,  12,   8,  12,  12,  12,  11},
    { 10,  14,  16,  11,  15,  11,  16,  14,  10},
    { 20,  18,  18,  17,  22,  17,  18,  18,  20},
    { 14,  15,  13,  14,  19,  14,  13,  15,  14}, // Enemy river bank
    { 13,  16,  16,  14,  19,  14,  16,  16,  13}, // Own river bank
    {  8,  14,  14,  14,  14,  14,  14,  14,   8},
    { 16,  18,  20,  20,  18,  20,  20,  18,  16},
    { 14,  15,  17,  16,  13,  16,  17,  15,  14},
    {  7,   9,  12,  12,  -4,  12,  12,   9,   7} // Own back rank
};

// Soldier (Pawn) PST (Phase: midgame)
const int SOLDIER_PST[10][9] = {
    { 13,  14,  15,  16,  14,  16,  15,  14,  13}, // Enemy back rank
    { 15,  16,  17,  17,  17,  17,  17,  16,  15},
    { 16,  17,  18,  17,  18,  17,  18,  17,  16},
    { 18,  18,  19,  18,  19,  18,  19,  18,  18},
    { 19,  18,  20,  19,  20,  19,  20,  18,  19}, // Enemy river bank
    { 20,   0,  19,   0,  20,   0,  19,   0,  20}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
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
    {  0,   0,   0,   2,   0,   2,   0,   0,   0},
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
    {  0,   0,   4,   0,   0,   0,   4,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   1,   0,   0,   0,   1,   0,   0} // Own back rank
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
    {  0,   0,   0,   0,   2,   0,   0,   0,   0},
    {  0,   0,   0,   7,   9,   7,   0,   0,   0},
    {  0,   0,   0,  10,   9,  10,   0,   0,   0} // Own back rank
};

} // namespace koi
