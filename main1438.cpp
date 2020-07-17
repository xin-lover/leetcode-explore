//1438. 绝对差不超过限制的最长连续子数组

#include <cstdio>
#include <vector>
#include <stack>
#include <map>

using namespace std;

int longestSubarray(vector<int>& nums, int limit) {
    //思路：其实就是找最大最小值，之前好像有类似的题，当时考虑的浮动窗口
    //但浮动窗口的问题在于移除的是最大或最小值的时候，需要再次查找最大或最小值的位置
    //考虑单调栈，单调栈只能记录单调的最大值，而我们需要的是每一个区间的最大值
    //我们假设，在第i个位置碰到一个新的最大值，它超过了限制，那么我们的需要找到另一个最小值是它符合要求
    //也就是在最小值的索引之后继续找另一个最小值，遇到了新的最小值同理
    //先用O(n^2)的方案解决

    //超时

    int res = 0;
    int start = 0;
    int mxi=0,mni=0;
    for(int i=0;i<nums.size();++i)
    {
        if(nums[i] > nums[mxi])
        {
            mxi = i;
            while(nums[mxi] - nums[mni] > limit)
            {
                //找新的最小值
                ++mni;
                start = mni;
                for(int j=mni+1;j<i;++j)
                {
                    if(nums[j] < nums[mni])
                    {
                        mni = j;
                    }
                }
            }
        }
        else if(nums[i] < nums[mni])
        {
            mni = i;
            while(nums[mxi] - nums[mni] > limit)
            {
                ++mxi;
                start = mxi;
                for(int j=mxi+1;j<i;++j)
                {
                    if(nums[j] > nums[mxi])
                    {
                        mxi = j;
                    }
                }
            }
        }

        res = max(res,i-start+1);
    }

    return res;
    // stack<int> skmax;
    // stack<int> skmin;

    // int res = 0;
    // int start = -1;
    // for(int i=0;i<nums.size();++i)
    // {
    //     if(skmax.empty() || (nums[i] >= nums[skmax.top()]))
    //     {
    //         skmax.push(i);
    //     }

    //     if(skmin.empty() || (nums[i] <= nums[skmin.top()]))
    //     {
    //         skmin.push(i);
    //     }

    //     if(nums[skmax.top()] - nums[skmin.top()] <= limit)
    //     {
    //         res = max(res,i-start);
    //     }
    //     else
    //     {
    //         while(nums[skmax.top()] - nums[skmin.top()] > limit)
    //         {
    //             if(skmax.top() < skmin.top())
    //             {
    //                 start = skmax.top();
    //                 skmax.pop();
    //             }
    //             else
    //             {
    //                 start = skmin.top();
    //                 skmin.pop();
    //             }
                
    //         }
    //     }
        
    // }

}

void reverseStack(stack<int>& sk)
{
    stack<int> tmp;
    while(!sk.empty())
    {
        tmp.push(sk.top());
        sk.pop();
    }

    swap(tmp,sk);
}

int longestSubarray2(vector<int>& nums, int limit) {

    //优化上面的算法，既然再次查找新的最小值最大值是线性复杂度，
    //我们考虑单调栈，递增栈保存最小值的递增序列
    //这样，如果遇到最大值的时候，我们直接考虑次一级大的最小值，如果还是不符合要求，继续这个过程
    //因为从前往后考虑，对于栈，需要把弹出的数据再次保存

    int res = 0;
    int start = 0;
    int mxi=0,mni=0;

    stack<int> skmax,skmin;
    for(int i=0;i<nums.size();++i)
    {
        //再次遇到最大值时,选取新的最小值
        if(nums[i] > nums[mxi])
        {
            mxi = i;

            //清空
            while(!skmax.empty())
            {
                skmax.pop();
            }

            printf("hh:%d %d\n",mxi,mni);
            if(nums[mxi] - nums[mni] > limit)
            {
                stack<int> tmp;
                printf("i:%d ss:%d\n",i,skmin.size());
                while(!skmin.empty() && (nums[mxi] - nums[skmin.top()] <= limit))
                {
                    //找新的最小值
                    mni = skmin.top();
                    tmp.push(mni);
                    skmin.pop();
                }

                if(skmin.empty())
                {
                    start = i; 
                    mni = i;
                }
                else
                {
                    start = skmin.top()+1;
                    mni = mni < start ? start : mni;
                }

                swap(skmin,tmp);
                reverseStack(skmin);
            }
        }
        else if(nums[i] < nums[mni])
        {
            mni = i;

            //清空
            while(!skmin.empty())
            {
                skmin.pop();
            }

            if(nums[mxi] - nums[mni] > limit)
            {
                stack<int> tmp;
                while(!skmax.empty() && (nums[skmax.top()] - nums[mni] <= limit))
                {
                    //找新的最大值
                    mxi = skmax.top();
                    tmp.push(mxi);
                    skmax.pop();
                }

                if(skmax.empty())
                {
                    start = i; 
                    mni = i;
                }
                else
                {
                    start = skmax.top()+1;
                    mxi = mxi < start ? start : mxi;
                }
                
                swap(tmp,skmax);
                reverseStack(skmax);
            }
        }

        while(!skmax.empty() && nums[i] > nums[skmax.top()])
        {
            skmax.pop();
        }
        skmax.push(i);
        while(!skmin.empty() && nums[i] < nums[skmin.top()])
        {
            skmin.pop();
        }
        skmin.push(i);

        printf("%d i:%d start:%d\n",i-start+1,i,start);
        res = max(res,i-start+1);
    }

    return res;
}

