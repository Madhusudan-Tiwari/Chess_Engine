#include<iostream>
#include "types.h"
#include "move_generation.h"
#include "globals.h"
using namespace std;

GameState check_game_state(char board[8][8], bool white_to_move)
{
    bool has_legal_move = true;
    for(int i = 0; i < 8 && !has_legal_move; i++)
    {
        for(int j = 0; j < 8 && !has_legal_move; j++)
        {
            char piece = board[i][j];
            if((white_to_move && isupper(piece)) || (!white_to_move && islower(piece)))
            {
                for(int k = 0; k < 8; k++)
                {
                    for(int l = 0; l < 8; l++)
                    {
                        if(is_legal_move(board, {i, j}, {k, l}, white_to_move))
                        {
                            has_legal_move = true;
                            break;
                        }
                    }
                    if(has_legal_move)break;
                }
            }
        }
    }

    Position king_pos = find_king(board, white_to_move);
    bool king_in_check = is_square_attacked(board, king_pos, white_to_move);

    if (has_legal_move)
    {
        return king_in_check ? CHECK : NORMAL;
    }
    else
    {
        return king_in_check ? CHECKMATE : STALEMATE;
    }
}

void update_castling_flags(Position from, Position to, char piece)
{
    if (piece == 'K') whiteKingMoved = true;
    if (piece == 'k') blackKingMoved = true;

    if (piece == 'R')
    {
        if (from.row == 7 && from.col == 0) whiteARookMoved = true;
        if (from.row == 7 && from.col == 7) whiteHRookMoved = true;
    }
    if (piece == 'r')
    {
        if (from.row == 0 && from.col == 0) blackARookMoved = true;
        if (from.row == 0 && from.col == 7) blackHRookMoved = true;
    }

    if (to.row == 7 && to.col == 0) whiteARookMoved = true;
    if (to.row == 7 && to.col == 7) whiteHRookMoved = true;
    if (to.row == 0 && to.col == 0) blackARookMoved = true;
    if (to.row == 0 && to.col == 7) blackHRookMoved = true;
}
