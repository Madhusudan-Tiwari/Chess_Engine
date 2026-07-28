#pragma once

#include "types.h"

void move_piece(
    char board[8][8],
    Position from,
    Position to,
    char promotion_piece = '\0'
);

void print_board(char board[8][8]);