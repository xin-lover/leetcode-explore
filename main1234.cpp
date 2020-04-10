//1234. 替换子串得到平衡字符串

#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int balancedString(string s) {
    //思路：这道题应该用动态规划
    //因为是替换，所以长度已经确定，最终每个字符的数量也却确定
    //而替换子串，也就是把s分成两部分，s的左边部分和右边部分连起来应该是平衡的，
    //所以我们可以从前和从后遍历记录当前位置出现的次数，然后一个长度一个长度的试，
    //这个复杂度是o(n^2)，空间复杂度是o(n)

    //超时，

    int n = s.size();
    if(n % 4 != 0)
    {
        return -1;
    }

    unordered_map<char,int> um;
    um['Q'] = 0;
    um['W'] = 1; 
    um['E'] = 2; 
    um['R'] = 3; 
    //从前遍历
    vector<int> tmp(4,0);
    vector<vector<int>> dp1(n+1,vector<int>(4,0));
    for(int i=1;i<=n;++i)
    {
        ++tmp[um[s[i-1]]];
        dp1[i] = tmp;
        for(int j=0;j<4;++j)
        {
            dp1[i][j] = tmp[j];
        }
    }

    //从后遍历，也可以不用这个数组，可以记录总的然后计算出这个结果
    tmp = {0,0,0,0};
    vector<vector<int>> dp2(n+1,vector<int>(4,0));
    dp2[n] = tmp;
    for(int i=n-1;i>=0;--i)
    {
        ++tmp[um[s[i]]];
        for(int j=0;j<4;++j)
        {
            dp2[i][j] = tmp[j];
        }
        
    }


    int unit = n/4;
    for(int i=0;i<n;++i)//替换子串长度
    {
        for(int j=0;j<n-i+1;++j)//替换子串开始位置
        {
            bool blance = true;
            int diff = 0;
            for(int k=0;k<dp1[j].size();++k)
            {
                diff += abs(dp1[j][k] + dp2[j+i][k] - unit);
            }
            if(diff == i) 
            {
                return i;
            }
        }
    }

    return -1;
}

int balancedString2(string s) {
    //思路：可以看出问题本质其实是那多了的字符弥补少的字符
    //所以我们只需要关注多余平衡数的字符，假设比平均数多n，那么
    //我们需要选取的区间中必须包含n个该字符，
    //我们可以使用滑动窗口,也就是窗口中包含替换字符的最小长度
    //不用想着去合并区间之类的

    unordered_map<char,int> um;
    for(int i=0;i<s.size();++i)
    {
        ++um[s[i]];
    }

    unordered_map<char,int> need;
    int avg = s.size() / 4;
    for(auto it = um.begin();it != um.end();++it)
    {
        if(it->second > avg)
        {
            need[it->first] = it->second-avg;
        }
    }

    if(need.size() == 0)
    {
        return 0;
    }

    int left=0,right=0;
    int res = s.size();
    int match =0;
    while(right <s.size())
    {
        char c = s[right];
        if(need.find(c) != need.end())
        {
            --need[c];
            if(need[c] == 0)
            {
                ++match;
            }
        }

        ++right;
        while(match == need.size())
        {
            res = min(res,right-left);
            char prec = s[left];
            if(need.find(prec) != need.end())
            {
                ++need[prec];
                if(need[prec] > 0)
                {
                    --match;
                }
            }

            ++left;
        }
    }

    return res;
}

int main()
{
    printf("%d\n",balancedString2("QWER"));//0
    printf("%d\n",balancedString2("QQER"));//1
    printf("%d\n",balancedString2("QQQR"));//2
    return 0;
}