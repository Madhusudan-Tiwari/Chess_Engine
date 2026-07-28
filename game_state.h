#pragma once

#include "types.h"

GameState check_game_state(
    char board[8][8],
    bool white_to_move
);

void update_castling_flags(
    Position from,
    Position to,
    char piece
);