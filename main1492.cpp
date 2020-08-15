//1492. n 的第 k 个因子

#include <cstdio>
#include <vector>

using namespace std;

int kthFactor(int n, int k) {
    //思路：问题是找因子，先一个一个的找吧

    vector<int> pre,post;   //避免重复计算
    for(int i=1;i*i<=n;++i)
    {
        if(n % i == 0)
        {
            pre.push_back(i);
            int p = n / i;
            if(i != p)
            {
                post.push_back(p);
            }   
            
        }
    }

    if(k <= pre.size())
    {
        return pre[k-1];
    }
    else if(k-pre.size() <= post.size())
    {
        reverse(post.begin(),post.end());
        return post[k-pre.size()-1];
    }
    else
    {
        return -1;
    }
    
}

int main()
{
    printf("%d\n",kthFactor(12,3)); //3
    printf("%d\n",kthFactor(1000,3));   //4
    printf("%d\n",kthFactor(1,1));   //1
    printf("%d\n",kthFactor(24,6));   //8

    return 0;
}