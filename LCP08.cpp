//LCP 08. 剧情触发时间

#include <cstdio>
#include <vector>

using namespace std;

vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
    //思路，问题的关键如何确定满足某个触发条件，一天一天增加，然后查找，肯定不行
    //还是考虑二分，因为资源是单调递增的

    int n = increase.size();
    vector<vector<int>> preSums(n+1,vector<int>(3,0));
    for(int i=1;i<=n;++i)
    {
        preSums[i][0] = preSums[i-1][0] + increase[i-1][0];
        preSums[i][1] = preSums[i-1][1] + increase[i-1][1];
        preSums[i][2] = preSums[i-1][2] + increase[i-1][2];
    }

    vector<int> res(requirements.size(),-1);
    for(int i=0;i<requirements.size();++i)
    {
        int left=0,right=preSums.size()-1;
        while(left < right)
        {
            int mid = left + (right-left)/2;
            bool chk = preSums[mid][0] >= requirements[i][0] && preSums[mid][1] >= requirements[i][1] && preSums[mid][2] >= requirements[i][2];
            if(chk)
            {
                right = mid;
            }
            else
            {
                left = mid+1;
            }
        }

        if(preSums[right][0] >= requirements[i][0] && preSums[right][1] >= requirements[i][1] && preSums[right][2] >= requirements[i][2])
        {
            res[i] = right;
        }
    }

    return res;
}

int main()
{
    //[2,-1,3,-1]
    vector<vector<int>> increase = {{2,8,4},{2,5,0},{10,9,8}}, requirements = {{2,11,3},{15,10,7},{9,17,12},{8,1,14}};

    //[-1,4,3,3,3]
    // increase = {{0,4,5},{4,8,8},{8,6,1},{10,10,0}}, requirements = {{12,11,16},{20,2,6},{9,2,6},{10,18,3},{8,14,9}};

    //[0]
    // increase = {{1,1,1}},requirements= {{0,0,0}};

    for(auto a : getTriggerTime(increase,requirements))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}