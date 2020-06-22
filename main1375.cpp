//1375. 灯泡开关 III

#include <cstdio>
#include <vector>

using namespace std;

int numTimesAllBlue(vector<int>& light) {
    //思路：开着的灯要想全变成蓝色，那么所有亮着的灯应该刚好连起来
    //这里有两种情况
    //1.所有亮着的灯都在light[k]左侧，就缺light[k]
    //2.所有亮着的灯都连起来了，除了light[k]
    //总结起来就是当前亮着的灯除了light[k]位置，都亮着
    //所以我们记录当前最大亮着的灯位置和亮着的数量，如果一致，说明亮着的灯连起来了，也就变成蓝色了

    int res = 0;
    int mxPos = 0;
    for(int i=0;i<light.size();++i)
    {
        mxPos = max(mxPos,light[i]-1);
        if(mxPos == i)
        {
            ++res;
        }
    }

    return res;
}

int main()
{
    vector<int> light = {2,1,3,5,4};    //3
    light = {3,2,4,1,5};   //2
    light = {4,1,2,3};  //1
    light = {1,2,3,4,5,6};  //6
    printf("%d\n",numTimesAllBlue(light));

    return 0;
}