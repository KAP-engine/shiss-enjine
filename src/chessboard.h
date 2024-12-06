#pragma once

#include <cstdint>

// CHESSBOARD_T
typedef struct {
    // white pieces
    uint64_t white_pawns;
    uint64_t white_king;
    uint64_t white_ministers; // "queen"
    uint64_t white_rooks;
    uint64_t white_elephants; // "elephant"
    uint64_t white_knights;
    // black pieces
    uint64_t black_pawns;
    uint64_t black_king;
    uint64_t black_ministers; // "queen"
    uint64_t black_rooks;
    uint64_t black_elephants; // "elephant"
    uint64_t black_knights;
} chessboard_t;

void chessboard_move(chessboard_t&, int start, int target);
