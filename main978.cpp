//978. 最长湍流子数组

#include <cstdio>
#include <vector>

using namespace std;

int maxTurbulenceSize(vector<int>& A) {
    //思路：每个数转换符号，也就是单向的，所以
    //直接按序遍历，如果需要不符合预期的情况，重新开始

    if(A.empty())
    {
        return 0;
    }
    int res = 1;
    int dir = 0;
    int tmp =0;
    for(int i=1;i<A.size();++i)   
    {
        if(dir == 0)
        {
            if(A[i] != A[i-1])
            {
                dir = A[i] > A[i-1] ? 1 :-1;
                dir = -dir;
                tmp = 2;
            }
        }
        else
        {
            if(dir*(A[i]-A[i-1]) > 0)
            {
                ++tmp;
                dir = -dir;
            }
            else
            {
                dir = 0;
                --i;
                res = max(tmp,res);
                tmp = 0;
            }
        }
        
    }

    return max(res,tmp);
}

int maxTurbulenceSize2(vector<int>& A) {
    //思路：优化，上面的方法if判断太多

    if(A.empty())
    {
        return 0;
    }
    int res = 1;
    int dir = 1;
    int tmp =1;
    for(int i=1;i<A.size();++i)   
    {
        int t =dir*(A[i]-A[i-1]);
        if(t > 0)
        {
            ++tmp;
            dir = -dir;
        }
        else
        {
            res = max(tmp,res);
            dir = -dir;
            i = (t==0 ? i : i-1);
            tmp = 1;
        }
        
    }

    return max(res,tmp);
}

int main()
{
    vector<int> v = {100};//1
    // v = {9,4,2,10,7,8,8,1,9};//5
    // v = {4,8,12,16};//2
    printf("%d\n",maxTurbulenceSize2(v));
    return 0;
}