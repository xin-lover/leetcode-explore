#include <cstdio>
#include <vector>

using namespace std;

int getComCount(int n)
{
    int sum =0;
    for(int i=3;i<=n;++i)
    {
        sum+=n-i + 1;
    }   

    return sum;
}
int numberOfArithmeticSlices(vector<int>& A) {
    //一个等差数列，其子数组也是等差数列，所以找到等差数列，计算子数组即可

    if(A.size() < 3)
    {
        return 0;
    }

    int res = 0;
    for(int i=0;i<A.size()-2;++i)
    {
        bool mark = true;
        int d = A[i+1]-A[i];
        printf("d:%d\n",d);
        for(int j=i+2;j<A.size();++j)
        {
            if(A[j]-A[j-1] != d)
            {
                mark = false;
                printf("j:%d\n",j);
                if(j - 1 - i >= 2)
                {
                    res += getComCount(j-i);
                    i=j-2;
                    printf("res:%d i:%d\n",res,i);
                }
                
                break;
            }
        }

        if(mark)
        {
            printf("mark:%d i:%d\n",mark,i);
            return res += A.size() - i >= 3 ? getComCount(A.size()-i) : 0; 
        }
    }

    return res;
}

int main()
{
    vector<int> v = {1,2,3,4};
    // printf("%d\n",numberOfArithmeticSlices(v));
    // v={1,2,3,6,7,8};
    // printf("%d\n",numberOfArithmeticSlices(v));
    // v={1,2,3,5,7};
    // printf("%d\n",numberOfArithmeticSlices(v));
    // v={1,2,4,5,7};
    // printf("%d\n",numberOfArithmeticSlices(v));
    v={1,2,3,4,5,7,10};
    printf("%d\n",numberOfArithmeticSlices(v));
    
    return 0;
}