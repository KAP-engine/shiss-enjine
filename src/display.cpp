
#include <cstdint>
#include <iostream>
#include <array>

#include "display.h"
#include "chessboard.h"
#include "utils.h"

void print_bin(uint64_t n) {
    if (n > 1) {
        print_bin(n >> 1);
    }

    printf("%llu", n & 1);
}

void print_bitboard(uint64_t board) {
    std::array<std::string, 64> values;
    for (int i = 0; i < 64; i++) {
        values[i] = ((board >> i) & 1) == 1 ? "1" : "0";
    }

    print_board_layout(values);
}

void print_chessboard(chessboard_t board) {
    std::array<std::string, 64> values;
    for (int i = 0; i < 64; i++) {
        values[i] = piece_char_at(board, i);
    }

    print_board_layout(values);
}

void print_board_layout(std::array<std::string, 64> values) {
    std::cout << "\n";

    for (int rank = 7; rank >= 0; rank--) {
        std::cout << " " << rank + 1 << "  ";

        for (int file = 0; file < 8; file++) {
            int square = (rank * 8 + file);

            std::cout << values[square] << " ";  
        }

        std::cout << "\n";
    }
    
    std::cout << "\n    a b c d e f g h \n\n\n";
}
