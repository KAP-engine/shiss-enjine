#pragma once

#include <cstdint>
#include <array>

// CHESSBOARD_T
typedef struct {
    // The order of the bit boards is as follows (capital letters are white pieces
    // and lowercase letters are black pieces):
    // P, N, B, R, Q, K
    // p, n, b, r, q, k
    // The least significant bit of a bit board represent the bottom left square of
    // the board.
    std::array<uint64_t, 12> bitboards;
    // 0 for white, 1 for black
    uint8_t active_side; 
    // For castling:
    // 0001 white short castle
    // 0010 white long castle
    // 0100 black short castle
    // 1000 black long castle
    uint8_t castling_rights;
} chessboard_t;

// MOVE_ERROR enum
typedef enum {
    None,
} move_error;

// This function moves a piece from a square to another, i (masmitish) used it
// for debugging and eventually grew emotionally attached to it, so i don't
// want to delete it.
void chessboard_direct_move(chessboard_t &, int source, int destination);

// This function takes an encoded move, processes it, and makes it.
move_error chessboard_make_move(chessboard_t& board, uint32_t move);

// These three functions return a bit board of which squares are full according
// to their names.
uint64_t all_white_pieces(chessboard_t &board); 
uint64_t all_black_pieces(chessboard_t &board); 
uint64_t all_pieces(chessboard_t &board); 

// This function constructs a chess board from a FEN string
// more about fen in:
// https://www.chess.com/terms/fen-chess
// https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
chessboard_t from_fen(std::string);

// This function returns a normal chess board, nothing special about it, its
// just a chess board, with the normal piece placement and the normal pieces,
// a standard chess board, not random chess not fisher chess, a completely and
// absolutely normaly normal chess board, trust me bro.
chessboard_t new_chessboard();
