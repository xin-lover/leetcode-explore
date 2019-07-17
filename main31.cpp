#include <cstdio>
#include <vector>

using namespace std;

int countBattleships(vector<vector<char>>& board) {
    //思路：考虑一个战舰，除了头和尾，上下左右相邻的位置只有两个X，因为没有无效的排列
    //所以，遍历每一个X，查看其上下左右X的数量，如果是1则战舰+1，最后战舰的数量是结果/2

    int m = board.size();
    int n = m == 0 ? 0 : board[0].size();

    int res = 0;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(board[i][j] == 'X')
            {
                int c = 0;
                c += (j+1 < n && board[i][j+1] == 'X') ? 1 : 0;
                c += (j > 0 && board[i][j-1] == 'X') ? 1 : 0;
                c += (i+1 < m && board[i+1][j] == 'X') ? 1 : 0;
                c += (i > 0 && board[i-1][j] == 'X') ? 1 : 0;
                if(c==0)
                {
                    res += 2;
                }
                if(c == 1)
                {
                    ++res;
                }
            }
        }
    }

    printf("res:%d\n",res);
    return res / 2;
}

int main()
{
    vector<vector<char>> board = {
        {'X','.','.','X'},
        {'.','X','.','X'},
        {'.','X','.','X'},
        {'.','X','.','X'},
    };

    printf("%d\n",countBattleships(board));
}