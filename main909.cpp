//leetcode 909. 蛇梯棋

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int snakesAndLadders(vector<vector<int>>& board) {
    //思路：蛇和梯子不算步数，通常的思路就是回溯
    //但觉得有点慢，重复计算太多了
    //这里只能往前走，目标就改为使用最少的步数走到最远的地方
    //可以考虑图的遍历方式，使用一个队列存储当前能走到的点，直到走到终点结束
    //这里有个可以剪枝的点，就是不走蛇和梯子可以求出一个最大的步数，操作这个步数就可以停止了
    //注意，坐标转换
    //每次只能爬一次梯子。。。。

    int m = board.size();
    int n = board[0].size();
    int nums = m * n;

    int c = m*n -1;
    int maxStep = c / 6 + (c%6 == 0 ? 0 : 1);
    int step = 0;
    int odd_or_even = ((n-1) & 1);
    
    vector<bool> flags(m*n+1,false);

    queue<int> qu;
    qu.push(1);

    while(!qu.empty() && step < maxStep)
    {
        ++step;
        int sz = qu.size();
        printf("---------------------\n");
        for(int i=0;i<sz;++i)
        {
            int p = qu.front();
            qu.pop();

            if(p+6 >= nums)
            {
                return step;
            }


            //当前位置就是梯子
            //转换坐标
            // int x = (p-1) / n;
            // int y = p - 1 - x * n;
            // x = m - x - 1;
            // y = !((x&1)^odd_or_even) ? y : n-1-y;

            // bool jump = false;
            // if(board[x][y] > 0)
            // {
            //     p = board[x][y];
            //     jump = true;
            // }

            for(int j=1;j<=6;++j)
            {
                ++p;

                // y+=dir;  //没必要，先把思路写清晰
                // if(y >= n || y < 0)
                // {
                //     --x;
                //     dir = -dir;
                //     y= dir > 0 ? 0 : n-1;
                // }

                // if(!flags[p])
                {
                    //转换坐标
                    int tx = (p-1) / n;
                    int ty = p - 1 - tx * n;
                    tx = m - tx - 1;
                    ty = !((tx&1)^odd_or_even) ? ty : n-1-ty;

                    int target = p;
                    if(board[tx][ty] > 0)
                    {
                        printf("boaddd:%d\n",board[tx][ty]);
                        target = board[tx][ty];
                    }

                    if(target >= nums)
                    {
                        return step;
                    }
                    if(!flags[target])
                    {
                        printf("push:%d\n",target);
                        flags[target] = true;
                        qu.push(target);
                    }
                }
            }
        }
    }

    return -1;
}

int main()
{
    vector<vector<int>> board = {
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,35,-1,-1,13,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,15,-1,-1,-1,-1}
    };

    board = {{-1,-1},{-1,3}};

    board = {
        {-1,-1,-1},
        {-1,9,8},
        {-1,8,9}};

    board = {{-1,4,-1},{6,2,6},{-1,3,-1}};

    board = {{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};

    board = {
        {1,1,-1},
        {1,1,1},
        {-1,1,1}};

    board = {
        {-1,-1,30,14,15,-1},
        {23,9,-1,-1,-1,9},
        {12,5,7,24,-1,30},
        {10,-1,-1,-1,25,17},
        {32,-1,28,-1,-1,32},
        {-1,-1,23,-1,13,19}
        };//2

    // board = {
    //     {-1,-1,2,-1},
    //     {14,2,12,3},
    //     {4,9,1,11},
    //     {-1,2,1,16}}; //1

    
    //4
    board = {{-1,-1,-1,46,47,-1,-1,-1},{51,-1,-1,63,-1,31,21,-1},{-1,-1,26,-1,-1,38,-1,-1},{-1,-1,11,-1,14,23,56,57},{11,-1,-1,-1,49,36,-1,48},{-1,-1,-1,33,56,-1,57,21},{-1,-1,-1,-1,-1,-1,2,-1},{-1,-1,-1,8,3,-1,6,56}};

    //6
    // board = {{-1,-1,-1,30,-1,144,124,135,-1,-1,-1,-1,-1},
    // {-1,-1,-1,-1,-1,-1,167,93,-1,-1,-1,-1,-1},
    // {-1,-1,-1,-1,-1,-1,-1,77,-1,-1,90,-1,-1},
    // {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    // {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,-1},
    // {-1,-1,-1,23,-1,-1,-1,-1,-1,155,-1,-1,-1},
    // {-1,-1,140,29,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    // {-1,-1,-1,-1,-1,115,-1,-1,-1,109,-1,-1,5},
    // {-1,57,-1,99,121,-1,-1,132,-1,-1,-1,-1,-1},
    // {-1,48,-1,-1,-1,68,-1,-1,-1,-1,31,-1,-1},
    // {-1,163,147,-1,77,-1,-1,114,-1,-1,80,-1,-1},
    // {-1,-1,-1,-1,-1,57,28,-1,-1,129,-1,-1,-1},
    // {-1,-1,-1,-1,-1,-1,-1,-1,-1,87,-1,-1,-1}};

    printf("%d\n",snakesAndLadders(board));
    return 0;
}