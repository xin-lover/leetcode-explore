#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

//leetcode 556. 下一个更大元素 III
int nextGreaterElement(int n) {
    //思路：123表示1,2,3的组合，其下一个比它更大的数是132
    //所以把数字先解析为数组，然后从右开始遍历，维持一个递增栈，直到一个数小于栈顶元素，然后交换最小元素和这个数

    vector<int> v;
    while(n > 0)
    {
        v.push_back(n % 10);
        n /= 10;
    }

    for(int i=1;i<v.size();++i)
    {
        if(v[i] < v[i-1])
        {
            printf("sss i:%d v[i]:%d\n",i,v[i]);
            //使用前面刚好大于v[i]的数字替换它，然后再把0-i的数组逆序
            for(int j=i-1;j>=0;--j)
            {
                if(v[i] >= v[j])
                {
                    printf("wy\n");
                    swap(v[i],v[j+1]);
                    break;
                }
                else if( j == 0)
                {
                    swap(v[i],v[0]);
                }
            }

            for(int j=0;j<v.size();++j)
            {
                printf("%d ",v[j]);
            }
            printf("\n");

            //反转,保持0--i-1最小
            for(int j=0;j<i/2;++j)
            {
                swap(v[j],v[i-1-j]);
            }

             for(int j=0;j<v.size();++j)
            {
                printf("%d ",v[j]);
            }
            printf("\n");

            int res = 0;
            int base = 1;
            for(int j=0;j<v.size();++j)
            {
                res += v[j]*base;
                base *=10;
            }

            return res;
        }
        
    }

    return -1;
}

int main()
{
    printf("%d\n",nextGreaterElement(1));
    printf("%d\n",nextGreaterElement(12));
    printf("%d\n",nextGreaterElement(21));
    printf("%d\n",nextGreaterElement(136542));
    printf("%d\n",nextGreaterElement(13654));
    printf("%d\n",nextGreaterElement(13653));
    printf("%d\n",nextGreaterElement(12443322));
    return 0;
}