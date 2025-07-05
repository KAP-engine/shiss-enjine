#include <string>

#include "console.h"
#include "chessboard.h"
#include "display.h"
#include "utils.h"

void error_print(std::string message) {
    std::cout << "\033[1;31m" << message << "\033[0m\n";
}

void warning_print(std::string message) {
    std::cout << "\033[1;33m" << message << "\033[0m\n";
}

void parse_command(std::vector<std::string> cmd, chessboard_t& board) {
    if (cmd[0] == "display") {
        print_chessboard(board);
    } else if (cmd[0] == "move") {
        uint32_t move = std::stoi(cmd[1]);

        move_error err = chessboard_make_move(board, move);

        switch (err) {
        case None:
            print_chessboard(board);
            break;

        case CannotCastle:
            error_print("invalid move: cannot castle");
            break;
        }
    } else if (cmd[0] == "move_gen") {
    } else {
        warning_print(std::string("unknown command: ") + cmd[0]);
    }
}

// else if (cmd[0] == "move") {
//     int row_source = cmd[1][0]-'a';   
//     int col_source = cmd[1][1]-'1';
//     int row_destination = cmd[1][2] - 'a';
//     int col_destination = cmd[1][3] - '1';

//     chessboard_direct_move(
//                     board, 
//                     to_index(row_source, col_source), 
//                     to_index(row_destination, col_destination)
//                 );
// }
