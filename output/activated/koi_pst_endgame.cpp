/*
 * Koi Engine Piece-Square Tables (PST)
 * Derived from 58,000+ Master Games (CCPD Dataset)
 * Phase: Endgame | Mode: activated_occupancy
 *
 * Orientation: [r][col] where r=0 is enemy back rank, r=9 is own back rank.
 */

namespace koi {

// Chariot (Rook) PST (Phase: endgame)
const int CHARIOT_PST[10][9] = {
    {  8,  10,   9,   8,   6,   8,   9,  10,   8}, // Enemy back rank
    {  7,   9,   9,   9,   6,   9,   9,   9,   7},
    {  6,   8,   8,   8,   9,   8,   8,   8,   6},
    { 10,  11,  11,  12,  12,  12,  11,  11,  10},
    {  8,   9,   8,  11,  11,  11,   8,   9,   8}, // Enemy river bank
    {  8,  10,  11,  11,  11,  11,  11,  10,   8}, // Own river bank
    {  8,  11,  10,  11,  12,  11,  10,  11,   8},
    {  6,   9,   8,   9,   8,   9,   8,   9,   6},
    {  5,   7,   7,   8,   2,   8,   7,   7,   5},
    {  5,   8,   7,   6,   0,   6,   7,   8,   5} // Own back rank
};

// Horse (Knight) PST (Phase: endgame)
const int HORSE_PST[10][9] = {
    {  1,   0,   0,  -1,  -4,  -1,   0,   0,   1}, // Enemy back rank
    {  0,   3,   7,   2,  -1,   2,   7,   3,   0},
    {  2,   4,   6,   3,   4,   3,   6,   4,   2},
    {  3,   7,   7,   8,   5,   8,   7,   7,   3},
    {  2,   4,   3,   8,   8,   8,   3,   4,   2}, // Enemy river bank
    {  1,   5,   8,   7,   7,   7,   8,   5,   1}, // Own river bank
    {  0,   3,   5,   4,   7,   4,   5,   3,   0},
    {  5,   3,   8,   6,   4,   6,   8,   3,   5},
    {  2,   0,   3,   3,   1,   3,   3,   0,   2},
    { -3,   2,   1,   3,  -3,   3,   1,   2,  -3} // Own back rank
};

// Cannon PST (Phase: endgame)
const int CANNON_PST[10][9] = {
    { 22,  17,   7,   1,  -4,   1,   7,  17,  22}, // Enemy back rank
    { 12,  10,   8,   7,   0,   7,   8,  10,  12},
    {  3,   4,   5,   0,   5,   0,   5,   4,   3},
    { 17,  14,  13,  16,  22,  16,  13,  14,  17},
    { 12,  10,   1,  14,  20,  14,   1,  10,  12}, // Enemy river bank
    { 11,  12,  13,  12,  21,  12,  13,  12,  11}, // Own river bank
    {  7,   9,   7,  11,  17,  11,   7,   9,   7},
    { 14,  15,  15,  21,  21,  21,  15,  15,  14},
    { 13,  14,  16,  20,  12,  20,  16,  14,  13},
    {  2,   4,  12,  16,   9,  16,  12,   4,   2} // Own back rank
};

// Soldier (Pawn) PST (Phase: endgame)
const int SOLDIER_PST[10][9] = {
    { 10,  12,  13,  12,  11,  12,  13,  12,  10}, // Enemy back rank
    { 12,  14,  16,  17,  14,  17,  16,  14,  12},
    { 13,  15,  16,  15,  16,  15,  16,  15,  13},
    { 16,  17,  18,  19,  19,  19,  18,  17,  16},
    { 18,  17,  17,  18,  19,  18,  17,  17,  18}, // Enemy river bank
    { 20,   0,  19,   0,  19,   0,  19,   0,  20}, // Own river bank
    {  0,   0,   8,   0,   7,   0,   8,   0,   0},
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
    {  0,   0,   3,   0,   0,   0,   3,   0,   0}, // Own river bank
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   0,   0,  15,   0,   0,   0,   0},
    {  0,   0,   0,   0,   0,   0,   0,   0,   0},
    {  0,   0,   3,   0,   0,   0,   3,   0,   0} // Own back rank
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
    {  0,   0,   0,   6,   7,   6,   0,   0,   0},
    {  0,   0,   0,   8,  10,   8,   0,   0,   0} // Own back rank
};

} // namespace koi
