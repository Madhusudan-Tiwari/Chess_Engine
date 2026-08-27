#include<iostream>
using namespace std;
#include "setup.h"
#include "game.h"
#include "perft.h"

int main()
{
    char board[8][8];

    init_default_board(board);
    reset_game_state();

    play_game(board);
    // int a;
    // cin>>a;
    // run_perft(board, a);

    return 0;
}