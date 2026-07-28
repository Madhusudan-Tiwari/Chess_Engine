#include<iostream>
#include "types.h"
using namespace std;

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

bool inside(int row, int col)
{
    return row >= 0 && row < 8 &&
           col >= 0 && col < 8;
}
