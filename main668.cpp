//668. 乘法表中第k小的数

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int findKthNumber(int m, int n, int k) {
    //思路：首先最小值肯定是1.。。但现在的问题是其它数字可能有多个。。。这个取决于它的因数分解，而且是两个因数
    //现在假设f[i][j]表示i行j列的乘法表的第k小的数，那么f[i+1][j]如何求？
    //它增加了{(i+1)*1,(i+1)*2,....(i+1)*j}，假如i+1 < f[i][j],i+1在数列中的位置无法确定
    //所以最简单的做法是用优先队列，但这个效率不高，而且k的影响很大

    if(k > m*n)
    {
        return 0;
    }
    priority_queue<int> qu;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            qu.push(i*j);
            if(qu.size() > k)
            {
                qu.pop();
            }
        }
    }

    return qu.top();

}

int findKthNumber2(int m, int n, int k) {
    //思路：借鉴632. 最小区间的思路，每一行或者说每一列都是单调递增的
    //所以我们使用优先队列存储每一行当前的最小值，每次取最小值所在的行把其下一个数放入优先队列即可。。。
    //还是超时，复杂度没有降下来
    

    if(k > m*n)
    {
        return 0;
    }
    vector<int> pointers(m,1);

    auto cmp = [&](int a,int b)
    {
        return (a+1) * pointers[a] > (b+1)*pointers[b];
    };

    priority_queue<int,vector<int>,decltype(cmp)> pq(cmp); 

    for(int i=0;i<m;++i)
    {
        pq.push(i);
    }

    int count = 0;
    int res = 0;
    while(count < k)
    {
        int t = pq.top();
        pq.pop();

        res = (t+1)*pointers[t];

        pointers[t]++;
        if(pointers[t] <= n)
        {
            pq.push(t);
        }
        ++count;

    }

    return res;
}

int findKthNumber3(int m, int n, int k) {
    //思路：每一行都是有序的，考虑二分
    //因为乘法表的最大值可以确定是m*n,整体也使用二分

    int left=1,right=m*n;
    while(left<right)
    {
        int mid = left + (right-left)/2;
        
        int sum = 0;
        for(int i=0;i<m;++i)
        {
            int lt=1,rt=n;
            if((i+1)*n<=mid)
            {
                sum += n;
                continue;
            }
            while(lt < rt)
            {
                int dd = lt + (rt-lt)/2;
                if((i+1)*dd <= mid)
                {
                    lt=dd+1;
                }
                else
                {
                    rt = dd;
                }
            }

            sum += rt-1;
        }

// printf("mid:%d sum:%d\n",mid,sum);
        if(sum < k)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }

    return right;
}

int main()
{
    int m = 3, n = 3, k = 5; //3
    m = 2, n = 3, k = 6;    //6
    m = 9895,n=28405, n= 100787757;
    printf("%d\n",findKthNumber3(m,n,k));

    return 0;
}