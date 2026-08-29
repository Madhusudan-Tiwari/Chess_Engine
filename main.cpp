#include<iostream>
using namespace std;
#include "setup.h"
#include "game.h"
#include "perft.h"
#include "types.h"

int main()
{
    BoardState board;
    init_default_board(board);

    play_game(board);
    // int a;
    // cin>>a;
    // run_perft(board, a);

    return 0;
}