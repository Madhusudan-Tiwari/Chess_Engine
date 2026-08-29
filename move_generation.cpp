#include<iostream>
#include "utils.h"
#include "types.h"
#include "board.h"
#include<vector>
using namespace std;

bool is_path_clear(char board[8][8], Position from, Position to)
{
    int dr = 0;
    int dc = 0;
    if(to.col < from.col) dc = -1;
    else if(to.col > from.col) dc = 1;
    if(to.row < from.row) dr = -1;
    else if(to.row > from.row) dr = 1;
    int curr_row = from.row + dr;
    int curr_col = from.col + dc;
    while(curr_row != to.row || curr_col != to.col)
    {
        if(board[curr_row][curr_col] != '.')return false;
        if(dr != 0) curr_row += dr;
        if(dc != 0) curr_col += dc;
    }
    return true;
}


bool is_square_attacked(char board[8][8], Position current, bool is_white)
{
    int knight_row[] = {-2,-2,-1,-1,1,1,2,2};
    int knight_col[] = {-1,1,-2,2,-2,2,-1,1};
    for(int k = 0; k < 8; k++)
    {
        int row = current.row + knight_row[k];
        int col = current.col + knight_col[k];
        if(inside(row, col))
        {
            if(is_white && board[row][col] == 'n')return true;
            if(!is_white && board[row][col] == 'N')return true;
        }
    }

    int king_row[] = {-1,-1,-1,0,0,1,1,1};
    int king_col[] = {-1,0,1,-1,1,-1,0,1};
    for(int k = 0; k < 8; k++)
    {
        int row = current.row + king_row[k];
        int col = current.col + king_col[k];
        if(inside(row, col))
        {
            if(is_white && board[row][col] == 'k')return true;
            if(!is_white && board[row][col] == 'K')return true;
        }
    }


    if(is_white)
    {
        if(inside(current.row - 1, current.col - 1) && board[current.row - 1][current.col - 1] == 'p') return true;
        if(inside(current.row - 1, current.col + 1) && board[current.row - 1][current.col + 1] == 'p') return true;
    }
    else
    {
        if(inside(current.row + 1, current.col - 1) && board[current.row + 1][current.col - 1] == 'P') return true;
        if(inside(current.row + 1, current.col + 1) && board[current.row + 1][current.col + 1] == 'P') return true;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for(int i = 0; i < 4; i++)
    {
        int row = current.row + dr[i];
        int col = current.col + dc[i];

        while(inside(row, col))
        {
            if(board[row][col] == '.')
            {
                row += dr[i];
                col += dc[i];
                continue;
            }

            if(is_white)
            {
                if(board[row][col] == 'r' || board[row][col] == 'q')
                    return true;
            }
            else
            {
                if(board[row][col] == 'R' || board[row][col] == 'Q')
                    return true;
            }
            break;
        }
    }


    int bishop_dr[] = {-1,-1,1,1};
    int bishop_dc[] = {-1,1,-1,1};
    for(int i = 0; i < 4; i++)
    {
        int row = current.row + bishop_dr[i];
        int col = current.col + bishop_dc[i];

        while(inside(row, col))
        {
            if(board[row][col] == '.')
            {
                row += bishop_dr[i];
                col += bishop_dc[i];
                continue;
            }

            if(is_white)
            {
                if(board[row][col] == 'b' || board[row][col] == 'q')
                    return true;
            }
            else
            {
                if(board[row][col] == 'B' || board[row][col] == 'Q')
                    return true;
            }
            break;
        }
    }

    return false;
}

Position find_king(char board[8][8], bool is_white)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(is_white && board[i][j] == 'K') return {i, j};
            else if(!is_white && board[i][j] == 'k') return{i, j};
        }
    }

    return {-1,-1};
}

