#pragma once

int perft(
    char board[8][8],
    int depth,
    bool white_to_move
);

int perft_divide(
    char board[8][8],
    int depth,
    bool white_to_move
);

void run_perft(
    char board[8][8],
    int depth
);