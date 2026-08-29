#include <vector>
#include "utils.h"

int minimax(char board[8][8], bool white_to_move, int depth);
Move find_best_move(char board[8][8], bool white_to_move, int depth);