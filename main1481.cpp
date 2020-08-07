//1481. 不同整数的最少数目

#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
    //思路：贪心策略，要种类最少，那么肯定优先移除数量最少的那种
    //方案，先统计种类，然后按数量排序

    map<int,int> mm;
    for(auto a : arr)
    {
        ++mm[a];
    }

    vector<int> counts(mm.size());
    int j = 0;
    for(auto it = mm.begin();it!=mm.end();++it)
    {
        counts[j++]=(it->second);
    }

    sort(counts.begin(),counts.end());

    int res = counts.size();
    int sum = 0;
    for(int i=0;i<counts.size();++i)
    {
        sum += counts[i];
        if(sum > k)
        {
            res = counts.size() - i;
            break;
        }
    }

    if(sum == k)
    {
        return 0;
    }
    
    return res;
}

int main()
{
    vector<int> arr = {5,5,4};
    int k = 1;  //1

    arr = {4,3,1,1,3,3,2}, k = 3;//2
    arr = {1}; k=1;

    printf("%d\n",findLeastNumOfUniqueInts(arr,k));
    return 0;
}