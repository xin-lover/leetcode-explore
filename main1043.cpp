//1043. 分隔数组以得到最大和

#include <cstdio>
#include <vector>

using namespace std;

int maxSumAfterPartitioning(vector<int>& A, int K) {
    //思路：是长度最大为K的子数组，而最大值我们就可以理解为波峰
    //那在这个波形中所有的值都会变为这个最大值
    //我们先遍历，假设我们碰到一个波峰在第i个位置，那么如果i+1小于K，那么毫无疑问都归到这个子数组中
    //也就是先构建一个i+1长度的子数组，至于i到K-1这些元素要根据下一个峰值来判定了，如果下一个峰值小于当前峰值，元素就归到当前子数组
    //但这里可能出现的情况就是下一个峰值也会有这样的一些元素存在，那么这两段元素不可能都能分到这个子数组，所以这里这些元素不能简单的这样分
    //一个可行的分割是这样，先选择一个最大的数，然后在基于它构建一个K长度的子数组，选择的其余k-1个元素的策略是它们的和最小

    //这个贪心策略不行，遇到[10,9,3,2],k=2时，明显应该是[10,9,9,2]，而不是[10,10,3,3]

    vector<int> ids;
    for(int i=0;i<A.size();++i)
    {
        ids.push_back(i);
    }

    sort(ids.begin(),ids.end(),[A](int a,int b)
    {
        return A[a]>A[b];
    });

    for(int i=0;i<ids.size();++i)
    {
        int p = ids[i];
        printf("p:%d\n",p);
        if(A[p]<0)
        {
            continue;
        }
        int len = K-1;
        int left = p-1,right=p+1;
        while(len>0)
        {
            if(left < 0 || A[left] < 0)
            {
                if(right >= A.size() || A[right] < 0)
                {
                    break;
                }
                else
                {
                    ++right;
                }
            }
            else
            {
                if(right >= A.size() || A[right] < 0)
                {
                    --left;
                }
                else
                {
                    if(A[left] > A[right])
                    {
                        ++right;
                    }
                    else
                    {
                        --left;
                    }
                }
            }

            --len;
        }

        int t = A[p];
        printf("left:%d right:%d\n",left,right);
        for(int j=left+1;j<=right-1;++j)
        {
            printf("%d ",A[j]);
            A[j] = -t;
        }
        printf("\n");
    }

    int sum = 0;
    for(int i=0;i<A.size();++i)
    {
        printf("%d ",A[i]);
        sum +=A[i];
    }
    printf("\n");

    return -sum;
}

int maxSumAfterPartitioning2(vector<int>& A, int K) {
    //思路：什么情况下我们可以确定某个数的变换？
    //使用动归，dp[i]表示包含第i个数时的最大和
    //那么,dp[i] = max{dp[i-k]+max(A[i]~A[i+K])*K,dp[i-k+1]+max(A[i]~A[i-k+1,~A[i]]).......))}

    vector<int> dp(A.size()+1,0);
    dp[0]=0;
    for(int i=0;i<A.size();++i)
    {
        int x = A[i];
        // dp[i+1] = x;
        for(int j=0;j<K;++j)
        {
            if(i-j<0)
            {
                break;
            }
            x = max(x,A[i-j]);
            dp[i+1] = max(dp[i+1],dp[i-j]+x*(j+1));
        }
        printf("%d\n",dp[i+1]);
    }

    return dp.back();
}

int main()
{
    vector<int> A = {1,15,7,9,2,5,10};
    int K = 3; //84

    // A = {1,4,1,5,7,3,6,1,9,9,3};
    // K = 4;//83

    // A = {10,9,3,2};
    // K = 2; //30

    printf("%d\n",maxSumAfterPartitioning2(A,K));
    return 0;
}