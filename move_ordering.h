#pragma once

#include <vector>
#include "types.h"

int piece_value(char piece);
int move_score(const Move& move, BoardState& board);
void order_moves(std::vector<Move>& legal_moves, BoardState& board);