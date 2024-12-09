#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

#include "chessboard.h"

chessboard_t new_chessboard(); 

std::vector<std::string> split_string(const std::string& s);

void set_bit(uint64_t &board, int index); 

void clear_bit(uint64_t &board, int index); 

uint64_t set_bit_val(uint64_t board, int index); 

uint64_t clear_bit_val(uint64_t board, int index); 

int64_t reverse_bitboard(uint64_t bitboard);

int to_index(int x, int y);

char piece_char_at(chessboard_t& board, int square_index);
