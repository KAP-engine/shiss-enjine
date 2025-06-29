#pragma once

#include <cstdint>

#include "chessboard.h"

// This function returns the score of the bit board depending on the color and
// type of the piece. It's used in evaluate_board().
int evaluate_bitboard(uint64_t board, uint8_t piece, uint8_t color);

// This function returns the score of the entire chess board.
int evaluate_board(chessboard_t chessboard);
