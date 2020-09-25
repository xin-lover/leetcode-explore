//45. 跳跃游戏 II

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int jump(vector<int>& nums) {
    //思路：这个有点像背包问题，但又不是
    //正常考虑，在第一个位置的时候，我们能知道下一步能到的位置，所以选择就是在这些位置中找最快到达最后一个位置的点
    //有点像图了，找最短路径。。。
    //我们类似广度优先遍历，每次推进一步，直到有一步能到最后一个位置。。。

    int n = nums.size();
    if(n <= 1)
    {
        return 0;
    }

    queue<int> qu;
    vector<bool> arrived(n,false);
    arrived[0] = true;
    qu.push(0);
    int count = 0;
    while(!qu.empty())
    {
        ++count;
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            int p = qu.front();
            qu.pop();

            for(int j=1;j<=nums[p] && p+j<n;++j)
            {
                if(p+j == n-1)
                {
                    return count;
                }
                if(!arrived[p+j])
                {
                    qu.push(p+j);
                    arrived[p+j] = true;
                }
            }
        }
    }

    return n-1;
}

int jump2(vector<int>& nums) {
    //思路：图的思路超时了，主要是每一个位置的选择太多，能跳n步就有n步的选择
    //这个时候我们需要优化这一步，因为能跳的位置是连续的，是否可以不用遍历？
    //到达位置期望是i+nums[i],我们能否采用贪心，也就是每次都选能够得着的位置中期望最大的那个？
    //这个应该不行，因为这只是对下一步最优，并不一定后面第二步会最优
    //换一个思路，我们从第一步跳出去，有nums[0]个候选位置，第一步能到的最远位置是nums[0]
    //接下来考虑第二步，在第j个位置最远可以跳到j+nums[j]，所以第二步能到的最远位置是第一步的候选位置的最大期望
    //小于这个最大期望的值都是可达的，所以第二步区间就是{nums[0],max{j+nums[j] | j > nums[0]}}
    //同理第三步，最后只要有一步的最远期望大于等于n-1即可

    int n = nums.size();
    int step = 0;
    int start = 0,end = 0;
    while(end < n-1)
    {
        ++step;
        int mx = 0;
        for(int j=start;j<=end;++j)
        {
            mx = max(mx,j+nums[j]);
        }

        start = end+1;
        end = mx;
    }

    return step;
}

int jump3(vector<int> nums)
{
    //贪心，每次选择最远位置,跟上面的思路其实是一样的。。。。
    int length = nums.size();
    int end = 0;
    int maxPosition = 0; 
    int steps = 0;
    for (int i = 0; i < length - 1; i++) {
        maxPosition = max(maxPosition, i + nums[i]); 
        if (i == end) {
            end = maxPosition;
            steps++;
        }
    }
    return steps;
}

int main()
{
    vector<int> nums ={2,3,1,1,4}; //2
    // nums = {1};

    printf("%d\n",jump2(nums));
    return 0;
}