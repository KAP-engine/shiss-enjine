
#include <cstdint>
#include <vector>
#include <sstream>
#include <string>

#include "chessboard.h"

uint64_t set_bit(uint64_t board, int coordinate) {
    return board |= (1ULL << coordinate);
}

uint64_t clear_bit(uint64_t board, int coordinate) {
    return board & ~(1ULL << coordinate);
}

int to_index(int x,int y) {
    return x + y * 8;
}

char piece_char_at(chessboard_t& board, int square) {
    if ((board.white_pawns >> square) & 1)
        return 'P';
    if ((board.white_king>> square) & 1)
        return 'K';
    if ((board.white_ministers >> square) & 1)
        return 'Q';
    if ((board.white_rooks >> square) & 1)
        return 'R';
    if ((board.white_elephants >> square) & 1)
        return 'B';
    if ((board.white_knights >> square) & 1)
        return 'N';
    if ((board.black_pawns >> square) & 1)
        return 'p';
    if ((board.black_king>> square) & 1)
        return 'k';
    if ((board.black_ministers >> square) & 1)
        return 'q';
    if ((board.black_rooks >> square) & 1)
        return 'r';
    if ((board.black_elephants >> square) & 1) 
        return 'b';
    if ((board.black_knights >> square) & 1)
        return 'n';
    return 'b';
}

std::vector<std::string> split_string(const std::string& s) {
    std::vector<std::string> v;
    std::stringstream ss(s);
    std::string word;
    while (ss >> word) {
        v.push_back(word);
    }

    return v;
}

chessboard_t new_chessboard() {
    return (chessboard_t) {
        .white_pawns = 0x000000000000FF00,
        .white_king = 0x0000000000000010,
        .white_ministers = 0x8, 
        .white_rooks = 0x0000000000000081,
        .white_elephants = 0x0000000000000024, 
        .white_knights = 0x0000000000000042,
        .black_pawns = 0x00FF000000000000,
        .black_king = 0x1000000000000000,
        .black_ministers = 0x800000000000000, 
        .black_rooks = 0x8100000000000000,
        .black_elephants = 0x2400000000000000, 
        .black_knights = 0x4200000000000000,
    };
} 
