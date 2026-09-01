#include <iostream>
#include <vector>
#include "utils.h"
#include "move_generation.h"
#include "evaluation.h"
#include "board.h"
#include "game_state.h"
#include "move_ordering.h"
using namespace std;

const int INF = 1000000000;
const int MATE_SCORE = 1000000;

int minimax(BoardState board, int depth, int alpha, int beta)
{
    if(depth == 0) return evaluate_position(board.board);

    vector<Move> legal_moves = generate_legal_moves(board);
    order_moves(legal_moves, board);

    if(legal_moves.empty())
    {
        Position king = find_king(board.board, board.whiteToMove);
        if(is_square_attacked(board.board, king, board.whiteToMove)) return board.whiteToMove ? -MATE_SCORE : MATE_SCORE;
        return 0;
    }

    int best_score = board.whiteToMove ? -INF : INF;
    

    for(const Move &move : legal_moves)
    {        
        BoardState temp_board = board;
        make_move(temp_board, move);  
        int score = minimax(temp_board, depth - 1, alpha, beta);

        if(board.whiteToMove)
        {
            best_score = max(score, best_score);
            alpha = max(best_score, alpha);
        }
        else
        {
            best_score = min(score, best_score);
            beta = min(beta, best_score);
        }

        if(alpha >= beta) break;
    }

    return best_score;
}

Move find_best_move(BoardState board, int depth)
{
    vector<Move> legal_moves = generate_legal_moves(board);
    order_moves(legal_moves, board);

    Move best_move = legal_moves[0];
    int best_score = board.whiteToMove? -1e9: 1e9;
    int alpha = -INF;
    int beta = INF;
    for(const Move& move: legal_moves)
    {
        BoardState temp_board = board;

        make_move(temp_board, move);
        int score = minimax(temp_board, depth - 1, alpha, beta);
        if (board.whiteToMove)
        {
            if (score > best_score)
            {
                best_score = score;
                best_move = move;
            }

            alpha = max(alpha, best_score);
        }
        else
        {
            if (score < best_score)
            {
                best_score = score;
                best_move = move;
            }

            beta = min(beta, best_score);
        }
        if (alpha >= beta) break;
    }
    return best_move;
}

