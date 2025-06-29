#pragma once

#include <cstdint>
#include <iostream>
#include <array>

#include "chessboard.h"

// This function prins a number in its binary form, useful for debugging and
// viewing bit boards.
void print_bin(uint64_t n);

// This functions prints a bit board in the form of a board, also useful for
// debugging.
void print_bitboard(uint64_t board);

// This function prints the entire chess board.
void print_chessboard(chessboard_t board);

// This function is used in print_chessboard(), it prints the board with and
// fills each square with the corresponding element of <values>.
// the values should be in the order of the chessboard, meaning from bottom
// left to top right.
void print_board_layout(std::array<std::string, 64> values);

// This function is also used in print_chessboard(), it prints the information
// related to the board such as the current playing side, castling rights, etc.
void print_board_info(chessboard_t& board);
