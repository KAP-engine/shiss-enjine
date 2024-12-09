
#include <cstdint>
#include <vector>
#include <sstream>
#include <string>

#include "chessboard.h"

void set_bit(uint64_t &board, int index) {
    board = board | (1ULL << index);
}

void clear_bit(uint64_t &board, int index) {
    board = board & ~(1ULL << index);
}

uint64_t set_bit_val(uint64_t board, int index) {
    return board | (1ULL << index);
}

uint64_t clear_bit_val(uint64_t board, int index) {
    return board & ~(1ULL << index);
}

int64_t reverse_bitboard(uint64_t bitboard) {
    uint64_t reversed = 0;
    for(int i = 0; i < 64; i++)
         reversed |= ((bitboard>>i) & 0b1)<<(63-i);
    return reversed;
}

int to_index(int x,int y) {
    return x + y * 8;
}

char piece_char_at(chessboard_t &board, int square_index) {
    for (std::size_t i = 0; i < board.bitboards.size(); i++) {
        int square_occupied = (board.bitboards[i] >> square_index) & 1;
        if (square_occupied) {
            switch (i) {
            case 0:
                return 'P';
            case 1:
                return 'N';
            case 2:
                return 'B';
            case 3:
                return 'R';
            case 4:
                return 'Q';
            case 5:
                return 'K';
            case 6:
                return 'p';
            case 7:
                return 'n';
            case 8:
                return 'b';
            case 9:
                return 'r';
            case 10:
                return 'q';
            case 11:
                return 'k';
            }
        }
    }

    return ' ';
}

std::vector<std::string> split_string(const std::string &s) {
    std::vector<std::string> v;
    std::stringstream ss(s);
    std::string word;
    while (ss >> word) {
        v.push_back(word);
    }
    return v;
}
