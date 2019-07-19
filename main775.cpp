//leetcode 775. 全局倒置与局部倒置

#include <cstdio>
#include <vector>

using namespace std;


bool isIdealPermutation(vector<int>& A) {
    //思路：一种是分别求两种倒置，局部倒置很简单，问题在于全局倒置怎么求，
    //使用暴力求解应该不是题的本意，
    //什么情况下全局倒置会等于局部倒置了？间隔超过1的两个数不能倒置，也就是所有的全局倒置都是局部倒置
    //所以A[i] < {A[i+2],A[i+3]……},这就可以得出0必须在前两位，不然不可能满足这个条件，同理可以得出1只能在1，2位置

    // int local = 0;
    // for(int i=1;i<A.size();++i)
    // {
    //     if(A[i] > A[i-1])
    //     {
    //         ++local;
    //     }
    // }


    for(int i=0;i<A.size();++i)
    {
        if(A[i] != i)
        {
            if(A[i]!=i+1 || A[i+1]!=i)
            {
                return false;
            }
            else
            {
                ++i;
            }
            
        }
    }

    return true;
}

int main()
{
    vector<int> v = {1,2,0};
    // v = {1,0,2};
    printf(isIdealPermutation(v) ? "true\n" : "false\n");
    return 0;
}