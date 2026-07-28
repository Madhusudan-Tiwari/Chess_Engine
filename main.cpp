#include<iostream>
#include<vector>
#include "perft.h"
#include "board.h"
using namespace std;

int main()
{
    char board[8][8] =
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
    print_board(board);

    bool is_white_turn = true;
    /* while(1)
    {
        pair<string, string> move =  take_input();
        Position from = string_to_index(move.first);
        Position to = string_to_index(move.second);
        if(is_legal_move(board, from, to, is_white_turn))
        {
            char piece = board[from.row][from.col];
            update_castling_flags(from, to, piece);            
            move_piece(board, from, to);
            is_white_turn = !is_white_turn;
            lastmove.from = from;
            lastmove.piece = piece;
            lastmove.to = to;
        }
        else cout<<"Illegal Move \n";
        print_board(board);
        GameState state = check_game_state(board, is_white_turn);

        if(state == CHECKMATE)
        {
            cout<<"Checkmate Game Over"<<"\n";
            break;
        }
        else if(state == STALEMATE)
        {
            cout<<"STALEMATE It's a DRAW"<<"\n";
            break;
        }
        else if(state == CHECK)
        {
            cout<<"CHECK"<<"\n";
        }
    }*/

    int count = perft_divide(board, 2, true);
    cout<<count;

    return 0;

}