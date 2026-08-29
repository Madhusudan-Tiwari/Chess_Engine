#include <iostream>
#include <vector>
#include "utils.h"
#include "move_generation.h"
#include "evaluation.h"
#include "board.h"
#include "game_state.h"
using namespace std;

int minimax(BoardState board, int depth)
{
    if(depth == 0) return evaluate_position(board.board);

    vector<Move> legal_moves = generate_legal_moves(board);
    if(legal_moves.empty()) return evaluate_position(board.board);

    int best_score = board.whiteToMove ? -1e9 : 1e9;
    

    for(Move move : legal_moves)
    {        
        BoardState temp_board = board;
        make_move(temp_board, move);  
        int score = minimax(temp_board, depth - 1);

        if(board.whiteToMove) best_score = max(score, best_score);
        else best_score = min(score, best_score);
    }

    return best_score;
}

Move find_best_move(BoardState board, int depth)
{
    vector<Move> legal_moves = generate_legal_moves(board);

    Move best_move = legal_moves[0];
    int best_score = board.whiteToMove? -1e9: 1e9;

    for(Move move: legal_moves)
    {
        BoardState temp_board = board;

        make_move(temp_board, move);
        int score = minimax(temp_board, depth - 1);
        if(board.whiteToMove && score > best_score)
        {
            best_move = move;
            best_score = score;
        }
        else if(!board.whiteToMove && score < best_score)
        {
            best_move = move;
            best_score = score;
        }
    }
    return best_move;
}

