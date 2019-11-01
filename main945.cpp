//leetcode 945. 使数组唯一的最小增量 

#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int minIncrementForUnique(vector<int>& A) {
    //思路：要不重复，那么首先要知道哪些重复的，然后把这些重复的数字插入到不重复的数组中
    //因为只能递增，所以情况就简单的多，优先把小的数字插入到前面的空闲位置
    //方案：先排序，然后遍历找重复项，找到后+1，因为+1后，可能导致后面的数比当前数小，对于这种情况把较小的的数直接置换为当前数+1

    sort(A.begin(),A.end());

    int res = 0;
    for(int i=1;i<A.size();++i)
    {
        if(A[i] <= A[i-1])
        {
            res += A[i-1]-A[i]+1;
            A[i] = A[i-1]+1;
        }
    }

    return res;    
}

int minIncrementForUnique2(vector<int>& A) {
    //思路：把上面的思路优化一下，记录每个数字的次数，然后按同样的思路变化
    //优化失败,可能底层的细节原因，比如map的性能
    if(A.empty())
    {
        return 0;
    }
    map<int,int> mp;
    for(int i=0;i<A.size();++i)
    {
        ++mp[A[i]];
    }

    auto curIt = mp.begin();
    auto nextIt = curIt;
    ++nextIt;

    int res = 0;
    for(;nextIt != mp.end();++curIt,++nextIt)
    {
        int repeat = curIt->second-1;
        int idle = nextIt->first - curIt->first-1;
        if(repeat > idle)
        {
            res += idle*(idle+1) / 2;
            res += (repeat - idle) * (idle+1);
            nextIt->second += (repeat - idle);
        }
        else
        {
            res += repeat * (repeat + 1) / 2;
        }
    }

    curIt = mp.end();
    --curIt;
    int repeat = curIt->second - 1;
    res += repeat * (repeat+1) / 2;
    return res;
}

int minIncrementForUnique3(vector<int>& A) {
    //思路：记录次数，然后对每个出现次数大于等于2的数，然后遇到没有出现的数的时候，如果此时有重复数那就把重复的数字变为它
    //所以一个优化就是：重复的数字x我们可以理解为已经move了x次，对于没有出现的y，那么x变到y需要y-x次，那么对于重复数字x
    //操作数-x，对于未重复数组操作数+y即可

    vector<int> tmp(40001,0);
    for(auto a : A)
    {
        ++tmp[a];
    }

    int res=0,token = 0;
    for(int i=0;i<tmp.size();++i)
    {
        if(tmp[i] > 1)
        {
            token+=tmp[i]-1;
            res -= i * (tmp[i]-1);
        }
        else if(tmp[i] == 0 && token > 0)
        {
            res += i;
            --token;
        }
    }

    return res;
}

//排序的思路优化：还是使用上面的优化方法，遇到重复的x，操作数-x，然后把重复数插入空闲位置
//与map思路一致，但因为不用map，性能可能高一些
//    public int minIncrementForUnique(int[] A) {
//         Arrays.sort(A);
//         int ans = 0, taken = 0;

//         for (int i = 1; i < A.length; ++i) {
//             if (A[i-1] == A[i]) {
//                 taken++;
//                 ans -= A[i];
//             } else {
//                 int give = Math.min(taken, A[i] - A[i-1] - 1);
//                 ans += give * (give + 1) / 2 + give * A[i-1];
//                 taken -= give;
//             }
//         }

//         if (A.length > 0)
//             ans += taken * (taken + 1) / 2 + taken * A[A.length - 1];

//         return ans;
//     }

int main()
{
    vector<int> v = {1,2,2};
    v = {3,2,1,2,1,7};
    // v = {};
    printf("%d\n",minIncrementForUnique3(v));
    return 0;
}