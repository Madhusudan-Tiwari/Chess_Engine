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
        Move best_move;
        if(board.whiteToMove) best_move = find_best_move(board, 5);
        else best_move = find_best_move(board, 2);

        cout << index_to_string(best_move.from)<< " "<< index_to_string(best_move.to)<< '\n';
        Move move = best_move;

        //pair<string,string> move = take_input();

        //Position from = string_to_index(move.first);
        //Position to = string_to_index(move.second);

        if(is_legal_move(board, move.from, move.to))
        {
            char piece = board.board[move.from.row][move.from.col];

            make_move(board, {move.from, move.to, piece});
        }
        else
        {
            cout << "Illegal Move\n";
            continue;
        }

        print_board(board.board);

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