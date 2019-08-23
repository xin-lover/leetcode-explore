//leetcode 835. 图像重叠

#include <cstdio>
#include <vector>

using namespace std;

int BitCount2(unsigned int n)
{
    unsigned int c =0 ;
    for (c =0; n; ++c)
    {
        n &= (n -1) ; // 清除最低位的1
    }
    return c ;
}

//     A = [[1,1,0],
//           [0,1,0],
//           [0,1,0]]
//      B = [[0,0,0],
//           [0,1,1],
//           [0,0,1]]
int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
    //思路：如果把排列看成特征的话，就是寻找相同特征
    //暴力破解，比较会花很多时间
    //一行最多30个数，整形是32位数，所以我们可以使用整形来表示一行或一列，这个整数就是行的特征值
    //然后我们左右移，每一次得到一个特征值，与运算得到1的数量，把所有的相机取最大值

    int n = A.size();
    vector<unsigned int> afeatures(A.size(),0);
    vector<unsigned int> bfeatures(A.size(),0);
    for(int i=0;i<A.size();++i)
    {
        for(int j=0;j<A[0].size();++j)
        {
            if(A[i][j] == 1)
            {
                afeatures[i] |= (1 << (n-j-1));
            }
            if(B[i][j] == 1)
            {
                bfeatures[i] |= (1 << (n-j-1));
            }
        }
    }

    int res = 0;
    //A右移和下移
    for(int i=0;i<A.size();++i)
    {
        for(int j=0;j<A.size();++j)
        {
            int tr1 = 0;
            int tr2 = 0;
            for(int k=0;k<A.size() - j;++k)
            {
                unsigned int t= (afeatures[k] >> i) & bfeatures[k+j];
                tr1 += BitCount2(t);

                t = (bfeatures[k] >> i) & afeatures[k+j];
                tr2 += BitCount2(t);
            }

            res = max(res,tr1);
            res = max(res,tr2);
        }
    }

    return res;


    //还有一个思路：就是记录A和B中所有1的位置，然后让A的每一个1作为左上角移动到B的每一个1上，然后找位置相同的1的个数
    //比如让a(0,0)为1，b(1,1)为1，让a移动到b，则需要加一个位移（1，1），即给A中所有元素都加这个位移，再与B取比较
    //因为查找比较费时，可以使用哈希表快速查找
}

int main()
{
    vector<vector<int>> A = {{1,1,0},
        {0,1,0},
        {0,1,0}};
    vector<vector<int>> B = {{0,0,0},
        {0,1,1},
        {0,0,1}};

    printf("%d\n",largestOverlap(A,B));
    return 0;
}