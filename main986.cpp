//986. 区间列表的交集

#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    //思路：因为列表已经排序，所以就很简单了，用两个下标指向两个序列，然后把重合区间提取，更新原空间为不重合区间
    //哪一列表的当前区间用尽，下标+1

    vector<vector<int>> res;
    int i=0,j=0;
    while(i < A.size() && j < B.size())
    {
        if(A[i][1] < B[j][0])
        {
            ++i;
            continue;
        }
        else if(B[j][1] < A[i][0])
        {
            ++j;
            continue;
        }
        else
        {
            //相交
            if(A[i][1] <= B[j][1])
            {
                if(A[i][0] >= B[j][0])
                {
                    res.push_back({A[i][0],A[i][1]});
                }
                else
                {
                    res.push_back({B[j][0],A[i][1]});
                }

                B[j][0] = A[i][1]+1;
                if(B[j][0] > B[j][1])
                {
                    ++j;
                }
                ++i;
            }
            else
            {
                if(B[j][0] >= A[i][0])
                {
                    res.push_back({B[j][0],B[j][1]});
                }
                else
                {
                    res.push_back({A[i][0],B[j][1]});
                }

                A[i][0] = B[j][1]+1;
                ++j;
            }
        }
        
    }

    return res;
}

vector<vector<int>> intervalIntersection2(vector<vector<int>>& A, vector<vector<int>>& B) {
    //思路一样，但写法更简单,不构造新空间
    int i=0,j=0;
    vector<vector<int>> res;

    while(i < A.size() && j<B.size())
    {
        int lo = max(A[i][0],B[j][0]);
        int hi = min(A[i][1],B[j][1]);

        if(lo <= hi)
        {
            res.push_back({lo,hi});
        }

        if(A[i][1] >= B[j][1])
        {
            ++j;
        }
        else
        {
            ++i;
        }
        
    }

    return res;
}

int main()
{
    vector<vector<int>> A = {{0,2},{5,10},{13,23},{24,25}}, B = {{1,5},{8,12},{15,24},{25,26}};
    auto res = intervalIntersection2(A,B); //[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
    for(auto a : res)
    {
        printf("[%d,%d],",a[0],a[1]);
    }
    printf("\n");
    return 0;
}