bool is_legal_move(BoardState& board, Position from, Position to)
{
    if(from.row == to.row && from.col == to.col) return false;
    char piece = board.board[from.row][from.col];
    if(piece == '.')return false;

    int row_diff = abs(to.row - from.row);
    int col_diff = abs(to.col-from.col);
    char target = board.board[to.row][to.col];

    if (board.whiteToMove)
    {
        if (!isupper(piece)) return false;
        if (isupper(target)) return false;
    }
    else
    {
        if (!islower(piece)) return false;
        if (islower(target)) return false;
    }
    
    
    switch(piece)
    {
        case 'P':
            if(col_diff == 0)
            {
                if(target != '.')return false;
                if(from.row == 6)
                {
                    if(to.row != 4 && to.row != 5) return false;
                    if(to.row == 4 && board.board[5][to.col] != '.')return false;
                }
                else 
                {
                    if(to.row - from.row != -1) return false;
                }
            }
            else if(col_diff == 1)
            {
                if(target == '.') if(board.lastmove.from.row != 1 || board.lastmove.to.row != 3 || board.lastmove.to.col != to.col || from.row != 3 || board.lastmove.piece != 'p') return false;
                if(to.row - from.row != -1)return false;
            }
            else return false;
            break;

        case 'p':
            if(col_diff == 0)
            {
                if(target != '.')return false;
                if(from.row == 1)
                {
                    if(to.row != 2 && to.row != 3) return false;
                    if(to.row == 3 && board.board[2][to.col] != '.')return false;
                }
                else 
                {
                    if(to.row - from.row != 1) return false;
                }
            }
            else if(col_diff == 1)
            {
                if(target == '.') if(board.lastmove.from.row != 6 || board.lastmove.to.row != 4 || board.lastmove.to.col != to.col || from.row != 4 || board.lastmove.piece != 'P') return false;
                if(to.row - from.row != 1)return false;
            }
            else return false;
            break;  

        case 'N':
        case 'n':
            if (!((row_diff == 1 && col_diff == 2) || (row_diff == 2 && col_diff == 1)))return false;
            break;

        case 'k':
        case 'K':
            if(row_diff > 1 || col_diff > 2) return false;
            if(col_diff == 2)
            {
                if(row_diff != 0) return false;
                if(board.whiteToMove && board.whiteKingMoved || !board.whiteToMove && board.blackKingMoved)return false;
                if(to.col > from.col)
                {
                    if (board.whiteToMove && board.whiteHRookMoved || !board.whiteToMove && board.blackHRookMoved) return false;
                    if (board.board[from.row][5] != '.' || board.board[from.row][6] != '.') return false;

                    if (is_square_attacked(board.board, {from.row, 4}, board.whiteToMove) ||
                        is_square_attacked(board.board, {from.row, 5}, board.whiteToMove) ||
                        is_square_attacked(board.board, {from.row, 6}, board.whiteToMove))
                        return false;
                }
                else
                {
                    
                    if (board.whiteToMove && board.whiteARookMoved || !board.whiteToMove && board.blackARookMoved) return false;
                    if (board.board[from.row][1] != '.' || board.board[from.row][2] != '.' || board.board[from.row][3] != '.') return false;

                    if (is_square_attacked(board.board, {from.row, 4}, board.whiteToMove) ||
                        is_square_attacked(board.board, {from.row, 3}, board.whiteToMove) ||
                        is_square_attacked(board.board, {from.row, 2}, board.whiteToMove))
                        return false;
                }
            }
            break;

        case 'r':
        case 'R':
            if(row_diff != 0 && col_diff != 0) return false;
            if(!is_path_clear(board.board, from, to)) return false;
            break;

        case 'b':
        case 'B':
            if(row_diff != col_diff) return false;
            if(!is_path_clear(board.board, from, to)) return false;
            break;

        case 'q':
        case 'Q':
            if(row_diff != col_diff && row_diff != 0 && col_diff != 0) return false;
            if(!is_path_clear(board.board, from, to)) return false;
            break;

        default:
            return false;
    }

    BoardState temp_board = board;

    make_move(temp_board, {from, to, piece, 'q'});

    Position king = find_king(temp_board.board, board.whiteToMove);
        
    if(is_square_attacked(temp_board.board, find_king(temp_board.board, board.whiteToMove), board.whiteToMove)) return false;

    return true;
}


vector<Move> generate_legal_moves(BoardState board)
{
    vector<Move> result;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            char piece = board.board[i][j];
            if(board.whiteToMove && isupper(piece) || !board.whiteToMove && islower(piece))
            {
                for(int k = 0; k < 8; k++)
                {
                    for(int l = 0; l < 8; l++)
                    {
                        if(is_legal_move(board, {i, j}, {k, l}))
                        {
                            if (piece == 'P' && k == 0)
                            {
                                result.push_back({{i,j},{k,l},piece,'Q'});
                                result.push_back({{i,j},{k,l},piece,'R'});
                                result.push_back({{i,j},{k,l},piece,'B'});
                                result.push_back({{i,j},{k,l},piece,'N'});
                            }
                            else if (piece == 'p' && k == 7)
                            {
                                result.push_back({{i,j},{k,l},piece,'q'});
                                result.push_back({{i,j},{k,l},piece,'r'});
                                result.push_back({{i,j},{k,l},piece,'b'});
                                result.push_back({{i,j},{k,l},piece,'n'});
                            }
                            else
                            {
                                result.push_back({{i,j},{k,l},piece,'\0'});
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}
