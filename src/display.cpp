
#include <cstdint>
#include <iostream>

#include "display.h"

void print_bin(uint64_t n) {
    if (n > 1) {
        print_bin(n >> 1);
    }

    printf("%llu", n & 1);
}

void print_bitboard(uint64_t board) {
    std::cout << "\n";

    for (int rank = 7; rank >= 0; rank--) {
        std::cout << " " << rank + 1 << "  ";

        for (int file = 0; file < 8; file++) {
            int square = (rank * 8 + file);
            std::cout << ((board >> square) & 1) << " ";  
        }

        std::cout << "\n";
    }
    
    std::cout << "\n    a b c d e f g h \n\n\n";
}
