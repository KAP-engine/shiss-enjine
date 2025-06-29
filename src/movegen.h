#pragma once

#include <cstdint>

uint64_t compute_king(uint64_t king_loc, uint64_t own_side);
uint64_t compute_knight(uint64_t knight_loc, uint64_t own_side);
uint64_t compute_white_pawn(uint64_t pawn_loc, 
                            uint64_t all_pieces,
                            uint64_t black_pieces);
uint64_t compute_black_pawn(uint64_t pawn_loc, 
                            uint64_t all_pieces,
                            uint64_t white_pieces);
uint64_t compute_sliding_piece(int piece_type,
                               uint64_t piece_loc, 
                               uint64_t all_pieces,
                               uint64_t own_side);

