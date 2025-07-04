#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>

#include "chessboard.h"
#include "display.h"
#include "move.h"
#include "utils.h"
#include "evaluation.h"
#include "console.h"
#include "movegen.h"
#include "types_and_consts.h"

int main () {
    // print_bin(reverse_bitboard(0x26));
    // print_bitboard(0x0101010101010100);
    std::cout << "shiss enjine activated, glory to shisha" << std::endl;

    chessboard_t board = from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    // chessboard_t board = from_fen("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");

    // print_bitboard(compute_king(board.bitboards[white+king], all_white_pieces(board)));
    // print_bitboard(compute_knight(0x8000000, 0));
    // print_bitboard(compute_black_pawn(0x20000000000000, all_black_pieces(board), all_pieces(board)));
    // print_bitboard(compute_sliding_piece(ministers, 0x20000000, all_pieces(board), all_white_pieces(board)));

    // chessboard_make_move(board, new_move(3, 62, 0, 1, 0, 0, 0));
    // print_bitboard(board.bitboards[black*6+knights]);

    chessboard_make_move(board, new_move(0, 0, 0, 0, 0, 0, 0b10));

    std::string input;
    do {
        getline(std::cin, input);
        parse_command(split_string(input), board);
    } while (input != "quit");

    return 0;
}

