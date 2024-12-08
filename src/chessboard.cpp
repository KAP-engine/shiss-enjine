#pragma once

#include <cctype>
#include <iostream>
#include <ctype.h>
#include <math.h>

#include "chessboard.h"
#include "display.h"
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

chessboard_t from_fen(std::string fen) {

    // TODO: VERIFY THE STRING WITH REGEX
    
    std::vector<std::string> partitions;
    size_t start = 0;
    size_t end = fen.find(" ");

    while (end != std::string::npos) {
        partitions.push_back(fen.substr(start, end - start));
        start = end + 1;
        end = fen.find(" ", start);
    }

    partitions.push_back(fen.substr(start));    

    chessboard_t board;
    for (size_t i = 0; i < board.bitboards.size(); i++) {
        board.bitboards[i] = 0;
    }

    size_t index = 0;
    size_t row = 0;
    for (size_t i = 0; i < partitions[0].length(); i++) {
        char current_char = partitions[0][i];

        if (current_char == '/') {
            row += 1;
            index = row * 8;
            continue;
        }

        if (std::isdigit(current_char)) {
            int empty_squares = current_char - '0';
            index += empty_squares;
            continue;
        }

        size_t bitboard_index = 0;

        if (std::islower(current_char)) {
            bitboard_index += 6;
        }

        current_char = tolower(current_char);
       
        switch (current_char) {
        case 'p':
            bitboard_index += 0;
            break;
        case 'n':
            bitboard_index += 1;
            break;
        case 'b':
            bitboard_index += 2;
            break;
        case 'r':
            bitboard_index += 3;
            break;
        case 'q':
            bitboard_index += 4;
            break;
        case 'k':
            bitboard_index += 5;
            break;
        }

        int x = index % 8;
        int y = 7 - floor(index / 8);
        size_t shifting_value = y*8 + x;

        board.bitboards[bitboard_index] |= (1ULL << shifting_value);

        index++;
    }

    return board;
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
