//1409. 查询带键的排列

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> processQueries(vector<int>& queries, int m) {
    //思路：整个转换过程倒是不复杂，但主要涉及数组的移动，如果真的移动数组
    //性能会非常低，采用记录移动操作的方式，每次查询时根据记录计算查询结果
    //但queries长度变成时，这个计算过程也同样会加长
    //长度10^3，先用map的方式试试

    unordered_map<int,int> um;
    vector<int> P(m);
    for(int i=1;i<=m;++i)
    {
        um[i] = i-1;
        P[i-1]=i;
    }

    vector<int> res;
    for(auto a : queries)
    {
        int p = um[a];
        res.push_back(p);

        int tmp = P[p];
        for(int i=p;i>0;--i)
        {
            P[i] = P[i-1];
            um[P[i]] = i;
        }
        P[0] = tmp;
        um[tmp] = 0;
    }


    return res;
}

vector<int> processQueries2(vector<int>& queries, int m) {
    //思路：记录操作，除了操作数，其它数字如果在操作数之前，则位置会向后移一位
    //而在其后的不动

    vector<int> res;
    for(int i=0;i<queries.size();++i)
    {
        int p = queries[i]-1;
        for(int j=0;j<i;++j)
        {
            if(p < res[j])
            {
                ++p;
            }
            else if(p == res[j])
            {
                p = 0;
            }
        }

        res.push_back(p);
    }

    return res;
}

int main()
{
    vector<int> queries = {3,1,2,1};
    int m = 5; //2 1 2 1

    // queries = {4,1,2,2};
    // m = 4;  //3 1 2 0

    // queries = {7,5,5,8,3};
    // m = 8;  //[6,5,0,7,5]

    for(auto a : processQueries2(queries,m))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}