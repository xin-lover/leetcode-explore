//leetcode 794. 有效的井字游戏

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

bool validTicTacToe(vector<string>& board) {
    //思路：根据规则
    //1.X数量必须不少于O，因为X先放；
    //2.X与O的数量不能差2以上，因为轮流放
    //3.判断X或O的数量大于3时，是否成行,成列，成对角线
    //结束时呈现也为true

    int xcount = 0;
    int ocount = 0;

    for(int i=0;i<board.size();++i)
    {
        for(int j=0;j<board[i].size();++j)
        {
            if(board[i][j] == 'X')
            {
                ++xcount;
            }
            else if(board[i][j] == 'O')
            {
                ++ocount;
            }
        }
    }

    if(ocount > xcount || xcount - ocount > 1)
    {
        return false;
    }

    if(ocount >= 3 || xcount >= 3)
    {
        //行判断
        for(int i=0;i<board.size();++i)
        {
            char c = board[i][0];
            if(c == 'X' || c == 'O')
            {
                if(board[i][1] == c && board[i][2] == c)
                {
                    if(c == 'X' && ocount == xcount)
                    {
                        return false;
                    }
                    if(c == 'O' && xcount > ocount)
                    {
                        return false;
                    }
                }
            }
        }

        //列判断
        for(int i=0;i<3;++i)
        {
            char c = board[0][i];
            if(c == 'X' || c == 'O')
            {
                if(board[1][i] == c && board[2][i] == c)
                {
                    if(c == 'X' && ocount == xcount)
                    {
                        return false;
                    }
                    if(c == 'O' && xcount > ocount)
                    {
                        return false;
                    }
                }
            }
        }

        //对角线
        char c = board[1][1];
        if(c == 'X' || c == 'O')
        {
            if(board[0][0] == c && board[2][2] == c)
            {
                if(c == 'X' && ocount == xcount)
                {
                    return false;
                }
                if(c == 'O' && xcount > ocount)
                {
                    return false;
                }
            }

            if(board[0][2] == c && board[2][0] == c)
            {
                if(c == 'X' && ocount == xcount)
                {
                    return false;
                }
                if(c == 'O' && xcount > ocount)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    vector<string> board = {"O  ","   ","   "};
    board = {"XXX","   ","OOO"};
    board = {"XOX", "O O", "XOX"};
    board = {"XO ","XO ","XO "};
    // board = {"XXX","OOX","OOX"};
    board = {"OXX","XOX","OXO"};
    
    printf(validTicTacToe(board) ? "true\n" : "false\n");
    return 0;
}