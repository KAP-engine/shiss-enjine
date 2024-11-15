

// void parse_command(vector<string> cmd, uint64_t &board) {
//     if (cmd[0] == "display") {
//         print_bitboard(board);
//     } else if (cmd[0] == "move") {
//         int row_source = cmd[0][0]-'a';   
//         int col_source = cmd[0][1]-'1';

//         int row_destination = cmd[1][0] - 'a';
//         int col_destination = cmd[1][1] - '1';

//         board = clear_bit(board,static_cast<ChessCoordinate>(to_1D(row_source,col_source,8)));
//         board = set_bit(board,static_cast<ChessCoordinate>(to_1D(row_destination,col_destination,8)));
//     }
// }
