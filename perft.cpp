#include<vector>
#include<iostream>
#include "move_generation.h"
#include "globals.h"
#include "board.h"
#include "game_state.h"
using namespace std;

int perft(char board[8][8], int depth, bool white_to_move)
{
    vector<Move> moves = generate_legal_moves(board, white_to_move);
    if(depth == 1) return moves.size();

    int count = 0;

    for(const auto &m : moves)
    {
        char temp_board[8][8];
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                temp_board[i][j] = board[i][j];
            }
        }

        Move prev_lastmove = lastmove;
        bool wKM = whiteKingMoved, bKM = blackKingMoved;
        bool wHRM = whiteHRookMoved, wARM = whiteARookMoved;
        bool bHRM = blackHRookMoved, bARM = blackARookMoved;
        lastmove = m;

        update_castling_flags(m.from, m.to, m.piece);
        
        move_piece(temp_board, m.from, m.to, 'q');
        count += perft(temp_board, depth - 1, !white_to_move);

        lastmove = prev_lastmove;
        whiteKingMoved = wKM; blackKingMoved = bKM;
        whiteHRookMoved = wHRM; whiteARookMoved = wARM;
        blackHRookMoved = bHRM; blackARookMoved = bARM;
    }
    return count;
}

int perft_divide(char board[8][8], int depth, bool white_to_move)
{
    vector<Move> moves = generate_legal_moves(board, white_to_move);

    int total = 0;

    for(const auto &m : moves)
    {
        char temp_board[8][8];
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                temp_board[i][j] = board[i][j];

        Move prev_lastmove = lastmove;
        bool wKM = whiteKingMoved, bKM = blackKingMoved;
        bool wHRM = whiteHRookMoved, wARM = whiteARookMoved;
        bool bHRM = blackHRookMoved, bARM = blackARookMoved;

        lastmove = m;
        update_castling_flags(m.from, m.to, m.piece);
        move_piece(temp_board, m.from, m.to, m.promotion);

        int nodes;
        if(depth == 1)
            nodes = 1;
        else
            nodes = perft(temp_board, depth - 1, !white_to_move);

        total += nodes;

        cout << char('a' + m.from.col)
             << 8 - m.from.row
             << char('a' + m.to.col)
             << 8 - m.to.row
             << " : "
             << nodes
             << '\n';

        lastmove = prev_lastmove;
        whiteKingMoved = wKM;
        blackKingMoved = bKM;
        whiteHRookMoved = wHRM;
        whiteARookMoved = wARM;
        blackHRookMoved = bHRM;
        blackARookMoved = bARM;
    }

    cout << "Total = " << total << '\n';
    return total;
}

void run_perft(char board[8][8],int depth)
{
    cout << "Perft Depth "
         << depth
         << " = "
         << perft_divide(board,depth,true)
         << '\n';
}