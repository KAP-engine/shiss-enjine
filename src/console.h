#pragma once

#include <string>

#include "chessboard.h"
#include "display.h"

// This function parses commands as its name suggests, you really need
// explanation for everything, grow some brain cells.
void parse_command(std::vector<std::string> cmd, chessboard_t &board);
