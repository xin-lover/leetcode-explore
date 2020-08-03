//1465. 切割后面积最大的蛋糕

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
    //思路：两种切法，一种是先横着切，然后再竖着切，这种切法，每次竖着切都会新生成m块，m=size(horizontalCuts)
    //比较大小即可，第二种切法是一刀横着，一刀竖着，交叉切，这样每次增加的数量不一样，但与第一种切法本质没有不同

    //方案，先记录横着切的高度，然后根据竖着切的坐标记录面积

    sort(horizontalCuts.begin(),horizontalCuts.end());
    sort(verticalCuts.begin(),verticalCuts.end());
    // vector<int> heights(horizontalCuts.size()+1);
    int start = 0;
    int mxh = 0;
    for(int i=0;i<horizontalCuts.size();++i)
    {
        mxh = max(mxh,horizontalCuts[i]-start);
        start = horizontalCuts[i];
    }
    mxh = max(mxh, h - start);

    int tmpArea = 0;
    start = 0;
    int mxw = 0;
    for(int i=0;i<verticalCuts.size();++i)
    {
        int w = verticalCuts[i] -start;
        mxw = max(mxw,w);
        start = verticalCuts[i];
    }
    mxw = max(mxw,w - start);


    static int lmt = pow(10,9) + 7;
    return (static_cast<long long>(mxw % lmt) * (mxh % lmt)) % lmt;
}

int main()
{
    int h = 5, w = 4;
    vector<int> horizontalCuts = {1,2,4}, verticalCuts = {1,3}; //4

    h = 5, w = 4, horizontalCuts = {3,1}, verticalCuts = {1};   //6

    h = 5, w = 4, horizontalCuts = {3}, verticalCuts = {3}; //9

    printf("%d\n",maxArea(h,w,horizontalCuts,verticalCuts));

    return 0;
}