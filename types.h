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
    Position from = {-1, -1};
    Position to = {-1, -1};
    char piece = ' ';
};