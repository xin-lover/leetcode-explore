//leetcod 885. 螺旋矩阵 lll
//

#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
    
    //思路：螺旋可以理解为4条边为一个圈，但最后一条边会延长
    //即最开始的边为2，到第3条边的时候为3，同理到第7条边的时候为4
    //策略：一条边一条边的添加
    
    vector<vector<int>> res;
    int len = 2;
    int state = 1;
    int curRow = r0;
    int curCol = c0;
    
    int c = max(c0,C-c0-1);
    int d = max(r0,R-r0-1);
    c = max(c,d);
    for(int j=0;j<=c;++j)
    {
        //向右
        int start,end;
        if(curRow >= 0)
        {
            start = max(curCol,0);
            end = min(curCol+len,C);
            printf("ss1:%d %d\n",curCol,end);
            for(int i=start;i<end;++i)
            {
                printf("get 4\n");
                res.push_back({curRow,i});
            }
        }
        
        //向下
        curCol = curCol + len -1;
        if(curCol < C)
        {
            start = max(curRow+1,0);
            end = min(curRow+len,R);
            printf("ss2:%d %d\n",curRow+1,end);
            for(int i=start;i<end;++i)
            {
                printf("get 1\n");
                res.push_back({i,curCol});
            }
        }

        
        //向左
        curRow=curRow + len - 1;
        ++len;
        if(curRow < R)
        {
            start = min(curCol-1,C-1);
            end = max(curCol-len,-1);
            printf("ss3:%d %d\n",curCol-1,end);
            for(int i=start;i>end;--i)
            {
                printf("get 2\n");
                res.push_back({curRow,i});
            }
        }

                    
        //向上
        curCol = curCol - len + 1;
        if(curCol >= 0)
        {
            start = min(curRow-1,R-1);
            end = max(curRow-len+1,-1);
            printf("ss4:%d %d\n",curRow-1,end);
            for(int i=start;i>end;--i)
            {
                printf("get 3\n");
                res.push_back({i,curCol});
            }
        }
       
        curRow=curRow-len+1;
        ++len; 
    }
    
    return res;
}

int main()
{
    auto res = spiralMatrixIII(1,4,0,0);
    // auto res = spiralMatrixIII(5,6,1,4);

    for(auto a : res)
    {
        printf("[");
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("]");
    }

    return 0;
}