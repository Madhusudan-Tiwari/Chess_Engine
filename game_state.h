#pragma once

#include "types.h"

GameState check_game_state(BoardState& board);

void update_castling_flags(
    BoardState& board,
    Position from,
    Position to,
    char piece
);