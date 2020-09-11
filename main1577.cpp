//1577. 数的平方等于两数乘积的方法数

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int numTriplets(vector<int>& nums1, vector<int>& nums2) {
    //思路：模拟，暴力求解吧

    unordered_map<long long,int> st1,st2;
    for(auto a : nums1)
    {
        st1[static_cast<long long>(a)*a]++;
    }
    for(auto a : nums2)
    {
        st2[static_cast<long long>(a)*a]++;
    }

    //可以统计次数，但先不这么做了
    int res = 0;
    for(int i=0;i<nums1.size();++i)
    {
        for(int j=i+1;j<nums1.size();++j)
        {
            int t = nums1[i]*nums1[j];
            if(st2.find(t) != st2.end())
            {
                res+=st2[t];
            }
        }
    }

    for(int i=0;i<nums2.size();++i)
    {
        for(int j=i+1;j<nums2.size();++j)
        {
            int t = nums2[i]*nums2[j];
            if(st1.find(t) != st1.end())
            {
                res+=st1[t];
            }
        }
    }

    return res;
}

int main()
{
    vector<int> nums1 = {7,4}, nums2 = {5,2,8,9}; //1
    // nums1 = {1,1}, nums2 = {1,1,1}; //9
    nums1 = {4,7,9,11,23}, nums2 = {3,5,1024,12,18};

    printf("%d\n",numTriplets(nums1,nums2));

    return 0;
}