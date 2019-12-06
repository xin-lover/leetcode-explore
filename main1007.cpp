//1007. 行相等的最少多米诺旋转

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int minDominoRotations(vector<int>& A, vector<int>& B) {
    //思路：首先要判断是否能有一行相等，因为只有6个数，所以可以存储每个数的位置集合
    //可以用set剔除重复项，那么当set集合的大小等于牌数时才能使其相等
    //很明显，最多有两个集合满足要求，而此时两个集合使等效的，因为最后两行肯定一样
    //所以我们只需要统计其中一行的翻转数k，然后求min(k,A.size()-k)即可
    //这里还不能直接使用第一行的，还需要考虑第二行的，因为目标数字可能在第二行占大多数

    vector<vector<bool>> flags(7,vector<bool>(A.size(),false));
    for(int i=0;i<A.size();++i)
    {
        flags[A[i]][i] = true;
    }
    for(int i=0;i<B.size();++i)
    {
        flags[B[i]][i] = true;
    }

    //统计次数
    int target = -1;
    for(int i=1;i<flags.size();++i)
    {
        int sum = 0;
        for(int j=0;j<flags[i].size();++j)
        {
            sum += flags[i][j] ? 1 : 0;
        }
        if(sum == A.size())
        {
            target = i;
            break;
        }
    }

    if(target == -1)
    {
        return -1;
    }
    printf("target:%d\n",target);

    int sum1 = 0;
    for(int i=0;i<A.size();++i)
    {
        if(A[i] != target)
        {
            ++sum1;
        }
    }
    sum1 = min(sum1,int(A.size()) - sum1);

    int sum2 = 0;
    for(int i=0;i<B.size();++i)
    {
        if(B[i] != target)
        {
            ++sum2;
        }
    }
    sum2 =min(sum2,int(A.size()) - sum2);

    return min(sum1,sum2);
}

int minDominoRotations2(vector<int>& A, vector<int>& B) {
    //思路：上面思路没问题，但步骤太繁琐了
    //因为要行一致，所以一致的数肯定是第一张牌里的两个数中的一个，或者是不能一致
    //所以策略就很简单了：让第一行一致，分别试第一张牌的两个数
    //但因为有一些牌上下是一样的，对于这样的情况如果使用min(count,n-count)是不对的
    //因为上下一样的牌是不需要翻转的，n-count认为这些牌都要翻转
    //另一种写法就是对于A[0]、B[0]求出把它放在上面和下面的4种结果，然后比较


    int n = A.size();
    int same = 0;
    int count1=0,count2=0;
    for(int i=0;i<n;++i)
    {
        if(A[i] == B[i])
        {
            ++same;
        }

        if(count1 != -1)
        {
            if(A[i] != A[0])
            {
                count1 = B[i] == A[0] ? count1+1 : -1;
            }
            
        }

        if(count2 != -1)
        {
            if(B[i] != B[0])
            {
                count2 = A[i] == B[0] ? count2 + 1 : -1;
            }
        }
    }

    int res = n;
    if(count1 != -1)
    {
        res = min(count1,n-count1-same);
    }

    if(count2 != -1)
    {
        res = min(res,min(count2,n-count2-same));
    }

    return res == n ? -1 : res;
}

int main()
{
    vector<int> A = {2,1,2,4,2,2}, B = {5,2,6,2,3,2};
    printf("%d\n",minDominoRotations2(A,B));//2
    A = {3,5,1,2,3}, B = {3,6,3,3,4};
    printf("%d\n",minDominoRotations2(A,B));//-1
    A = {1,2,1,1,1,2,2,2};
    B = {2,1,2,2,2,2,2,2};//1
    printf("%d\n",minDominoRotations2(A,B));
    
    return 0;
}