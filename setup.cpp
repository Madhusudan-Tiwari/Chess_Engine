#include "globals.h"

void init_default_board(char board[8][8])
{
    char starting_board[8][8] =
    {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            board[i][j]=starting_board[i][j];
        }
    }
}

void reset_game_state()
{
    lastmove = {};

    whiteKingMoved = false;
    blackKingMoved = false;

    whiteARookMoved = false;
    whiteHRookMoved = false;

    blackARookMoved = false;
    blackHRookMoved = false;
}