#pragma once

#include <cstdint>

const uint32_t MASK_SOURCE  = 0b111111;
const uint32_t MASK_TARGET = 0b111111 << 6;
const uint32_t MASK_PROMOTION_TYPE = 0b11 << 12;
const uint32_t MASK_CAPTURE_FLAG = 1 << 14;
const uint32_t MASK_DOUBLE_PAWN_FLAG = 1 << 15;
const uint32_t MASK_EN_PASSANT_FLAG = 1 << 16;
const uint32_t MASK_CASTLING = 0b11 << 17;

// MOVE ENCODING
// 0000 0000 0000 0011 1111 source square index (6)
// 0000 0000 1111 1100 0000 target square index (6)
// 0000 0011 0000 0000 0000 promotion piece type (2)
// 0000 0100 0000 0000 0000 capture flag (1)
// 0000 1000 0000 0000 0000 double pawn move flag (1)
// 0001 0000 0000 0000 0000 en passant flag (1)
// 0110 0000 0000 0000 0000 castling type (2)
// As for promotion, 00 represents promotion to a minister, 01 to a knight,
// 10 to an elephant and 11 to a rook.
// And for castling, 00 and 11 means that this is not a castling move, 01 that
// it is a short castling and 10 that it is a long castle.

// This function constructs a move from it's parameters.
uint32_t new_move(int source, int target, int promotion_type, uint8_t capture_flag,
                  uint8_t double_pawn_move_flag, uint8_t en_passant_flag, int castling);

// These functions serve to decode a move.
uint8_t get_move_source(uint32_t move);
uint8_t get_move_target(uint32_t move);
uint8_t get_move_promotion_type(uint32_t move);
bool is_move_capture(uint32_t move);
bool is_move_double_pawn_move(uint32_t move);
bool is_move_en_passant(uint32_t move);
uint8_t get_move_castling(uint32_t move);
