#pragma once

#include <string>
#include <utility>

#include "types.h"

bool valid_square(std::string pos);

std::pair<std::string, std::string> take_input();

Position string_to_index(std::string pos);
std::string index_to_string(Position pos);

bool inside(int row, int col);