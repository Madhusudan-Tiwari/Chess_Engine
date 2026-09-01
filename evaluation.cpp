#include <iostream>
#include "evaluation.h"

const int PAWN_VALUE   = 100;
const int KNIGHT_VALUE = 320;
const int BISHOP_VALUE = 330;
const int ROOK_VALUE   = 500;
const int QUEEN_VALUE  = 900;

const int pawn_table[8][8] =
{
    {  0,   0,   0,   0,   0,   0,   0,   0 },
    { 50,  50,  50,  50,  50,  50,  50,  50 },
    { 10,  10,  20,  30,  30,  20,  10,  10 },
    {  5,   5,  10,  25,  25,  10,   5,   5 },
    {  0,   0,   0,  20,  20,   0,   0,   0 },
    {  5,  -5, -10,   0,   0, -10,  -5,   5 },
    {  5,  10,  10, -20, -20,  10,  10,   5 },
    {  0,   0,   0,   0,   0,   0,   0,   0 }
};

const int knight_table[8][8] =
{
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20,   0,   0,   0,   0, -20, -40},
    {-30,   0,  10,  15,  15,  10,   0, -30},
    {-30,   5,  15,  20,  20,  15,   5, -30},
    {-30,   0,  15,  20,  20,  15,   0, -30},
    {-30,   5,  10,  15,  15,  10,   5, -30},
    {-40, -20,   0,   5,   5,   0, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}
};

const int bishop_table[8][8] =
{
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10,   0,   0,   0,   0,   0,   0, -10},
    {-10,   0,   5,  10,  10,   5,   0, -10},
    {-10,   5,   5,  10,  10,   5,   5, -10},
    {-10,   0,  10,  10,  10,  10,   0, -10},
    {-10,  10,  10,  10,  10,  10,  10, -10},
    {-10,   5,   0,   0,   0,   0,   5, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20}
};

const int rook_table[8][8] =
{
    {  0,   0,   0,   5,   5,   0,   0,   0 },
    { -5,   0,   0,   0,   0,   0,   0,  -5 },
    { -5,   0,   0,   0,   0,   0,   0,  -5 },
    { -5,   0,   0,   0,   0,   0,   0,  -5 },
    { -5,   0,   0,   0,   0,   0,   0,  -5 },
    { -5,   0,   0,   0,   0,   0,   0,  -5 },
    {  5,  10,  10,  10,  10,  10,  10,   5 },
    {  0,   0,   0,   0,   0,   0,   0,   0 }
};

const int queen_table[8][8] =
{
    {-20, -10, -10,  -5,  -5, -10, -10, -20},
    {-10,   0,   0,   0,   0,   0,   0, -10},
    {-10,   0,   5,   5,   5,   5,   0, -10},
    { -5,   0,   5,   5,   5,   5,   0,  -5},
    {  0,   0,   5,   5,   5,   5,   0,  -5},
    {-10,   5,   5,   5,   5,   5,   5, -10},
    {-10,   0,   5,   0,   0,   0,   0, -10},
    {-20, -10, -10,  -5,  -5, -10, -10, -20}
};

const int king_table[8][8] =
{
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-20, -30, -30, -40, -40, -30, -30, -20},
    {-10, -20, -20, -20, -20, -20, -20, -10},
    { 20,  20,   0,   0,   0,   0,  20,  20},
    { 20,  30,  10,   0,   0,  10,  30,  20}
};

int piece_square_value(char piece, int row, int col)
{
    bool white = isupper(piece);

    if(!white) row = 7 - row;

    switch(tolower(piece))
    {
        case 'p': return pawn_table[row][col];
        case 'n': return knight_table[row][col];
        case 'b': return bishop_table[row][col];
        case 'r': return rook_table[row][col];
        case 'q': return queen_table[row][col];
        case 'k': return king_table[row][col];
    }

    return 0;
}

int evaluate_position(char board[8][8])
{
    int score = 0;
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            char piece = board[row][col];
            switch(piece)
            {
                case 'P': score += PAWN_VALUE; break;
                case 'N': score += KNIGHT_VALUE; break;
                case 'B': score += BISHOP_VALUE; break;
                case 'R': score += ROOK_VALUE; break;
                case 'Q': score += QUEEN_VALUE; break;

                case 'p': score -= PAWN_VALUE; break;
                case 'n': score -= KNIGHT_VALUE; break;
                case 'b': score -= BISHOP_VALUE; break;
                case 'r': score -= ROOK_VALUE; break;
                case 'q': score -= QUEEN_VALUE; break;
            }

            if(piece != '.')
            {
                int value = piece_square_value(piece, row, col);
                if(isupper(piece)) score += value;
                else score -= value;
            }
        }
    }
    return score;
}