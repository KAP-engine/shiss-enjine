
#include <cstdint>

#include "types_and_consts.h"
#include "evaluation.h"
#include "chessboard.h"

int evaluate_bitboard(uint64_t board, int piece, int color) {
    int result = 0;
    for (int i = 0;i<64;i++) {
        if ((1ULL << i ) & board) {
            result += PIECE_VALUE_MULT[piece+color*6][i];
        }
    }
    return result;
}

int evaluate_board(chessboard_t chessboard) {
    int whiteAdvantage = 0;
    int blackAdvantage = 0;

    whiteAdvantage =
    evaluate_bitboard(chessboard.bitboards[white+pawns], pawns,0) +
    evaluate_bitboard(chessboard.bitboards[white+knights], knights,0) +
    evaluate_bitboard(chessboard.bitboards[white+elephants], elephants,0) +
    evaluate_bitboard(chessboard.bitboards[white+rooks], rooks,0) +
    evaluate_bitboard(chessboard.bitboards[white+ministers], ministers,0) +
    evaluate_bitboard(chessboard.bitboards[white+king], king,0); 

    blackAdvantage =
    evaluate_bitboard(chessboard.bitboards[black*6+pawns], pawns, 0) +
    evaluate_bitboard(chessboard.bitboards[black*6+knights], knights, 0) +
    evaluate_bitboard(chessboard.bitboards[black*6+elephants], elephants, 0) +
    evaluate_bitboard(chessboard.bitboards[black*6+rooks], rooks, 0) +
    evaluate_bitboard(chessboard.bitboards[black*6+ministers], ministers, 0) +
    evaluate_bitboard(chessboard.bitboards[black*6+king], king, 0);

    return whiteAdvantage-blackAdvantage;
}
