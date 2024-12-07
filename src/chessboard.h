#pragma once

#include <cstdint>
#include <array>

// CHESSBOARD_T
typedef struct {
    std::array<uint64_t, 12> bitboards;
} chessboard_t;

void chessboard_move(chessboard_t&, int source, int destination);

chessboard_t new_chessboard();
