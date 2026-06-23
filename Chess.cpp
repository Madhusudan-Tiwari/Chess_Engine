#include<iostream>
using namespace std;

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

void move_piece(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = '.';
}

int main()
{
    char board[8][8] =
    {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}};

    print_board(board);
}