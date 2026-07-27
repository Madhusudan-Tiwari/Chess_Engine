#include<iostream>
using namespace std;

bool whiteKingMoved = false;
bool blackKingMoved = false;

bool whiteHRookMoved = false;
bool whiteARookMoved = false;

bool blackHRookMoved = false;
bool blackARookMoved = false;

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

void move_piece(char board[8][8], Position from, Position to)
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

    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = '.';
}

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

bool inside(int row, int col)
{
    return row >= 0 && row < 8 &&
           col >= 0 && col < 8;
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

bool is_legal_move(char board[8][8], Position from, Position to, bool is_white_turn)
{
    if(from.row == to.row && from.col == to.col) return false;
    char piece = board[from.row][from.col];
    if(piece == '.')return false;

    int row_diff = abs(to.row - from.row);
    int col_diff = abs(to.col-from.col);
    char target = board[to.row][to.col];

    if(is_white_turn && (piece > 'Z' || (target < 'Z' && target > 'A'))) return false;
    if(!is_white_turn && (piece < 'a' || ( target <'z' && target > 'a'))) return false;
    
    
    switch(piece)
    {
        case 'P':
            if(col_diff == 0)
            {
                if(target != '.')return false;
                if(from.row == 6)
                {
                    if(to.row != 4 && to.row != 5) return false;
                    if(to.row == 4 && board[5][to.col] != '.')return false;
                }
                else 
                {
                    if(to.row - from.row != -1) return false;
                }
            }
            else if(col_diff == 1)
            {
                if(target == '.')return false;
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
                    if(to.row == 3 && board[2][to.col] != '.')return false;
                }
                else 
                {
                    if(to.row - from.row != 1) return false;
                }
            }
            else if(col_diff == 1)
            {
                if(target == '.')return false;
                if(to.row - from.row != 1)return false;
            }
            else return false;
            break;  

        case 'N':
        case 'n':
            if((row_diff != 1 && row_diff != 2) || (col_diff != 1 && col_diff!=2) || row_diff + col_diff != 3)return false;
            break;

        case 'k':
        case 'K':
            if(row_diff > 1 || col_diff > 2) return false;
            if(col_diff == 2)
            {
                if(row_diff != 0) return false;
                if(is_white_turn && whiteKingMoved || !is_white_turn && blackKingMoved)return false;
                if(to.col > from.col)
                {
                    if (is_white_turn && whiteHRookMoved || !is_white_turn && blackHRookMoved) return false;
                    if (board[from.row][5] != '.' || board[from.row][6] != '.') return false;

                    if (is_square_attacked(board, {from.row, 4}, is_white_turn) ||
                        is_square_attacked(board, {from.row, 5}, is_white_turn) ||
                        is_square_attacked(board, {from.row, 6}, is_white_turn))
                        return false;
                }
                else
                {
                    
                    if (is_white_turn && whiteARookMoved || !is_white_turn && blackARookMoved) return false;
                    if (board[from.row][1] != '.' || board[from.row][2] != '.' || board[from.row][3] != '.') return false;

                    if (is_square_attacked(board, {from.row, 4}, is_white_turn) ||
                        is_square_attacked(board, {from.row, 3}, is_white_turn) ||
                        is_square_attacked(board, {from.row, 2}, is_white_turn))
                        return false;
                }
            }
            break;

        case 'r':
        case 'R':
            if(row_diff != 0 && col_diff != 0) return false;
            if(!is_path_clear(board, from, to)) return false;
            break;

        case 'b':
        case 'B':
            if(row_diff != col_diff) return false;
            if(!is_path_clear(board, from, to)) return false;
            break;

        case 'q':
        case 'Q':
            if(row_diff != col_diff && row_diff != 0 && col_diff != 0) return false;
            if(!is_path_clear(board, from, to)) return false;
            break;

        default:
            return false;
    }

    char temp_board[8][8];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            temp_board[i][j] = board[i][j];
        }
    }

    move_piece(temp_board, from, to);
    if(is_square_attacked(temp_board, find_king(temp_board, is_white_turn), is_white_turn)) return false;

    return true;
}


GameState check_game_state(char board[8][8], bool white_to_move)
{
    bool has_legal_move = false;
    for(int i = 0; i < 8 && !has_legal_move; i++)
    {
        for(int j = 0; j < 8 && !has_legal_move; j++)
        {
            char piece = board[i][j];
            if((white_to_move && isupper(piece)) || (!white_to_move && islower(piece)))
            {
                for(int k = 0; k < 8; k++)
                {
                    for(int l = 0; l < 8; l++)
                    {
                        if(is_legal_move(board, {i, j}, {k, l}, white_to_move))
                        {
                            has_legal_move = true;
                            break;
                        }
                    }
                    if(has_legal_move)break;
                }
            }
        }
    }

    Position king_pos = find_king(board, white_to_move);
    bool king_in_check = is_square_attacked(board, king_pos, white_to_move);

    if (has_legal_move)
    {
        return king_in_check ? CHECK : NORMAL;
    }
    else
    {
        return king_in_check ? CHECKMATE : STALEMATE;
    }
}

void update_castling_flags(Position from, Position to, char piece)
{
    if (piece == 'K') whiteKingMoved = true;
    if (piece == 'k') blackKingMoved = true;

    if (piece == 'R')
    {
        if (from.row == 7 && from.col == 0) whiteARookMoved = true;
        if (from.row == 7 && from.col == 7) whiteHRookMoved = true;
    }
    if (piece == 'r')
    {
        if (from.row == 0 && from.col == 0) blackARookMoved = true;
        if (from.row == 0 && from.col == 7) blackHRookMoved = true;
    }

    if (to.row == 7 && to.col == 0) whiteARookMoved = true;
    if (to.row == 7 && to.col == 7) whiteHRookMoved = true;
    if (to.row == 0 && to.col == 0) blackARookMoved = true;
    if (to.row == 0 && to.col == 7) blackHRookMoved = true;
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
            char piece = board[from.row][from.col];
            update_castling_flags(from, to, piece);            
            move_piece(board, from, to);
            is_white_turn = !is_white_turn;
        }
        else cout<<"Illegal Move \n";
        print_board(board);
        GameState state = check_game_state(board, is_white_turn);

        if(state == CHECKMATE)
        {
            cout<<"Checkmate Game Over"<<"\n";
            break;
        }
        else if(state == STALEMATE)
        {
            cout<<"STALEMATE It's a DRAW"<<"\n";
            break;
        }
        else if(state == CHECK)
        {
            cout<<"CHECK"<<"\n";
        }
    }

}