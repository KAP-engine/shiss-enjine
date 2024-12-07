#include "console.h"
#include "chessboard.h"
#include "utils.h"

void parse_command(std::vector<std::string> cmd, chessboard_t& board) {
    if (cmd[0] == "display") {
        print_chessboard(board);
    } else if (cmd[0] == "move") {
        int row_source = cmd[1][0]-'a';   
        int col_source = cmd[1][1]-'1';
        int row_destination = cmd[1][2] - 'a';
        int col_destination = cmd[1][3] - '1';

        chessboard_move(
                        board, 
                        to_index(row_source, col_source), 
                        to_index(row_destination, col_destination)
                    );
    }
}
