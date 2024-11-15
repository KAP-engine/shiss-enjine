#include "console.h"

void parse_command(std::vector<std::string> cmd, uint64_t &board) {
    if (cmd[0] == "display") {
        print_bitboard(board);
    } else if (cmd[0] == "move") {
        int row_source = cmd[1][0]-'a';   
        int col_source = cmd[1][1]-'1';

        int row_destination = cmd[2][0] - 'a';
        int col_destination = cmd[2][1] - '1';

        board = clear_bit(board,to_index(row_source,col_source,8));
        board = set_bit(board,to_index(row_destination,col_destination,8));
    }
}
