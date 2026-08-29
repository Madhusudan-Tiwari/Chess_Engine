#include "types.h"

void init_default_board(BoardState &state)
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
            state.board[i][j]=starting_board[i][j];
        }
    }

    state.lastmove = {};

    state.whiteToMove = true;
    
    state.whiteKingMoved = false;
    state.blackKingMoved = false;

    state.whiteARookMoved = false;
    state.whiteHRookMoved = false;

    state.blackARookMoved = false;
    state.blackHRookMoved = false;
}