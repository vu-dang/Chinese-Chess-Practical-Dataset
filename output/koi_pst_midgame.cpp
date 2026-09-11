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
    {  8,  10,  10,  11,   7,  11,  10,  10,   8},
    {  8,  11,  11,  10,  10,  10,  11,  11,   8},
    { 11,  12,  12,  12,  12,  12,  12,  12,  11},
    {  9,  11,  10,  11,  11,  11,  10,  11,   9}, // Enemy river bank
    {  9,  12,  12,  12,  11,  12,  12,  12,   9}, // Own river bank
    {  9,  11,  11,  11,  11,  11,  11,  11,   9},
    {  8,  10,   9,  10,   8,  10,   9,  10,   8},
    {  8,  10,   9,  10,   6,  10,   9,  10,   8},
    {  8,  10,   9,  10,   0,  10,   9,  10,   8} // Own back rank
};

// Horse (Knight) PST (Phase: midgame)
const int HORSE_PST[10][9] = {
    {  1,   1,   0,   1,  -4,   1,   0,   1,   1}, // Enemy back rank
    {  1,   3,   5,   3,   1,   3,   5,   3,   1},
    {  4,   3,   6,   4,   6,   4,   6,   3,   4},
    {  5,   5,   7,   6,   7,   6,   7,   5,   5},
    {  3,   5,   4,   7,   6,   7,   4,   5,   3}, // Enemy river bank
    {  2,   7,   6,   8,   6,   8,   6,   7,   2}, // Own river bank
    {  4,   4,   6,   6,   8,   6,   6,   4,   4},
    {  5,   4,   7,   5,   4,   5,   7,   4,   5},
    {  4,   2,   5,   5,   5,   5,   5,   2,   4},
    {  0,   5,   3,   4,  -2,   4,   3,   5,   0} // Own back rank
};

// Cannon PST (Phase: midgame)
const int CANNON_PST[10][9] = {
    { 17,  16,  14,  10,  -4,  10,  14,  16,  17}, // Enemy back rank
    { 11,  13,  12,  13,   8,  13,  12,  13,  11},
    { 11,  14,  16,  12,  16,  12,  16,  14,  11},
    { 20,  18,  18,  17,  22,  17,  18,  18,  20},
    { 15,  15,  13,  14,  19,  14,  13,  15,  15}, // Enemy river bank
    { 14,  16,  16,  15,  19,  15,  16,  16,  14}, // Own river bank
    {  9,  14,  15,  14,  15,  14,  15,  14,   9},
    { 17,  18,  20,  20,  18,  20,  20,  18,  17},
    { 14,  16,  17,  16,  14,  16,  17,  16,  14},
    {  7,   9,  13,  12,  -3,  12,  13,   9,   7} // Own back rank
};

// Soldier (Pawn) PST (Phase: midgame)
const int SOLDIER_PST[10][9] = {
    { 13,  14,  15,  16,  13,  16,  15,  14,  13}, // Enemy back rank
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
