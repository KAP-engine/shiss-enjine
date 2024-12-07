#include <cstdint>

#include "movegen.h"
#include "types_and_consts.h"

uint64_t compute_king(uint64_t bitboard, uint64_t own_side) { 
    uint64_t bitboard_clip_file_a = bitboard & ~MASK_FILE[file_a];
    uint64_t bitboard_clip_file_h = bitboard & ~MASK_FILE[file_h];

    uint64_t spot_1 = bitboard_clip_file_a << 9; // top left
    uint64_t spot_2 = bitboard << 8; // top
    uint64_t spot_3 = bitboard_clip_file_h << 7; // top right
    uint64_t spot_4 = bitboard_clip_file_h >> 1; // right
    uint64_t spot_5 = bitboard_clip_file_h >> 9; // bottom right
    uint64_t spot_6 = bitboard << 8; // bottom
    uint64_t spot_7 = bitboard_clip_file_a >> 7; // bottom left
    uint64_t spot_8 = bitboard_clip_file_a << 1; // left

    uint64_t king_moves = spot_1 | spot_2 | spot_3 | spot_4 | spot_5 | spot_6
        | spot_7 | spot_8;

    uint64_t king_valid_moves = king_moves & own_side;

    return king_valid_moves;
}
