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