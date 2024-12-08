#pragma once

#include <cstdint>
#include <iostream>
#include <array>

#include "chessboard.h"

void print_bin(uint64_t n);

void print_bitboard(uint64_t board);
void print_chessboard(chessboard_t board);
// values should be in the order of the chessboard
void print_board_layout(std::array<std::string, 64> values);
