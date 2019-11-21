//leetcode 969. 煎饼排序
#include <cstdio>
#include <vector>

using namespace std;

vector<int> pancakeSort(vector<int>& A) {
    //思路：A是1到n的序列，因为要翻转前n个数，1个可以采取的方案就是先把大的数排列好
    //假设最大的数在位置n，则先翻转n，这样大数到0位置，再翻转整个数列，大数就到末尾了
    //这样，最极端的情况就是每个数排两次
    //复杂度在每次翻转后数列就变了，所以序号要重新排

    int n = A.size();
    // vector<int> B(n);
    // for(int i=0;i<n;++i)
    // {
    //     B[A[i]-1] = i;
    // }

    int seq = 0;
    vector<int> res;
    for(int k=n;k>1;--k)
    {
        for(int i=0;i<k;++i)
        {
            if(A[i] == k)
            {
                seq = i;
        printf("k:%d seq:%d\n",k,seq);
                break;
            }
        }

        if(seq == k-1)
        {
            continue;
        }

        //第一次翻转
        if(seq != 0)
        {
            res.push_back(seq+1);
            for(int i =0;i<=seq/2;++i)
            {
                swap(A[i],A[seq-i]);
            }
                    for(auto a : A)
            {
                printf("%d ",a);
            }
            printf("\n-----------\n");
        }

        //第二次翻转
        res.push_back(k);
        for(int i=0;i<=(k-1)/2;++i)
        {
            swap(A[i],A[k-1-i]);
        }

        for(auto a : A)
        {
            printf("%d ",a);
        }
        printf("\n");

    }
    return res;
}

int main()
{
    vector<int> v = {3,2,4,1}; //3 4 2 3 2
    v = {1,2,3}; //[]
    vector<int> res = pancakeSort(v);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}