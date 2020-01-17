//1039. 多边形三角剖分的最低得分

#include <cstdio>
#include <vector>

using namespace std;


int minScoreTriangulation(vector<int>& A) {
    //思路：首先我们需要搞懂切分三角形的过程
    //每一次切一个三角形的时候，就是加一条新边，去掉两条旧边，其实也就是相当于去掉一个顶点
    //小于等于三个顶点的时候停止
    //自然而然想到贪心，如何贪心？
    //首先肯定想到优先把最大的顶点去掉，把A排序
    //这种方式不行

    int n = A.size();
    vector<int> B(n);
    for(int i=0;i<B.size();++i)
    {
        B[i] = i;
    }
    sort(B.begin(),B.end(),[A](int a,int b)
    {
        return A[a] > A[b];
    });

    int sum = 0;
    for(int i=0;i<B.size()-2;++i)
    {
        int p = B[i];
        int last = p; 
        do{
            --last;
            if(last < 0) last+=n;
        }while(A[last]<0);
        int next = p;
        do{
            ++next;
            if(next >= n) next-=n;
        }while(A[next] < 0);

        sum += A[p]*A[last]*A[next];
        A[p] = -A[p];
    }

    return sum;
}

int mt2(vector<int>& A)
{
    if(A.size() < 3)
    {
        return 0;
    }

    if(A.size() == 3)
    {
        return A[0]*A[1]*A[2];
    }

    int mn = 2;
    for(int i=3;i<A.size()-1;++i)
    {
        if(A[i] < A[mn])
        {
            mn = i;
        }
    }

    if(A[0] * A[mn] <= A[1]*A.back())
    {
        vector<int> B,C;
        for(int i=0;i<=mn;++i)
        {
            B.push_back(A[i]);
        }
        
        C.push_back(A[0]);
        for(int i=mn;i<A.size();++i)
        {
            C.push_back(A[i]);
        }

        return mt2(B) + mt2(C);
    }
    else
    {
        vector<int> B;
        for(int i=1;i<A.size();++i)
        {
            B.push_back(A[i]);
        }
        return A[0]*A[1]*A.back() + mt2(B); 
    }
    

}

int minScoreTriangulation2(vector<int>& A) {
    //思路：上面的贪心策略不行，也就是说贪心点不行
    //那我们考虑边，原有的边只会使用一次，如果我们把切分分成一个个的阶段的话
    //上一个阶段新加的边变成下一个阶段初始边，它又会被使用一次
    //每一次切掉一个三角形，去掉两条边，新加一条边
    //如果贪心边，我们切分一个三角形可能加一条边，也可能两条每条边会影响新的三角形，而我们又没有一个选点的策略
    //所以贪心策略不行
    //采用分治，如何把A分成两部分？
    //选择乘积最小但不相连的两个点

    //先把A重新排列，让第一个元素最小，然后接下来在不与第一个点相连的点中选择一个点与第一个点相连，从而分为两个部分
    //问题：有重复元素时有问题，也就是两个元素都是最小值的时候，不一定是第一个最小值能得出最小结果
    //但其实只会有两种情况，因为第一个节点最小，而我们找的又是除了n-1,0,1之外的所有节点的最小值，所以可能比这条边小的只有n-1,1这条边
    //还是不行，考虑[1,2,5,2]

    int n = A.size();
    int mn = 0;
    for(int i=0;i<A.size();++i)
    {
        if(A[i] < A[mn])
        {
            mn = i;
        }
    }

    vector<int> B;
    for(int i=0;i<n;++i)
    {
        B.push_back(A[(mn+i)%n]);
    }

    
    return mt2(B);
}

int minScoreTriangulation3(vector<int>& A) {
    //思路：动归,dp[i][j]表示第i个角到第j个角的最小剖分
    //那么dp[i][j] = min(dp[i][j],dp[i][k]+dp[k][j]+A[i]*A[j]*A[k])

    int n = A.size();
    vector<vector<int>> dp(n,vector<int>(n,INT_MAX));
    for(int i=0;i<n;++i)
    {
        dp[i][(i+1)%n] = 0; //相邻点
    }
    for(int i=2;i<n;++i)
    {
        for(int j=0;j+i<n;++j)
        {
            for(int k=1;k<i;++k)
            {
                dp[j][j+i] = min(dp[j][j+i],dp[j][j+k] + dp[j+k][j+i] + A[j]*A[j+k]*A[j+i]);
            }
        }
    }

    return dp[0][n-1];
}

int main()
{
    vector<int> A = {1,2,3};//6
    // A = {3,7,4,5}; //144
    // A = {1,3,1,4,1,5}; //13
    // A = {3,7,4,5}; //144
    printf("%d\n",minScoreTriangulation3(A));
    return 0;
}