int evaluate_position(char board[8][8])
{
    int score = 0;
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            switch(board[row][col])
            {
                case 'P': score += 100; break;
                case 'N': score += 320; break;
                case 'B': score += 330; break;
                case 'R': score += 500; break;
                case 'Q': score += 900; break;

                case 'p': score -= 100; break;
                case 'n': score -= 320; break;
                case 'b': score -= 330; break;
                case 'r': score -= 500; break;
                case 'q': score -= 900; break;
            }
        }
    }
    return score;
}