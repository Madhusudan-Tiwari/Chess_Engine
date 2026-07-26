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

bool is_legal_move(char board[8][8], Position from, Position to, bool is_white_turn)
{
    if(from.row == to.row && from.col == to.col) return false;
    char piece = board[from.row][from.col];
    if(piece == '.')return false;
    if(is_white_turn && piece > 'Z') return false;
    if(!is_white_turn && piece < 'a') return false;
    

    
    
    switch(piece)
    {
        case 'P':
            if(to.col != from.col)return false;
            if(board[to.row][to.col] != '.')return false;
            if(from.row == 6)
            {
                if(to.row != 4 && to.row != 5) return false;
                if(to.row == 4 && board[5][to.col] != '.')return false;
            }
            else 
            {
                if(to.row - from.row != -1) return false;
            }
            break;

        case 'p':
            if(to.col != from.col)return false;
            if(board[to.row][to.col] != '.')return false;
            if(from.row == 1)
            {
                if(to.row != 2 && to.row != 3) return false;
                if(to.row == 3 && board[2][to.col] != '.')return false;
            }
            else 
            {
                if(to.row - from.row != 1) return false;
            }
            break;  

        default:
            return false;
    }



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

    bool is_white_turn = true;
    while(1)
    {
        pair<string, string> move =  take_input();
        Position from = string_to_index(move.first);
        Position to = string_to_index(move.second);
        if(is_legal_move(board, from, to, is_white_turn))
        {
            move_piece(board, from.row, from.col, to.row, to.col);
            is_white_turn = !is_white_turn;
        }
        else cout<<"Illegal Move \n";
        print_board(board);
    }

}