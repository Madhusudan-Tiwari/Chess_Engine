#include<iostream>
#include "types.h"
using namespace std;

void move_piece(char board[8][8], Position from, Position to, char promotion_piece)
{
    char piece = board[from.row][from.col];
    if ((piece == 'K' || piece == 'k') && abs(to.col - from.col) == 2)
    {
        
        if (to.col > from.col)
        {
            board[from.row][5] = board[from.row][7];
            board[from.row][7] = '.';
        }
        else
        {
            board[from.row][3] = board[from.row][0];
            board[from.row][0] = '.';
        }
    }

    if ((piece == 'P' || piece == 'p') && abs(to.col - from.col) == 1 && board[to.row][to.col] == '.')
    {
        int captured_row = (piece == 'P') ? to.row + 1 : to.row - 1;
        board[captured_row][to.col] = '.';
    }

    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = '.';

    if (piece == 'P' && to.row == 0)
    {
        if (promotion_piece != '\0') board[to.row][to.col] = toupper(promotion_piece);
        else
        {
            while (1)
            {
                cout << "Please enter the piece you want to promote it to (Q, B, N, R): ";
                char a;
                cin >> a;
                a = toupper(a);
                if (a == 'Q' || a == 'N' || a == 'R' || a == 'B')
                {
                    board[to.row][to.col] = a;
                    break;
                }
                else cout << "Please enter a valid choice\n";
            }
        }
    }
    else if (piece == 'p' && to.row == 7)
    {
        if (promotion_piece != '\0')
        {
            board[to.row][to.col] = tolower(promotion_piece);
        }
        else
        {
            while (1)
            {
                cout << "Please enter the piece you want to promote it to (q, b, n, r): ";
                char a;
                cin >> a;
                a = tolower(a);
                if (a == 'q' || a == 'n' || a == 'r' || a == 'b')
                {
                    board[to.row][to.col] = a;
                    break;
                }
                else cout << "Please enter a valid choice\n";
            }
        }
    }

    
}


void print_board(char board[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            cout<<board[i][j];
        }
        cout<<"\n";
    }
    cout<<"\n";
}
