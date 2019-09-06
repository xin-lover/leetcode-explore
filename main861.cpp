//leetcode 861. 翻转矩阵后的得分

#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

int matrixScore(vector<vector<int>>& A) {
    //思路：结果是由行表示，所以翻转的原则是保证高位为1
    //所以现在的问题是选择行转换还是列转换
    //每一行，每一列都最后都可认为最多翻转一次，因为2次就相当于没有翻转
    //列的翻转看0和1多少，而行看位置
    //先行变换和先列变换是一样的，所以我们统一先行变换再列变换
    //策略：先使用行变换把首位都变为1，然后再考虑每一列的列变换

    if(A.empty() || A[0].empty())
    {
        return 0;
    }

    for(int i=0;i<A.size();++i)
    {
        if(A[i][0] == 0)
        {
            for(int j=0;j<A[i].size();++j)
            {
                A[i][j] = 1 - A[i][j];
            }
        }
    }

    int sum = A.size() * pow(2,A[0].size()-1);
    //每一列根据0的多少判断,优化，直接计算结果
    for(int i=1;i<A[0].size();++i)
    {
        int count0 = 0;
        int count1 = 0;
        for(int j=0;j<A.size();++j)
        {
            if(A[j][i] == 0)
            {
                ++count0;
            }
            else
            {
                ++count1;
            }
        }

        sum += (count0 > count1 ? count0 : count1)*pow(2,A[0].size()-1-i);
    }

    return sum;
}

int main()
{
    vector<vector<int>> A = {{0,0,1,1},{1,0,1,0},{1,1,0,0}};
    printf("%d\n",matrixScore(A));
    return 0;
}