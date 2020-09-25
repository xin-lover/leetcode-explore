//37. 解数独

#include <cstdio>
#include <vector>

using namespace std;

void solveSudoku(vector<vector<char>>& board) {
    //思路：没有专业学过数独解法，以前都是在数组中找能确定的位置一个一个的往上填
    //能确定的位置就是那个3个条件，横、竖、当前宫格不能出现重复的数字
    //如果在程序中使用这种思路，那就是递进的过程
    //也就是不断的扫描表格，第一遍确定第一遍能确定的数字，然后不断递进直到所有数字都确定
    //但这个遇到需要猜的问题，就不行了。。。
    //使用暴力破解，那复杂度非常高

    int m = board.size();
    int n = m==0 ? 0 : board[0].size();

    bool complete = false;
    while(!complete)
    {
        complete = true;
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(board[i][j] == '.')
                {
                    //取 横、竖、当前宫格
                    vector<bool> flags(9,false);
                    for(int k=0;k<9;++k)
                    {
                        if(board[i][k] != '.')
                        {
                            flags[board[i][k]-'0'-1] = true;
                        }
                    }

                    for(int k=0;k<9;++k)
                    {
                        if(board[k][j] != '.')
                        {
                            flags[board[k][j]-'0'-1] = true;
                        }
                    }

                    int x = i / 3;
                    int y = j / 3;
                    for(int k1=0;k1<3;++k1)
                    {
                        for(int k2=0;k2<3;++k2)
                        {
                            if(board[x*3+k1][y*3+k2] != '.')
                            {
                                flags[board[x*3+k1][y*3+k2]-1-'0'] = true;
                            }
                        }
                    }

                    //如果只有一个未确定，那么就取它
                    int t = 0;
                    int p = -1;
                    for(int k=0;k<9;++k)
                    {
                        if(flags[k])
                        {
                            ++t;
                        }
                        else
                        {
                            p = k;
                        }
                        
                    }

                    if(t == 8)
                    {
                        board[i][j] = '0' + p+1;
                    }
                    else if(t < 8)
                    {
                        complete = false;
                    }
                    
                }
            }
        }
    }
}

void dfs(vector<vector<bool>>& lines,vector<vector<bool>>& columns,vector<vector<vector<bool>>>& blocks,vector<pair<int, int>>& spaces,int start,vector<vector<char>>& board,bool& valid)
{
    if(start == spaces.size())
    {
        valid = true;
        return;
    }

    auto [i,j] = spaces[start];

    for(int x=0;x<9 && !valid;++x)
    {
        if(!lines[i][x] && !columns[j][x] && !blocks[i/3][j/3][x])
        {
            board[i][j] = '0' + x + 1;
            lines[i][x] = true;
            columns[j][x] = true;
            blocks[i/3][j/3][x] = true;
            dfs(lines,columns,blocks,spaces,start+1,board,valid);
            lines[i][x] = false;
            columns[j][x] = false;
            blocks[i/3][j/3][x] = false;
        }
    }
}

void solveSudoku2(vector<vector<char>>& board) {
    //思路：行优先，递归+回溯

    vector<vector<bool>> lines(9,vector<bool>(9,false));
    vector<vector<bool>> columns(9,vector<bool>(9,false));
    vector<vector<vector<bool>>> blocks(3,vector<vector<bool>>(3,vector<bool>(9,false)));
    vector<pair<int, int>> spaces;

    int m = board.size();
    int n = m == 0 ? 0 : board[0].size();
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(board[i][j] != '.')
            {
                int c = board[i][j]-'0'-1;
                lines[i][c] = true;
                columns[j][c] = true;
                blocks[i/3][j/3][c] = true;
            }
            else
            {
                spaces.emplace_back(i,j);
            }
            
        }
    }

    bool valid =false;
    dfs(lines,columns,blocks,spaces,0,board,valid);
}

//使用位运算优化
class Solution {
private:
    int line[9];
    int column[9];
    int block[3][3];
    bool valid;
    vector<pair<int, int>> spaces;

public:
    void flip(int i, int j, int digit) {
        line[i] ^= (1 << digit);
        column[j] ^= (1 << digit);
        block[i / 3][j / 3] ^= (1 << digit);
    }

    void dfs(vector<vector<char>>& board, int pos) {
        if (pos == spaces.size()) {
            valid = true;
            return;
        }

        auto [i, j] = spaces[pos];
        int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1)) {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);//__builtin_ctz(x)：x末尾0的个数。x=0时结果未定义。
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        memset(line, 0, sizeof(line));
        memset(column, 0, sizeof(column));
        memset(block, 0, sizeof(block));
        valid = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
                else {
                    int digit = board[i][j] - '0' - 1;
                    flip(i, j, digit);
                }
            }
        }

        dfs(board, 0);
    }
};

//枚举优化，使用第一个想法，找到能唯一确定数的位置先填上。。。。
// class Solution {
// private:
//     int line[9];
//     int column[9];
//     int block[3][3];
//     bool valid;
//     vector<pair<int, int>> spaces;

// public:
//     void flip(int i, int j, int digit) {
//         line[i] ^= (1 << digit);
//         column[j] ^= (1 << digit);
//         block[i / 3][j / 3] ^= (1 << digit);
//     }

//     void dfs(vector<vector<char>>& board, int pos) {
//         if (pos == spaces.size()) {
//             valid = true;
//             return;
//         }

//         auto [i, j] = spaces[pos];
//         int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
//         for (; mask && !valid; mask &= (mask - 1)) {
//             int digitMask = mask & (-mask);
//             int digit = __builtin_ctz(digitMask);
//             flip(i, j, digit);
//             board[i][j] = digit + '0' + 1;
//             dfs(board, pos + 1);
//             flip(i, j, digit);
//         }
//     }

//     void solveSudoku(vector<vector<char>>& board) {
//         memset(line, 0, sizeof(line));
//         memset(column, 0, sizeof(column));
//         memset(block, 0, sizeof(block));
//         valid = false;

//         for (int i = 0; i < 9; ++i) {
//             for (int j = 0; j < 9; ++j) {
//                 if (board[i][j] != '.') {
//                     int digit = board[i][j] - '0' - 1;
//                     flip(i, j, digit);
//                 }
//             }
//         }

//         while (true) {
//             int modified = false;
//             for (int i = 0; i < 9; ++i) {
//                 for (int j = 0; j < 9; ++j) {
//                     if (board[i][j] == '.') {
//                         int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
//                         if (!(mask & (mask - 1))) {
//                             int digit = __builtin_ctz(mask);
//                             flip(i, j, digit);
//                             board[i][j] = digit + '0' + 1;
//                             modified = true;
//                         }
//                     }
//                 }
//             }
//             if (!modified) {
//                 break;
//             }
//         }

//         for (int i = 0; i < 9; ++i) {
//             for (int j = 0; j < 9; ++j) {
//                 if (board[i][j] == '.') {
//                     spaces.emplace_back(i, j);
//                 }
//             }
//         }

//         dfs(board, 0);
//     }
// };

int main()
{
    vector<vector<char>> boards = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};

    for(auto a : boards)
    {
        for(auto b : a)
        {
            printf("%c ",b);
        }
        printf("\n");
    }

    printf("-----------------\n");
    // solveSudoku(boards);
    solveSudoku2(boards);

    for(auto a : boards)
    {
        for(auto b : a)
        {
            printf("%c ",b);
        }
        printf("\n");
    }

    return 0;
}