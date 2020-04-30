//1282. 用户分组

#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
    //思路：所在组的元素数量相同，说明两者可能在同一组
    //没有其它条件，就意味着可能有多种答案，我们随意选择其中一种
    //方案：按数量分组，然后平分即可

    //优化：可以一次遍历，使用一个数组存储每种数量集合，当某种集合数量够了就放到结果数组中
    //比如：遇到3，就把这个元素放到指定的容量为3的集合中，如果这个集合数量到3了，就存储到结果中再清空
    int n = groupSizes.size();
    vector<vector<int>> states(n+1);

    for(int i=0;i<n;++i)
    {
        states[groupSizes[i]].push_back(i);
    }

    vector<vector<int>> res;
    for(int i=1;i<=n;++i)
    {
        int groups = states[i].size() / i;
        for(int j=0;j<groups;++j)
        {
            vector<int> tmp;
            for(int k=0;k<i;++k)
            {
                tmp.push_back(states[i][j*i+k]);
            }
            res.push_back(tmp);
        }
    }

    return res;
}

vector<vector<int>> groupThePeople2(vector<int>& groupSizes) {
    //优化：可以一次遍历，使用一个数组存储每种数量集合，当某种集合数量够了就放到结果数组中
    //比如：遇到3，就把这个元素放到指定的容量为3的集合中，如果这个集合数量到3了，就存储到结果中再清空
    int n = groupSizes.size();
    vector<vector<int>> states(n+1);
    vector<vector<int>> res;
    for(int i=0;i<n;++i)
    {
        int capacity = groupSizes[i];
        states[capacity].push_back(i);
        if(states[capacity].size() == capacity)
        {
            res.push_back(states[capacity]);
            states[capacity].clear();
        }
    }

    return res;
}

int main()
{
    vector<int> groupSizes = {3,3,3,3,3,1,3};   //[[5],[0,1,2],[3,4,6]]
    // groupSizes = {2,1,3,3,3,2}; //[[1],[0,5],[2,3,4]]

    vector<vector<int>> res = groupThePeople2(groupSizes);
    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    return 0;
}