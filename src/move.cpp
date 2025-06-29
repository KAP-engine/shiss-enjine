#include <cstdint>

#include "move.h"

uint32_t new_move(
    int source, int target, int promotion_piece,
    uint8_t capture_flag, uint8_t double_pawn_move_flag,
    uint8_t en_passant_flag, int castling
) {
    return source | target << 6 | promotion_piece << 12 |
        capture_flag << 14 | double_pawn_move_flag << 15 |
        en_passant_flag << 16 | castling << 17;
}

uint8_t get_move_source(uint32_t move) {
    return (uint8_t)(move & MASK_SOURCE);
}

uint8_t get_move_target(uint32_t move) {
    return (move & MASK_TARGET) >> 6;
}

uint8_t get_move_promotion_type(uint32_t move) {
    return (move & MASK_PROMOTION_TYPE) >> 12;
}

bool is_move_capture(uint32_t move) {
    return (move & MASK_CAPTURE_FLAG) >> 14;
}

bool is_move_double_pawn_move(uint32_t move) {
    return (move & MASK_DOUBLE_PAWN_FLAG) >> 15;
}

bool is_move_en_passant(uint32_t move) {
    return (move & MASK_EN_PASSANT_FLAG) >> 16;
}

uint8_t get_move_castling(uint32_t move) {
    return (move & MASK_CASTLING) >> 17;
}

