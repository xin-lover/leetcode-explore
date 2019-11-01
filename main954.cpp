//leetcode 954. 二倍数对数组

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

bool canReorderDoubled(vector<int>& A) {
    //思路：数组是偶数个元素，根据条件只需要满足条件的数对满足半数即可
    //方案：使用map记录需要的元素，类似双数之和，但这里有个问题，就是顺序问题，比如1,2,4,8,我们如果先配对2，4，那么就少一对
    //简单的方法就是排序，时间复杂度就是排序的复杂度了

    sort(A.begin(),A.end());
    int res = 0;
    unordered_map<int,int> um;
    for(auto a : A)
    {
        printf("a:%d\n",a);
        if(um.find(a) != um.end() && um[a] > 0)
        {
            if(um[a] > 0)
            {
                ++res;
                --um[a];
            }
        }
        else
        {
            ++um[a*2];
            if(a !=0 && a != 1 && a != -1)
            {
                ++um[a / 2];
            }
        }
    }

    return res >= A.size() / 2;
}


bool canReorderDoubled2(vector<int>& A) {
    //思路：先按正负分组，看数量是否符合要求，然后排序
    //本质没变，应该是快了

    vector<int> v1;
    vector<int> v2;

    int count_0 = 0;
    for(auto a : A)
    {
        if(a > 0)
        {
            v1.push_back(a);
        }
        else if(a < 0)
        {
            v2.push_back(a);
        }
        else
        {
            count_0++;
        }
    }

    if(count_0 % 2 != 0)
    {
        return false;
    }

    if(v1.size() % 2 != 0)
    {
        return false;
    }

    int res = 0;
    unordered_map<int,int> um;
    for(auto a : v1)
    {
        if(um.find(a) != um.end() && um[a] > 0)
        {
            --um[a];
            ++res;
        }
        else
        {
            ++um[a];
        }
    }

    if(res*2 != v1.size())
    {
        return false;
    }

    um.clear();
    res = 0;
    for(auto a : v2)
    {
        if(um.find(a) != um.end() && um[a] > 0)
        {
            --um[a];
            ++res;
        }
        else
        {
            ++um[a];
        }
    }

    return res*2==v2.size();
}

int main()
{
    vector<int> A = {4,-2,2,-4};
    A = {-1,-2,-4,-8};
    A = {3,1,3,6};
    A = {0,0,0,0,0,0};
    printf(canReorderDoubled2(A) ? "true\n" : "false\n");
    return 0;
}