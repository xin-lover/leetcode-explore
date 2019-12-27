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

int minScoreTriangulation2(vector<int>& A,int start,int end) {
    
    //start和end相连且最小，所以找start到end之间的最小值切分即可
    int mn = start+1;
    for(int i=start+2;i<A.size();++i)
    {
        if(A[i] < A[mn])
        {
            mn = i;
        }
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
}

int main()
{
    vector<int> A = {1,2,3};//6
    A = {3,7,4,5}; //144
    // A = {1,3,1,4,1,5}; //13
    printf("%d\n",minScoreTriangulation(A));
    return 0;
}