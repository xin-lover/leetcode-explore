//1561. 你可以获得的最大硬币数目

#include <cstdio>
#include <vector>

using namespace std;

int maxCoins(vector<int>& piles) {
    //思路：因为第三个人总是最后选，我们可以让他最少，剩下的两个人分
    //而中间又总是最后选，所以很明显，每次都选择最高的两个

    sort(piles.begin(),piles.end());

    int n = piles.size();
    int u = n / 3;

    int res = 0;
    for(int i=u;i<n;i+=2)
    {
        res += piles[i];
    }

    return res;
}

int main()
{
    vector<int> piles = {2,4,1,2,7,8}; //9
    piles = {9,8,7,6,5,1,2,3,4};    //18
    piles = {2,4,5};    //4

    printf("%d\n",maxCoins(piles));

    return 0;
}