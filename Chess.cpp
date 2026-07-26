#include<iostream>
using namespace std;


struct Position
{
    int row;
    int col;
};

bool valid_square(string pos)
{
    if(pos.length() != 2 || pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') return false;
    return true;
}

pair<string, string> take_input()
{
    string from, to;
    while(true)
    {
        cin>>from>>to;
        if(valid_square(from) && valid_square(to)) return {from, to};
        cout<< "Invalid Input \n";
    }
}

Position string_to_index(string pos)
{
    int col = pos[0] - 'a';
    int row = 8 - (pos[1] - '0');
    return{row, col};
}

bool is_legal_move(char board[8][8], Position from, Position to)
{
    if(from.row == to.row && from.col == to.col) return false;
    if(board[from.row][from.col] == '.')return false;
    return true;
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
    print_board(board);

    while(1)
    {
        pair<string, string> move =  take_input();
        Position from = string_to_index(move.first);
        Position to = string_to_index(move.second);
        if(is_legal_move(board, from, to))
        {
            move_piece(board, from.row, from.col, to.row, to.col);
        }
        else cout<<"Illegal Move";
        print_board(board);
    }

}