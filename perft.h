#pragma once

int perft(
    BoardState board,
    int depth
);

int perft_divide(
    BoardState board,
    int depth
);

void run_perft(
    BoardState board,
    int depth
);