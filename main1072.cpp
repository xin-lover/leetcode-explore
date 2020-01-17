//1072. 按列翻转得到最大值等行数

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
    //思路：列翻转，列是有限的，但因为每个列的选择有两个，所有的情况有2^列数
    //穷举不合适，考虑翻转之后行能相等，那意味着行的特征是相等的
    //所以我们只需要比较行就可以了，注意如果row2==row1,row3==row1,可以推断出row2==row3
    //所以我们的算法是O(row^2)的复杂度
    //两行相等我们用异或来比较，也就是每个位置都异或，那么结果要么全0，要么全1，某则不相等

    int res = 0;
    for(int i=0;i<matrix.size();++i)
    {
        int t = 1;
        for(int j=i+1;j<matrix.size();++j)
        {
            int sum = 0;
            for(int k=0;k<matrix[i].size();++k)
            {
                sum += (matrix[i][k]^matrix[j][k]);
            }
            if(sum == 0 || sum == matrix[i].size())
            {
                ++t;
            }
        }

        res = max(t,res);
    }

    return res;
}

int maxEqualRowsAfterFlips2(vector<vector<int>>& matrix) {
    //优化：上面行的比较有点冗余，根据行等价，我们可以推出同一个集合中行不用再次比较

    vector<int> flags(matrix.size(),-1);
    int res = 0;
    for(int i=0;i<matrix.size();++i)
    {
        if(flags[i] != -1)
        {
            continue;
        }
        int t = 1;
        for(int j=i+1;j<matrix.size();++j)
        {
            if(flags[j] != -1)
            {
                continue;
            }
            int sum = 0;
            for(int k=0;k<matrix[i].size();++k)
            {
                sum += (matrix[i][k]^matrix[j][k]);
            }
            if(sum == 0 || sum == matrix[i].size())
            {
                ++t;
                flags[j] = i;
            }
        }

        res = max(t,res);
    }

    return res;
}

int maxEqualRowsAfterFlips3(vector<vector<int>>& matrix) 
{
    //思路：上面的优化性能提高一倍，还可以再剪枝，但复杂度不会再有大的变化
    //考虑转换为string，同时如果一行都让其以0开始，通过set或map求最大值

    unordered_map<string,int> um;
    for(int i=0;i<matrix.size();++i)
    {
        bool flip = (matrix[i][0] == 1);
        string t;
        for(int j=0;j<matrix[i].size();++j)
        {
            t.append(1,(flip ? 1-matrix[i][j] : matrix[i][j]) + '0');
        }

        ++um[t];
    }

    int res = 1;
    for(auto it = um.begin();it!=um.end();++it)
    {
        res = max(res,it->second);
    }

    return res;
}

int maxEqualRowsAfterFlips4(vector<vector<int>>& matrix) 
{
    //避免01转换，特征定义变一下，变成连续相同数字出现的次数
    //比如11100110为3221，这样00011001也是3221，但他们可以翻转后让行变为一样的
}

int main()
{
    vector<vector<int>> matrix = {{0,1},{1,0}};//2
    // matrix = {{0,0,0},{0,0,1},{1,1,0}}; //2
    printf("%d\n",maxEqualRowsAfterFlips4(matrix));
    return 0;
}