#include <iostream>
#include <vector>
#include "utils.h"
#include "move_generation.h"
#include "evaluation.h"
#include "board.h"
using namespace std;

int minimax(char board[8][8], bool white_to_move, int depth)
{
    if(depth == 0) return evaluate_position(board);

    vector<Move> legal_moves = generate_legal_moves(board, white_to_move);
    if(legal_moves.empty()) return evaluate_position(board);

    char temp_board[8][8];
    int best_score = white_to_move ? -1e9 : 1e9;
    

    for(Move move : legal_moves)
    {
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                temp_board[row][col] = board[row][col];

            }
        }
        
        move_piece(temp_board, move.from, move.to, move.promotion);
        int score = minimax(temp_board, !white_to_move, depth - 1);

        if(white_to_move) best_score = max(score, best_score);
        else best_score = min(score, best_score);
    }

    return best_score;
}

Move find_best_move(char board[8][8], bool white_to_move, int depth)
{
    vector<Move> legal_moves = generate_legal_moves(board, white_to_move);

    Move best_move = legal_moves[0];
    int best_score = white_to_move? -1e9: 1e9;

    for(Move move: legal_moves)
    {
        char temp_board[8][8];
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                temp_board[i][j] = board[i][j];
            }
        }
        move_piece(temp_board, move.from, move.to, move.promotion);
        int score = minimax(temp_board, !white_to_move, depth - 1);
        if(white_to_move && score > best_score)
        {
            best_move = move;
            best_score = score;
        }
        else if(!white_to_move && score < best_score)
        {
            best_move = move;
            best_score = score;
        }
    }
    return best_move;
}

