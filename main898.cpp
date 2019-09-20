//leetcode 898. 子数组按位或操作

#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int subarrayBitwiseORs(vector<int>& A) {
    //思路：使用set，因为是连续子数组，所以分组很简单，这个算法可行，但性能一般
    //超时
    //优化，使用map
    //超时，说明还是遍历复杂度高

    unordered_map<int,int> res;
    for(int i=0;i<A.size();++i)
    {
        int t = 0;
        for(int j=i;j<A.size();++j)
        {
            t |= A[j];
            ++res[t];
        }
    }

    return res.size();
}

int subarrayBitwiseORs2(vector<int>& A) {
    //思路：借鉴官方java题解，超时
    //其实就是优化了第二层遍历，从N下降到32
    set<int> cur;
    set<int> res;

    cur.insert(0);

    for(auto a : A)
    {
        set<int> tmp;
        for(auto b : cur)   //这里cur的最多32种
        {
            tmp.insert(a | b);
        }

        tmp.insert(a);
        res.insert(tmp.begin(),tmp.end());
        swap(cur,tmp);
    }

    return res.size();
}

int subarrayBitwiseORs3(vector<int>& A) {
    unordered_set<int> res, cur, cur2;  //优化就是使用unordered_set
    //循环n次，
    for (int i: A) {
        cur2 = {i};
        //i=8时，cur代表的是上一轮的cur2 ，为1|4|2, 4|2, 2  ,并利用set的特性将其中的冗余元素进行了去除
        //最坏情况下，在第n圈中，循环n-1次
        for (int j: cur) cur2.insert(i|j);
        //处理后，cur2代表的是1|4|2|8, 4|2|8, 2|8, 8 并利用set的特性将其中的冗余元素进行了去除
        cur = cur2;
        
        for (int j: cur) res.insert(j);    //对新结果进行了插入
    }
    return res.size();
}

int subarrayBitwiseORs4(vector<int>& A)
{
    int n=A.size();
    int max_val=*max_element(A.begin(),A.end());
    int count=0;
    while(max_val)
    {
        count++;
        max_val/=2;
    }
    int tmp=pow(2,count)-1;
    unordered_set<int> res;
    for(int i=0;i<n;i++)
    {
        res.insert(A[i]);
        int ss=A[i];
        for(int j=i-1;j>=0 && ss<tmp;j--)   //优化点，ss < tmp,也就是提前剪枝
        {
            ss|=A[j];
            res.insert(ss);
        }
    }
    return res.size();
}

int main()
{
    vector<int> v = {1};
    // printf("%d\n",subarrayBitwiseORs2(v));
    // v = {1,1,2};
    // printf("%d\n",subarrayBitwiseORs2(v));
    // v = {1,2,4};
    // printf("%d\n",subarrayBitwiseORs2(v));
    v = {3,11};
    printf("%d\n",subarrayBitwiseORs2(v));
    return 0;
}