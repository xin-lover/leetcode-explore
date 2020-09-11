//1552. 两球之间的磁力

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

bool check(int interval,vector<int>& position, int m)
{
    int cnt=1;
    int pre=0;
    for(int i=0;i<position.size() && cnt < m;++i)
    {
        if(position[i]>= position[pre]+interval)
        {
            pre = i;
            ++cnt;
        }
    }

    return cnt >= m;
}

int maxDistance(vector<int>& position, int m) {
    //思路：二分+贪心，漂亮的解法。。。。
    //先对position排序，可得最大间距S，符合要求的间距一定在[1,S]之间
    //剩下的问题就是如何确定间距是否满足要求
    //考虑贪心，我们第一个小球一定选择第一个位置，那么其后的小球我们按选择的间距p找
    //比如第二个找大于等于position[0]+p位置的篮子。。。这样只要篮子够用就行

    sort(position.begin(),position.end());
    int left=1,right=position.back()-position.front();
    int res = 0;
    while(left<=right)
    {
        int mid = left+(right-left)/2;

        if(check(mid,position,m))
        {
            res = mid;
            left=mid+1;
        }
        else
        {
            right = mid-1;
        }
    }

    return res;
}

int main()
{
    vector<int> position = {1,2,3,4,7};
    int m = 3; //3

    position = {5,4,3,2,1,1000000000}, m = 2;   //999999999

    printf("%d\n",maxDistance(position,m));

    return 0;
}