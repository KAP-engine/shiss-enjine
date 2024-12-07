#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>

#include "chessboard.h"
#include "display.h"
#include "utils.h"
#include "evaluation.h"
#include "console.h"

int main () {
    std::cout << "program started" << std::endl;

    chessboard_t board = new_chessboard();

    std::string input;
    do {
        getline(std::cin, input);
        parse_command(split_string(input), board);
    } while (input != "quit");

    return 0;
}

