//leetcode 646 最长数对链

#include <cstdio>
#include <vector>

using namespace std;

int findLongestChain(vector<vector<int>>& pairs) {
    //思路：排序，同时考察两个数，优先第二个

    sort(pairs.begin(),pairs.end(),[](vector<int> a, vector<int> b){
        if(a[1] == b[1])
        {
            return a[0] < b[0];
        }

        return a[1] < b[1];
    });

    //记录end
    int ep = pairs[0][1];
    printf("ep:%d\n",ep);
    int res=1;
    for(int i=1;i<pairs.size();++i)
    {
        printf("hh:%d\n",pairs[i][0]);
        if(pairs[i][0] > ep)
        {
            ++res;
            ep = pairs[i][1];
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> v = {{1,2},{2,3},{4,5}};
    printf("res:%d\n",findLongestChain(v));
    return 0;
}