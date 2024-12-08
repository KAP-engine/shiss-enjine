#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>

#include "chessboard.h"
#include "display.h"
#include "utils.h"
#include "evaluation.h"
#include "console.h"
#include "movegen.h"
#include "types_and_consts.h"

int main () {
    std::cout << "shiss enjine activated, glory to shisha" << std::endl;

    chessboard_t board = from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    print_bitboard(compute_king(board.bitboards[white+king], all_white_pieces(board)));

    std::string input;
    do {
        getline(std::cin, input);
        parse_command(split_string(input), board);
    } while (input != "quit");

    return 0;
}

