#pragma once

#include "chessboard.h"
#include "display.h"
#include <string>
#include <vector>

void parse_command(std::vector<std::string> cmd, chessboard_t &board);
