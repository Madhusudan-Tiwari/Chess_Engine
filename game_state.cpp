#include<iostream>
#include "types.h"
#include "move_generation.h"
using namespace std;

GameState check_game_state(BoardState& board)
{
    bool has_legal_move = false;
    for(int i = 0; i < 8 && !has_legal_move; i++)
    {
        for(int j = 0; j < 8 && !has_legal_move; j++)
        {
            char piece = board.board[i][j];
            if((board.whiteToMove && isupper(piece)) || (!board.whiteToMove && islower(piece)))
            {
                for(int k = 0; k < 8; k++)
                {
                    for(int l = 0; l < 8; l++)
                    {
                        if(is_legal_move(board, {i, j}, {k, l}))
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

    Position king_pos = find_king(board.board, board.whiteToMove);
    bool king_in_check = is_square_attacked(board.board, king_pos, board.whiteToMove);

    if (has_legal_move)
    {
        return king_in_check ? CHECK : NORMAL;
    }
    else
    {
        return king_in_check ? CHECKMATE : STALEMATE;
    }
}

void update_castling_flags(BoardState& board, Position from, Position to, char piece)
{
    if (piece == 'K') board.whiteKingMoved = true;
    if (piece == 'k') board.blackKingMoved = true;

    if (piece == 'R')
    {
        if (from.row == 7 && from.col == 0) board.whiteARookMoved = true;
        if (from.row == 7 && from.col == 7) board.whiteHRookMoved = true;
    }
    if (piece == 'r')
    {
        if (from.row == 0 && from.col == 0) board.blackARookMoved = true;
        if (from.row == 0 && from.col == 7) board.blackHRookMoved = true;
    }

    if (to.row == 7 && to.col == 0) board.whiteARookMoved = true;
    if (to.row == 7 && to.col == 7) board.whiteHRookMoved = true;
    if (to.row == 0 && to.col == 0) board.blackARookMoved = true;
    if (to.row == 0 && to.col == 7) board.blackHRookMoved = true;
}