int longestSubarray3(vector<int>& nums, int limit) {

    //reversestack太耗时，所以用vector来代替，不反转

    int res = 0;
    int start = 0;
    int mxi=0,mni=0;

    vector<int> skmax,skmin;
    int p_max=0,p_min=0;
    for(int i=0;i<nums.size();++i)
    {
        //再次遇到最大值时,选取新的最小值
        if(nums[i] > nums[mxi])
        {
            mxi = i;

            //清空
            skmax.clear();
            p_max = 0;

            if(nums[mxi] - nums[mni] > limit)
            {
                int j = skmin.size()-1;
                while(j>=p_min && (nums[mxi] - nums[skmin[j]] <= limit))
                {
                    //找新的最小值
                    mni = skmin[j];
                    --j;
                }

                if(j < p_min)
                {
                    start = i; 
                    mni = i;
                }
                else
                {
                    start = skmin[j]+1;
                    mni = mni < start ? start : mni;
                }

                p_min = j+1;
            }
        }
        else if(nums[i] < nums[mni])
        {
            mni = i;

            //清空
            skmin.clear();
            p_min = 0;

            int j = skmax.size()-1;
            if(nums[mxi] - nums[mni] > limit)
            {
                while(j>=p_max && (nums[skmax[j]] - nums[mni] <= limit))
                {
                    //找新的最大值
                    mxi = skmax[j];
                    --j;
                }

                if(j<p_max)
                {
                    start = i; 
                    mni = i;
                }
                else
                {
                    start = skmax[j]+1;
                    mxi = mxi < start ? start : mxi;
                }

                p_max = j+1;
            }
        }

        while(skmax.size() > p_max+1 && nums[i] > nums[skmax.back()])
        {
            skmax.pop_back();
        }
        skmax.push_back(i);
        while(skmin.size() > p_min+1 && nums[i] < nums[skmin.back()])
        {
            skmin.pop_back();
        }
        skmin.push_back(i);

        res = max(res,i-start+1);
    }

    return res;
}

//利用map排序。。。。
int longestSubarray5(vector<int>& nums, int limit) {
    map<int, int> m;
    int ans = 0;
    int i = 0;
    for (int j = 0; j < nums.size(); j++) {
        m[nums[j]]++;
        while (m.rbegin()->first - m.begin()->first > limit) {
            m[nums[i]]--;
            if (m[nums[i]] == 0) {
                m.erase(nums[i]);
            }
            i++;
        }
        ans = max(ans, j - i + 1);
    }
    return ans;
}

//同样的思路，滑动窗口+优先队列也可以。。。。

int main()
{
    vector<int> nums = {8,2,4,7};
    int limit = 4;  //2
    nums = {10,1,2,4,7,2};
    limit = 5;  //4
    // nums = {2,5,2};
    // limit=9;    //3
    nums = {1,2,3,4,5,6,7,8};
    limit = 3; //4
    // nums={3,42,79,52,37,3,21,26,42,73,18,44,55};
    // limit=63;   //7
    printf("%d\n",longestSubarray3(nums,limit));

    return 0;
}