#pragma once

enum GameState
{
    NORMAL,
    CHECK,
    CHECKMATE,
    STALEMATE
};

struct Position
{
    int row;
    int col;
};

struct Move
{
    Position from = {};
    Position to = {};
    char piece = ' ';
    char promotion = '\0';
};

struct BoardState
{
    char board[8][8];
    bool whiteToMove;

    bool whiteKingMoved;
    bool blackKingMoved;

    bool whiteARookMoved;
    bool whiteHRookMoved;
    bool blackARookMoved;
    bool blackHRookMoved;

    Move lastmove;
};