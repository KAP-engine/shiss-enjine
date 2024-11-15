#pragma once

#include <cstdint>

#include "types_and_consts.h"

chessboard_t new_chessboard(); 

uint64_t set_bit(uint64_t board, int coordinate); 

uint64_t clear_bit(uint64_t board, int coordinate); 

int to_index(int x, int y, int width);
