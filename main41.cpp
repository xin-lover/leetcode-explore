#include <cstdio>
#include <vector>

using namespace std;

int magicalString(int n) {
    
    //思路：暴力破解,照规律推演
    //1 22 11 2 1 22 1 22 11 2 11 22
    //1 2 2 1 1 2 1 2 2 1 2 2

    vector<int> nums(n,1);
    nums[1] = 2;
    int p1 = 1;
    int p2 = 1;
    int nextVal = 2;
    int nextCount = 2;
    int res = 1;
    while(p1 < n)
    {
        for(int i=0;i<nextCount && p1 < n;++i,++p1)
        {
            nums[p1] = nextVal;
            if(nextVal == 1)
            {
                ++res;
            }
        }
        ++p2;

        nextCount = nums[p2];
        nextVal = (nextVal == 1 ? 2 : 1);
        printf("p1:%d p2:%d nextVal:%d\n",p1,p2,nextVal);
    }
    
    for(int i=0;i<n;++i)
    {
        printf("%d ",nums[i]);
    }
    printf("\n");
    return res;
}

int main()
{
    printf("%d\n",magicalString(2));
    return 0;
}