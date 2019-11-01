//leetcode 955. 删列造序 II

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int minDeletionSize(vector<string>& A) {
    //思路：如果把string看成一个数字，这个数字26进制，删除一位就是减去那一位代表的数
    //按字典排列，考虑两个字符串的情况str1,str2,那么遍历str1,对于str1[i]>str2[i]的位置都应该删除
    //对于第三个字符串我们只需要跟第二个比就行,但这里会出现如果把前面决定了str2大于 str1的部分都删除的话
    //那么应该还要考虑str1，所以我们采用一个策略，记录当前每个没删除的位置的最大字符，后面的都需要比这个大

    if(A.empty())
    {
        return 0;
    }

    //思路错了，不用每一个列都是字典排序。。。。。
    int res = 0;
    string flags= A[0];
    for(int i=1;i<A.size();++i)
    {
        bool bigger = false;
        for(int j=0;j<A[i].size();++j)
        {
            if(flags[j] < 'a')
            {
                continue;
            }

            if(A[i][j] < flags[j])
            {
                if(!bigger)
                {
                    flags[j] = 'a'-1;
                    ++res;
                }
            }
            else if(A[i][j] > flags[j])
            {
                flags[j] = A[i][j];
                bigger = true;
            }
        }
    }

    return res;
}

int minDeletionSize2(vector<string>& A) {

    //思路：只需要最前面的列是字典排序即可
    //主要问题是相等情况的处理，一种思路是把相同的部分看成一个新数组然后求解，但这个需要在确定当前列满足递增的情况
    //换一种思路，就使用之前的26进制，遍历列，也就是当前数字符合严格递增为止

    if(A.empty())
    {
        return 0;
    }

    int res = 0;
    vector<int> flag(A.size(),0);
    for(int j=0;j<A[0].size();++j)
    {
        bool inc = true;
        bool strict = true;
        int mx = 0;
        for(int i=0;i<A.size();++i)
        {
            int p = flag[i] * 26 + A[i][j];
            if(p < mx)
            {
                ++res;
                inc = false;
                break;
            }
            else if(p == mx)
            {
                strict = false;
            }
            else
            {
                mx = p;
            }
            
        }

        if(inc)
        {
            if(strict)
            {
                return res;
            }
            for(int i=0;i<A.size();++i)
            {
                flag[i] = flag[i] * 26 + A[i][j];
            }
        }
    }

    return res;
}

int minDeletionSize3(vector<string>& A) {
    //思路：必须保证前面的是递增的，所以我们遍历的时候把非递增的列先删除

    //问题，还是后面会把影响前面判读的大小的列删除了
    if(A.empty())
    {
        return 0;
    }
    int res =0;
    vector<bool> flags(A[0].size(),false);
    for(int i=1;i<A.size();++i)
    {
        printf("i:%d\n",i);
        for(int j=0;j<A[i].size();++j)
        {
            if(flags[j])
            {
                continue;
            }

            printf("%c %c\n",A[i][j],A[i-1][j]);
            if(A[i][j] < A[i-1][j])
            {
                flags[j] = true;
                ++res;
            }
            else if(A[i][j] > A[i-1][j])
            {
                break;
            }
            else
            {
                //do nothing
            }
            
        }
    }

    return res;
}
int minDeletionSize4(vector<string>& A) {
    //思路：改进上面的思路，即每一列dd
}

int main()
{
    vector<string> A = {"ca","bb","ac"};//1
    A = {"xc","yb","za"};//0
    A = {"zyx","wvu","tsr"};//3
    // A = {"abx","agz","bgc","bfc"};//1
    A = {"doeeqiy","yabhbqe","twckqte"};//3
    printf("%d\n",minDeletionSize3(A));

    return 0;
}