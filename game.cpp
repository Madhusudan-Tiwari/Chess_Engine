#include <iostream>
#include "game.h"
#include "board.h"
#include "game_state.h"
#include "move_generation.h"
#include "utils.h"
#include "search.h"
using namespace std;

void play_game(BoardState& board)
{
    print_board(board.board);
    
    while(true)
    {
        cout << (board.whiteToMove ? "White" : "Black")
             << " to move\n";

        pair<string,string> move = take_input();

        Position from = string_to_index(move.first);
        Position to = string_to_index(move.second);

        if(is_legal_move(board, from, to))
        {
            char piece = board.board[from.row][from.col];

            make_move(board, {from, to, piece});
        }
        else
        {
            cout << "Illegal Move\n";
            continue;
        }

        print_board(board.board);

        Move best_move = find_best_move(board, 1);
        cout<< best_move.from.row<< best_move.from.col<< " "<< best_move.to.row<< best_move.to.col;
        GameState state = check_game_state(board);

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