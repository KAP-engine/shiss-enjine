
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
    evaluate_bitboard(chessboard.white_pawns, pawn,0) +
    evaluate_bitboard(chessboard.white_knights, knight,0) +
    evaluate_bitboard(chessboard.white_elephants, elephant,0) +
    evaluate_bitboard(chessboard.white_rooks, rook,0) +
    evaluate_bitboard(chessboard.white_ministers, queen,0) +
    evaluate_bitboard(chessboard.white_king, king,0); 

    blackAdvantage =
    evaluate_bitboard(chessboard.black_pawns, pawn, 0) +
    evaluate_bitboard(chessboard.black_knights, knight, 0) +
    evaluate_bitboard(chessboard.black_elephants, elephant, 0) +
    evaluate_bitboard(chessboard.black_rooks, rook, 0) +
    evaluate_bitboard(chessboard.black_ministers, queen, 0) +
    evaluate_bitboard(chessboard.black_king, king, 0);

    return whiteAdvantage-blackAdvantage;
}
