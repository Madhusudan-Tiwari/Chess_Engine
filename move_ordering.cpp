#include <iostream>
#include <vector>
#include <algorithm>
#include "types.h"


int piece_value(char piece)
{
    switch(tolower(piece))
    {
        case 'p': return 100;
        case 'n': return 320;
        case 'b': return 330;
        case 'r': return 500;
        case 'q': return 900;
        case 'k': return 10000;
    }

    return 0;
}

int move_score(const Move& move, BoardState& board)
{
    int score = 0;

    char attacker = board.board[move.from.row][move.from.col];
    char victim = board.board[move.to.row][move.to.col];

    if (victim != '.')
    {
        score += 10 * piece_value(victim);
        score -= piece_value(attacker);
    }

    if (move.promotion != '\0') score += 800;

    return score;
}

void order_moves(std::vector<Move>& legal_moves, BoardState& board)
{
    sort(legal_moves.begin(), legal_moves.end(),
    [&](const Move& a, const Move& b)
    {
        return move_score(a, board) > move_score(b, board);
    });
}