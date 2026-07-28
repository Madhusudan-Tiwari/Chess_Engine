#pragma once

#include <vector>

#include "types.h"

bool is_path_clear(
    char board[8][8],
    Position from,
    Position to
);

bool is_square_attacked(
    char board[8][8],
    Position current,
    bool is_white
);

Position find_king(
    char board[8][8],
    bool is_white
);

bool is_legal_move(
    char board[8][8],
    Position from,
    Position to,
    bool is_white_turn
);

std::vector<Move> generate_legal_moves(
    char board[8][8],
    bool white_to_move
);