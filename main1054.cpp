//1054. 距离相等的条形码

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> rearrangeBarcodes(vector<int>& barcodes) {
    //思路：简单的思路就是统计所有的条形码出现次数
    //然后每两个一组排列，直到其中一个用完
    //但这个思路只能让元素按出现的次数排序,所以还要再按出现次数排一次序
    //这样也不行，按照这个思路，每次用完一组数后，又要重新排列，不现实
    //我们如果就一组一个的排，可能出现的情况就是最长的那个数最后会连续
    //所以我们避免一下这种情况，可以让另一组数单独于多出这些数间隔排列
    //这样就相当于两个数把最多的那个数隔开了
    //但这样仅限于两个数组的长度和大于最长的那个数组
    //所以总结一下就是先用其它数组把最长的那个数组隔开
    //然后再填其它的数

    unordered_map<int,int> um;
    for(auto a : barcodes)
    {
        ++um[a];
    }

    vector<int> ay;
    for(auto it = um.begin();it!=um.end();++it)
    {
        ay.push_back(it->first);
    }

    sort(ay.begin(),ay.end(),[&um](int a ,int b)
    {
        return um[a] > um[b];
    });

    int len = um[ay.front()];
    int sum = 0;
    int c = 0;
    for(int i=1;i<ay.size() && sum < len;++i)
    {
        ++c;
        sum += um[ay[i]];
    }

    int remain = sum - len;
    vector<int> res;
    int j=1;
    for(int k=0;k<len;++k)
    {
        res.push_back(ay[0]);
        --um[ay[0]];
        if(j < ay.size())
        {
            res.push_back(ay[j]);
            --um[ay[j]];
            if(um[ay[j]] == 0)
            {
                ++j;
            }
        }

        for(int i=c+1;i<ay.size();++i)
        {
            if(um[ay[i]] > 0)
            {
                res.push_back(ay[i]);
                --um[ay[i]];
            }
        }
        if(remain>0)
        {
            res.push_back(ay[c]);
            --remain;
        }
    }


    return res;
}

vector<int> rearrangeBarcodes2(vector<int>& barcodes) {
    //思路：上面第一种想法是选取最多的两个码排列，剩余的再次进入集合中，然后排序
    //开始觉得排序太费劲了，题解中有人针对这个情况使用了优先队列。。。。。。算是把排序复杂度降低了
}

int main()
{
    vector<int> A = {1,1,1,2,2,2}; //2,1,2,1,2,1
    // A = {1,1,1,1,2,2,3,3};
    // A = {7,7,7,8,5,7,5,5,5,8};
    A ={1};
    vector<int> res = rearrangeBarcodes(A);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}