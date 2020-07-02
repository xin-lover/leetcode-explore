//1395. 统计作战单位数

#include <cstdio>
#include <vector>

using namespace std;

int numTeams(vector<int>& rating) {
    //思路：确定前两个分数，最后一个分数就很容易确定了，更进一步，确定中间的分数，那么那么我们只需要前面选取大于它的数和后面选取小于它的数即可
    //如何快速的确定大于小于某个数的个数？先线性查找吧

    int res = 0;
    for(int i=0;i<rating.size();++i)
    {
        int left_max=0;
        int left_min = 0;
        for(int j=0;j<i;++j)
        {
            if(rating[j] > rating[i])
            {
                left_max++;
            }
            else 
            {
                left_min++;
            }
        }

        int right_max=0,right_min = 0;
        for(int j=i+1;j<rating.size();++j)
        {
            if(rating[j] > rating[i])
            {
                right_max++;
            }
            else 
            {
                right_min++;
            }
        }

        res += left_max * right_min + left_min * right_max;
    }

    return res;
}

//离散化数组,优化上面left_max等4个数的查找过程，利用桶的思想，如果i存在，则该桶的值为1，这样可以使用前缀和的思想求出大于或小于某个值的个数
//树状数组（二元索引树），一种动态维护前缀和的数据结构。
//对于树状数组，重点是动态修改
class Solution {
public:
    static constexpr int MAX_N = 200 + 5;

    int c[MAX_N];
    vector <int> disc;
    vector <int> iLess, iMore, kLess, kMore;

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int p, int v) {
        while (p < MAX_N) {
            c[p] += v;
            p += lowbit(p);
        }
    }

    int get(int p) {
        int r = 0;
        while (p > 0) {
            r += c[p];
            p -= lowbit(p);
        }
        return r;
    }

    int numTeams(vector<int>& rating) {
        disc = rating;
        disc.push_back(-1);
        sort(disc.begin(), disc.end());
        auto getId = [&] (int target) {
            return lower_bound(disc.begin(), disc.end(), target) - disc.begin();
        };


        iLess.resize(rating.size());
        iMore.resize(rating.size());
        kLess.resize(rating.size());
        kMore.resize(rating.size());

        //整体的思路还是求iless这些数值，不过使用树状数组来计算前缀和，同时利用动态更新，也就是树状数组维护的是元素数量，而不是具体值了
        memset(c, 0, sizeof c);
        for (int i = 0; i < rating.size(); ++i) {
            auto id = getId(rating[i]);
            iLess[i] = get(id); //这里的计算很有意思，id是排序后的序号，而get的时候因为后面的id还没有添加，所以get得到的数量也就是已添加id的数量
            iMore[i] = get(201) - get(id); 
            add(id, 1); 
        }

        memset(c, 0, sizeof c);
        for (int i = rating.size() - 1; i >= 0; --i) {
            auto id = getId(rating[i]);
            kLess[i] = get(id);
            kMore[i] = get(201) - get(id); 
            add(id, 1);
        }
        
        int ans = 0;
        for (unsigned i = 0; i < rating.size(); ++i) {
            printf("%d %d %d %d\n",iLess[i],iMore[i],kLess[i],kMore[i]);
            ans += iLess[i] * kMore[i] + iMore[i] * kLess[i];
        }

        return ans;
    }
};

int main()
{
    vector<int> rating = {2,5,3,4,1}; //3
    // rating = {2,1,3};   //0
    // printf("%d\n",numTeams(rating));
    Solution s;
    printf("%d\n",s.numTeams(rating));
    return 0;
}