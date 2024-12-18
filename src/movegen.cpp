#include <cstdint>
#include <iostream>
#include <math.h>

#include "movegen.h"
#include "utils.h"
#include "types_and_consts.h"

uint64_t compute_king(uint64_t king_loc, uint64_t own_side) { 
    uint64_t king_loc_clip_file_a = king_loc & ~MASK_FILE[file_a];
    uint64_t bitboard_clip_file_h = king_loc & ~MASK_FILE[file_h];

    uint64_t spot_1 = king_loc << 8; // top
    uint64_t spot_2 = bitboard_clip_file_h << 9; // top right
    uint64_t spot_3 = bitboard_clip_file_h << 1; // right
    uint64_t spot_4 = bitboard_clip_file_h >> 7; // bottom right
    uint64_t spot_5 = king_loc >> 8; // bottom 
    uint64_t spot_6 = king_loc_clip_file_a >> 9; // bottom left
    uint64_t spot_7 = king_loc_clip_file_a >> 1; // left
    uint64_t spot_8 = king_loc_clip_file_a << 7; // top left

    uint64_t king_moves = spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6
        | spot_7 | spot_8;

    uint64_t king_valid_moves = king_moves & ~own_side;

    return king_valid_moves;
}

uint64_t compute_knight(uint64_t knight_loc, uint64_t own_side) {
    uint64_t spot_1_8_mask = (~MASK_FILE[file_a] | MASK_FILE[file_b]);
    uint64_t spot_2_7_mask = ~MASK_FILE[file_a];
    uint64_t spot_3_6_mask = ~MASK_FILE[file_h];
    uint64_t spot_4_5_mask = (~MASK_FILE[file_g] | MASK_FILE[file_h]);

    uint64_t spot_1 = (knight_loc & spot_1_8_mask) << 6; // top left low
    uint64_t spot_2 = (knight_loc & spot_2_7_mask) << 15; // top left high
    uint64_t spot_3 = (knight_loc & spot_3_6_mask) << 17; // top right high
    uint64_t spot_4 = (knight_loc & spot_4_5_mask) << 10; // top right low
    uint64_t spot_5 = (knight_loc & spot_4_5_mask) >> 6; // bottom right high
    uint64_t spot_6 = (knight_loc & spot_3_6_mask) >> 15; // bottom right low
    uint64_t spot_7 = (knight_loc & spot_2_7_mask) >> 17; // bottom left low
    uint64_t spot_8 = (knight_loc & spot_1_8_mask) >> 10; // bottom left high

    uint64_t knight_moves = 
        spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6 | spot_7 | spot_8;
    

    uint64_t knight_valid_moves = knight_moves & ~own_side;

    return knight_valid_moves;
}

uint64_t compute_white_pawn(
    uint64_t pawn_loc, 
    uint64_t all_pieces, 
    uint64_t black_pieces
) {
    uint64_t pawn_one_step = (pawn_loc << 8) & ~all_pieces;
    uint64_t pawn_two_step = 
        ((pawn_one_step & MASK_RANK[rank_3]) << 8) & ~all_pieces;

    uint64_t pawn_right_attack = 
        ((pawn_loc & ~MASK_FILE[file_h]) << 9) & black_pieces;
    uint64_t pawn_left_attack = 
        ((pawn_loc & ~MASK_FILE[file_a]) << 7) & black_pieces;

    uint64_t pawn_valid_moves = 
        pawn_one_step | pawn_two_step | pawn_right_attack | pawn_left_attack;

    return pawn_valid_moves;
}

uint64_t compute_black_pawn(
    uint64_t pawn_loc, 
    uint64_t all_pieces, 
    uint64_t white_pieces
) {
    uint64_t pawn_one_step = (pawn_loc >> 8) & ~all_pieces;
    uint64_t pawn_two_step = 
        ((pawn_one_step & MASK_RANK[rank_6]) >> 8) & ~all_pieces;

    uint64_t pawn_right_attack = 
        ((pawn_loc & ~MASK_FILE[file_h]) >> 7) & white_pieces;
    uint64_t pawn_left_attack = 
        ((pawn_loc & ~MASK_FILE[file_a]) >> 9) & white_pieces;

    uint64_t pawn_valid_moves = 
        pawn_one_step | pawn_two_step | pawn_right_attack | pawn_left_attack;

    return pawn_valid_moves;
}

int first_set_bit(int n) {
    return log2(n & -n);
}

uint64_t compute_sliding_piece(
    int piece_type,
    uint64_t piece_loc, 
    uint64_t all_pieces,
    uint64_t own_side
) {

    uint64_t final_moves = 0;

    if (piece_type == rooks || piece_type == ministers) {
        size_t piece_loc_index = first_set_bit(piece_loc);

        uint64_t o = all_pieces;
        uint64_t s = piece_loc;

        uint64_t horizontal_moves = (
            (o - 2*s) ^ 
            reverse_bitboard(reverse_bitboard(o) - 2*reverse_bitboard(s))
        ) & MASK_RANK[(int)floor(piece_loc_index / 8)] & ~own_side; // flooring is automatic

        uint64_t m = MASK_FILE[piece_loc_index % 8];
        uint64_t vertical_moves = (
            ((o&m) - 2*s) ^ 
            reverse_bitboard(reverse_bitboard(o&m) - 2*reverse_bitboard(s))
        ) & m & ~own_side;


        final_moves |= horizontal_moves | vertical_moves;
    }

    if (piece_type == elephants || piece_type == ministers) {
        uint64_t diagonal_moves = 0;

        uint64_t antidiagonal_moves = 0;

        final_moves |= diagonal_moves | antidiagonal_moves;
    }

    
// (((o&m)-2s) ^ ((o&m)'-2s')') &m

    return final_moves;
}
