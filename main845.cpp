//leetcode 845. 数组中的最长山脉

#include <cstdio>
#include <vector>

using namespace std;

int longestMountain(vector<int>& A) {
    //思路：其实就是找波峰
    //策略，记录当前的趋势，山脉是上升和下降的组合，所以记录上升的位置，然后直到下降的点就是波峰点，下降过程中碰到上升的点即可记录长度

    int start = -1;
    int state = 0;
    int res = 0;
    for(int i=1;i<A.size();++i)
    {
        if(A[i] > A[i-1])
        {
            if(state == 0)
            {
                start = i-1;
                state = 1;
            }
            else if(state == 2)
            {
                res = max(res,i-start);
                state = 1;
                start = i-1;
            }
            
        }
        else if(A[i] == A[i-1])
        {
            if(state == 2)
            {
                res = max(res,i-start);
            }
            state = 0;
        }
        else
        {
            if(state == 1)
            {
                state = 2;
            }
        }
    }

    if(state == 2)
    {
        res = max(res,(int)A.size()-start);
    }

    return res;
}

int main()
{
    vector<int> v = {2,1,4,7,3,2,5};
    v = {2,2,2};
    v = {0,1,2,3,4,5,4,3,2,1,0};
    v = {875,884,239,731,723,685};
    printf("%d\n",longestMountain(v));
    return 0;
}