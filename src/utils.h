#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

#include "chessboard.h"

// idk what this does nor whether its used or not.
std::vector<std::string> split_string(const std::string& s);

// These four functions all set and clear bits of a bit board, the difference
// between the first pair and the second is that the first pair performs the
// operation on the bit board itself since it receives its pointer, while the
// second pair returns a new bit board with the desired edition.
void set_bit(uint64_t &board, int index); 
void clear_bit(uint64_t &board, int index); 
uint64_t set_bit_val(uint64_t board, int index); 
uint64_t clear_bit_val(uint64_t board, int index); 

// This function reverses the bits of a bit board.
int64_t reverse_bitboard(uint64_t bitboard);

// This is a small helper function that transforms board x and y coordinates to
// an index, useful.
int to_index(int x, int y);

// This function returns the appropriate symbol for the give square of the
// board.
char piece_char_at(chessboard_t& board, int square_index);
