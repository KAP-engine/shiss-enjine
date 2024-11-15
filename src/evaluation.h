#pragma once

#include <cstdint>

#include "types_and_consts.h"

int evaluate_bitboard(uint64_t board, int piece, int color);

int evaluate_board(chessboard_t chessboard);
