#include <iostream>
#include "game.h"
#include "board.h"
#include "game_state.h"
#include "move_generation.h"
#include "utils.h"
#include "globals.h"
#include "search.h"
using namespace std;

void play_game(char board[8][8])
{
    bool is_white_turn = true;

    print_board(board);
    
    while(true)
    {
        cout << (is_white_turn ? "White" : "Black")
             << " to move\n";

        pair<string,string> move = take_input();

        Position from = string_to_index(move.first);
        Position to = string_to_index(move.second);

        if(is_legal_move(board,from,to,is_white_turn))
        {
            char piece = board[from.row][from.col];

            update_castling_flags(from,to,piece);

            move_piece(board,from,to);

            lastmove.from = from;
            lastmove.to = to;
            lastmove.piece = piece;

            is_white_turn = !is_white_turn;
        }
        else
        {
            cout << "Illegal Move\n";
            continue;
        }

        print_board(board);

        Move best_move = find_best_move(board, is_white_turn, 1);
        cout<< best_move.from.row<< best_move.from.col<< " "<< best_move.to.row<< best_move.to.col;
        GameState state = check_game_state(board, is_white_turn);

        switch(state)
        {
            case CHECK:
                cout << "CHECK\n";
                break;

            case CHECKMATE:
                cout << "Checkmate!\n";
                return;

            case STALEMATE:
                cout << "Stalemate!\n";
                return;

            default:
                break;
        }
    }
}