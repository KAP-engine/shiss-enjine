#pragma once

#include <cstdint>
#include <array>

// CHESSBOARD_T
// The order of the bit boards is as follows (capital letters are white pieces
// and lowercase letters are black pieces):
// P, N, B, R, Q, K
// p, n, b, r, q, k
// The least significant bit of a bit board represent the bottom left square of
// the board.
typedef struct {
    std::array<uint64_t, 12> bitboards;
} chessboard_t;

// This function moves a piece from a square to another, i (masmitish) used it
// for debugging and eventually grew emotionally attached to it, so i don't
// want to delete it.
void chessboard_direct_move(chessboard_t &, int source, int destination);

// This function takes an encoded move, processes it, and makes it.
void chessboard_make_move(chessboard_t& board, uint32_t move);

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
