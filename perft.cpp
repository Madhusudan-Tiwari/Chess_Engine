#include<vector>
#include<iostream>
#include "move_generation.h"
#include "board.h"
#include "game_state.h"
using namespace std;

int perft(BoardState board, int depth)
{
    vector<Move> moves = generate_legal_moves(board);
    if(depth == 1) return moves.size();

    int count = 0;

    for(const auto &m : moves)
    {
        BoardState temp_board = board;

        update_castling_flags(temp_board, m.from, m.to, m.piece);
        
        make_move(temp_board, m);

        count += perft(temp_board, depth - 1);
    }
    return count;
}

int perft_divide(BoardState board, int depth)
{
    vector<Move> moves = generate_legal_moves(board);

    int total = 0;

    for(const auto &m : moves)
    {
        BoardState temp_board = board;

        make_move(temp_board, m);

        int nodes;
        if(depth == 1)
            nodes = 1;
        else
            nodes = perft(temp_board, depth - 1);

        total += nodes;

        cout << char('a' + m.from.col)
             << 8 - m.from.row
             << char('a' + m.to.col)
             << 8 - m.to.row
             << " : "
             << nodes
             << '\n';

    }

    cout << "Total = " << total << '\n';
    return total;
}

void run_perft(BoardState board, int depth)
{
    cout << "Perft Depth "
         << depth
         << " = "
         << perft_divide(board, depth)
         << '\n';
}