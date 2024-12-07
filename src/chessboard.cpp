#pragma once

#include "chessboard.h"
#include "utils.h"
#include "types_and_consts.h"

void chessboard_move(chessboard_t& board, int source, int dest) {
    for (std::size_t i = 0; i < board.bitboards.size(); i++) {
        int square_occupied = (board.bitboards[i] >> source) & 1;
        if (!square_occupied)
            continue;

        clear_bit(board.bitboards[i], source);
        set_bit(board.bitboards[i], dest);
        break;
    }
}

uint64_t all_white_pieces(chessboard_t &board) {
    return board.bitboards[white + pawns] |
        board.bitboards[white + knights] | 
        board.bitboards[white + elephants] | 
        board.bitboards[white + rooks] | 
        board.bitboards[white + ministers] | 
        board.bitboards[white + king];
} 

uint64_t all_black_pieces(chessboard_t &board) {
    return board.bitboards[black*6 + pawns] |
        board.bitboards[black*6 + knights] | 
        board.bitboards[black*6 + elephants] | 
        board.bitboards[black*6 + rooks] | 
        board.bitboards[black*6 + ministers] | 
        board.bitboards[black*6 + king];
} 

chessboard_t new_chessboard() {
    return (chessboard_t) {
        .bitboards = {
            0xFF00, // white pawns
            0x42, // white knights
            0x24, // white elephants
            0x81, // white rooks
            0x8, // white ministers 
            0x10, // white king
            0xFF000000000000, // black pawns
            0x4200000000000000, // black knights
            0x2400000000000000, // black elephants
            0x8100000000000000, // black rooks
            0x800000000000000, // black ministers
            0x1000000000000000, // black king
        },
    };
} 
