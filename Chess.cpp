#include<iostream>
using namespace std;

pair<string, string> take_input()
{
    string from, to;
    cin>>from>>to;
    return {from, to};
}

pair<int , int> string_to_index(string pos)
{
    int col = pos[0] - 'a';
    int row = 8 - (pos[1] - '0');
    return{row, col};
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

    while(1)
    {
        pair<string, string> move =  take_input();
        pair<int, int> from = string_to_index(move.first);
        pair<int, int> to = string_to_index(move.second);
        move_piece(board, from.first, from.second, to.first, to.second);
        print_board(board);
    }

}