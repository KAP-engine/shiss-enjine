#include <_types/_uint64_t.h>
#include <bitset>
#include <math.h>
#include <string>

#include "chessboard.h"
#include "display.h"
#include "movegen.h"
#include "utils.h"
#include "move.h"
#include "types_and_consts.h"

void chessboard_direct_move(chessboard_t& board, int source, int target) {
    for (std::size_t i = 0; i < board.bitboards.size(); i++) {
        int square_occupied = (board.bitboards[i] >> source) & 1;
        if (!square_occupied)
            continue;

        clear_bit(board.bitboards[i], source);
        set_bit(board.bitboards[i], target);
        break;
    }
}

move_error chessboard_make_move(chessboard_t& board, uint32_t move) {
    uint8_t source = get_move_source(move); 
    uint8_t target = get_move_target(move);

    // castling
    uint8_t castling_type = get_move_castling(move);
    if (castling_type != 0b00 || castling_type != 0b11) {
        uint8_t side = board.active_side;

        if (can_castle(board, side, castling_type)) {
            if (castling_type == SHORT_CASTLE) {
                uint64_t new_king_bitboard = 1ULL << (side*56+6);
                board.bitboards[side*6+king] = new_king_bitboard;

                uint64_t& rook_bitboard = board.bitboards[side*6+rooks]; 
                clear_bit(rook_bitboard, side*56+7);
                set_bit(rook_bitboard, side*56+5);
            } else if (castling_type == LONG_CASTLE) {
                uint64_t new_king_bitboard = 1ULL << (side*56+2);
                board.bitboards[side*6+king] = new_king_bitboard;

                uint64_t& rook_bitboard = board.bitboards[side*6+rooks]; 
                clear_bit(rook_bitboard, side*56+0);
                set_bit(rook_bitboard, side*56+3);
            }

            // edit castling rights
            
            board.castling_rights = board.castling_rights & ~(1ULL << (side*2 + castling_type - 1));
            std::cout << std::bitset<4>(1ULL << (side*2 + castling_type -1)) << "\n";

            return None;
        }
    }
    
    // clear captured square
    bool is_capture = is_move_capture(move);
    if (is_capture) {
        for (std::size_t i = 0; i < board.bitboards.size(); i++) {
            bool square_occupied = (board.bitboards[i] >> target) & 1;
            if (!square_occupied) {
                continue;
            }

            clear_bit(board.bitboards[i], target);
            break;
        }
    }

    // move piece
    for (std::size_t i = 0; i < board.bitboards.size(); i++) {
        bool square_occupied = (board.bitboards[i] >> source) & 1;
        if (!square_occupied) {
            continue;
        }

        clear_bit(board.bitboards[i], source);
        set_bit(board.bitboards[i], target);
        break;
    }

    // handle promotion

    return None;
}

uint64_t all_white_pieces(chessboard_t &board) {
    return board.bitboards[white + pawns] |
        board.bitboards[white + knights] | 
        board.bitboards[white + elephants] | 
        board.bitboards[white + rooks] | 
        board.bitboards[white + ministers] | 
        board.bitboards[white + king];
} 

uint64_t all_black_pieces(chessboard_t &board) {
    return board.bitboards[black*6 + pawns] |
        board.bitboards[black*6 + knights] | 
        board.bitboards[black*6 + elephants] | 
        board.bitboards[black*6 + rooks] | 
        board.bitboards[black*6 + ministers] | 
        board.bitboards[black*6 + king];
} 

uint64_t all_pieces(chessboard_t &board) {
    return board.bitboards[white + pawns] |
        board.bitboards[white + knights] | 
        board.bitboards[white + elephants] | 
        board.bitboards[white + rooks] | 
        board.bitboards[white + ministers] | 
        board.bitboards[white + king] |
        board.bitboards[black*6 + pawns] |
        board.bitboards[black*6 + knights] | 
        board.bitboards[black*6 + elephants] | 
        board.bitboards[black*6 + rooks] | 
        board.bitboards[black*6 + ministers] | 
        board.bitboards[black*6 + king];
} 

chessboard_t from_fen(std::string fen) {

    // TODO: VERIFY THE STRING WITH REGEX
    
    std::vector<std::string> partitions;
    size_t start = 0;
    size_t end = fen.find(" ");

    while (end != std::string::npos) {
        partitions.push_back(fen.substr(start, end - start));
        start = end + 1;
        end = fen.find(" ", start);
    }

    partitions.push_back(fen.substr(start));    

    chessboard_t board;

    // setting up the active side
    board.active_side = 0;
    if (partitions[1] == "w" || partitions[1] == "W") {
        board.active_side = white;
    } else if (partitions[1] == "b" || partitions[1] == "B") {
        board.active_side = black;
    }

    // setting up castling rights
    board.castling_rights = 0;
    if (partitions[2].find("K") != std::string::npos) {
        board.castling_rights |= CASTLING_WHITE_SHORT;
    }
    if (partitions[2].find("Q") != std::string::npos) {
        board.castling_rights |= CASTLING_WHITE_LONG;
    }
    if (partitions[2].find("k") != std::string::npos) {
        board.castling_rights |= CASTLING_BLACK_SHORT;
    }
    if (partitions[2].find("q") != std::string::npos) {
        board.castling_rights |= CASTLING_BLACK_LONG;
    }

    // setting up bit boards
    for (size_t i = 0; i < board.bitboards.size(); i++) {
        board.bitboards[i] = 0;
    }

    size_t index = 0;
    size_t row = 0;
    for (size_t i = 0; i < partitions[0].length(); i++) {
        char current_char = partitions[0][i];

        if (current_char == '/') {
            row += 1;
            index = row * 8;
            continue;
        }

        if (std::isdigit(current_char)) {
            int empty_squares = current_char - '0';
            index += empty_squares;
            continue;
        }

        size_t bitboard_index = 0;

        if (std::islower(current_char)) {
            bitboard_index += 6;
        }

        current_char = tolower(current_char);
       
        switch (current_char) {
        case 'p':
            bitboard_index += 0;
            break;
        case 'n':
            bitboard_index += 1;
            break;
        case 'b':
            bitboard_index += 2;
            break;
        case 'r':
            bitboard_index += 3;
            break;
        case 'q':
            bitboard_index += 4;
            break;
        case 'k':
            bitboard_index += 5;
            break;
        }

        int x = index % 8;
        int y = 7 - floor(index / 8);
        size_t shifting_value = y*8 + x;

        board.bitboards[bitboard_index] |= (1ULL << shifting_value);

        index++;
    }

    return board;
}

chessboard_t new_chessboard() {
    return (chessboard_t) {
        .bitboards = {
            0xFF00, // white pawns
            0x42, // white knights
            0x24, // white elephants
            0x81, // white rooks
            0x8, // white ministers 
            0x10, // white king
            0xFF000000000000, // black pawns
            0x4200000000000000, // black knights
            0x2400000000000000, // black elephants
            0x8100000000000000, // black rooks
            0x800000000000000, // black ministers
            0x1000000000000000, // black king
        },
        .active_side = 0,
        .castling_rights = 0b1111,
    };
} 
