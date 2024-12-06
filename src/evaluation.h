#pragma once

#include <cstdint>

#include "chessboard.h"

int evaluate_bitboard(uint64_t board, int piece, int color);

int evaluate_board(chessboard_t chessboard);
