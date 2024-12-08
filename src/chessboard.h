#pragma once

#include <cstdint>
#include <array>

// CHESSBOARD_T
typedef struct {
    std::array<uint64_t, 12> bitboards;
} chessboard_t;

void chessboard_move(chessboard_t &, int source, int destination);

uint64_t all_white_pieces(chessboard_t &board); 
uint64_t all_black_pieces(chessboard_t &board); 
uint64_t all_pieces(chessboard_t &board); 

chessboard_t from_fen(std::string);

chessboard_t new_chessboard();
