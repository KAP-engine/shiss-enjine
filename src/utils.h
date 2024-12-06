#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

#include "chessboard.h"

chessboard_t new_chessboard(); 

std::vector<std::string> split_string(const std::string& s);

uint64_t set_bit(uint64_t board, int coordinate); 

uint64_t clear_bit(uint64_t board, int coordinate); 

int to_index(int x, int y);

char piece_char_at(chessboard_t& board, int square);
