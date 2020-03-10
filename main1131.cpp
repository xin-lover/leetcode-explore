//1131. 绝对值表达式的最大值

#include <cstdio>
#include <vector>

using namespace std;

//|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
    //思路：最简单的方式就是穷举了，也就是O(n^2)的复杂度
    //既然暴力解不可行，那么我们就需要思考有没有更好的办法，已知要求 |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j| 的最大值，我们可以先考虑一下子问题的求解：

// 子问题 1. 求 |arr1[i] - arr1[j]| 的最大值
// 这就比较简单了，可以直观地看出来答案，一个数组 arr1 里两个元素差的绝对值的最大值，应该等于 max(arr1) - min(arr1)
// 子问题 2. 求 |arr1[i] - arr1[j]| + |i - j| 的最大值
// 比上一题复杂了一点，观察并不能得出答案，因此，不妨把表达式的绝对值符号去掉，看看展开后会得到怎样的结果：
// abs( arr1[i] - arr1[j]) + abs(i - j) 
// =  arr1[i] - arr1[j] + i - j =  (arr1[i] + i) - (arr1[j] + j) # 式1
// =  arr1[i] - arr1[j] - i + j =  (arr1[i] - i) - (arr1[j] - j) # 式2
// = -arr1[i] + arr1[j] + i - j = -(arr1[i] - i) + (arr1[j] - j) # 式3
// = -arr1[i] + arr1[j] - i + j = -(arr1[i] + i) + (arr1[j] + j) # 式4
// 因为 i 和 j 是可以互换的，所以式 11 等价于式 44， 式 22 等价于式 33，因此可以得到：

// abs( arr1[i] - arr1[j]) + abs(i - j) 
// = (arr1[i] + i) - (arr1[j] + j) ------式1
// = (arr1[i] - i) - (arr1[j] - j) ------式2

// 现在不难发现， 原始表达式的值只取决于两个中间表达式：
// 中间表达式 A = arr1[i] + i
// 中间表达式 B = arr1[i] - i
// 所以有：
// max(abs( arr1[i] - arr1[j]) + abs(i - j) )
// = max((arr1[i] + i) - (arr1[j] + j),
//       (arr1[i] - i) - (arr1[j] - j))
// = max( max(A) - min(A),
//        max(B) - min(B))
// 因此，不难得到子问题的求解代码如下：

// class Solution(object):
//     def maxAbsValExpr(self, arr1, arr2):
//         """
//         :type arr1: List[int]
//         :type arr2: List[int]
//         :rtype: int
//         """
//         A = []
//         B = []
//         for i, x in enumerate(arr1):
//             A.append(x + i)
//             B.append(x - i)
//         return max(max(A) - min(A), max(B) - min(B))
// 现在已经知道了子问题如何求解，那么本题也可以采用相同的解法，首先把绝对值符号去掉，展开表达式：

// |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
 
//  =  (arr1[i] + arr2[i] + i) - (arr1[j] + arr2[j] + j)
//  =  (arr1[i] + arr2[i] - i) - (arr1[j] + arr2[j] - j)
//  =  (arr1[i] - arr2[i] + i) - (arr1[j] - arr2[j] + j)
//  =  (arr1[i] - arr2[i] - i) - (arr1[j] - arr2[j] - j)
//  = -(arr1[i] + arr2[i] + i) + (arr1[j] + arr2[j] + j)
//  = -(arr1[i] + arr2[i] - i) + (arr1[j] + arr2[j] - j)
//  = -(arr1[i] - arr2[i] + i) + (arr1[j] - arr2[j] + j)
//  = -(arr1[i] - arr2[i] - i) + (arr1[j] - arr2[j] - j)
 
// 因为存在四组两两等价的展开，所以可以优化为四个表达式：
// A = arr1[i] + arr2[i] + i
// B = arr1[i] + arr2[i] - i
// C = arr1[i] - arr2[i] + i
// D = arr1[i] - arr2[i] - i

// max( |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|)
// = max(max(A) - min(A),
//       max(B) - min(B),
//       max(C) - min(C),
//       max(D) - min(D))

    int A1,B1,C1,D1;
    int A2,B2,C2,D2;
    A1 = B1 = C1 = D1 = INT_MIN;
    A2 = B2 = C2 = D2 = INT_MAX;
    for(int i=0;i<arr1.size();++i)
    {
        int a = arr1[i]+arr2[i]+i;
        A1 = max(A1,a);
        A2 = min(A2,a);

        int b = arr1[i] + arr2[i]-i;
        B1 = max(B1,b);
        B2 = min(B2,b);

        int c = arr1[i] - arr2[i]+i;
        C1 = max(C1,c);
        C2 = min(C2,c);

        int d = arr1[i]-arr2[i]-i;
        D1 = max(D1,d);
        D2 = min(D2,d);
    }

    return max(max(A1-A2,B1-B2),max(C1-C2,D1-D2));
}

//另一种理解：
// 我们将 arr1 中的所有值看做平面上点的横坐标，将 arr2 中的所有值看做平面上点的纵坐标，那么表达式 |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|，前两项就可以看成是平面上两点的曼哈顿距离，整个式子就是要求两个点的曼哈顿距离与两个点索引差的和。
// 由于有取绝对值的操作存在，那么可能产生的计算有 4 种，分别为：右上减左下，右下减左上，左上减右下，左下减右上。以测试样例为例，第一组样例如左图，右上减左下取得最大值为 3 + 7 + 3 = 13；第二组样例如右图，右下减左上取得最大值为 15 + 3 + 2 = 20。
//这种思路有点说不过去，前半段是可以的，但还有个索引之差，思路过不去

//用三维曼哈顿距离可以过去
// 看一眼时间复杂度，用暴力肯定超时，仔细想想可以把这个题抽象为求三维曼哈顿距离的最大值
// dist = |x_i - x_j| + |y_i - y_j| + |z_i - z_j|
// dist=∣xi−xj∣+∣yi−y j∣+∣zi ​	−zj∣ 
// 分析：
// dist这个表达式去绝对值后，x_i，y_i，z_ixi，yi，zi ​	

//  只可能有八种情况
// 1：x_i + y_i + z_i，2：x_i + y_i - z_i, ...，8：-x_i - y_i - z_i1：x i ​	+y i ​	+z i ​	，2：x i ​	+y i ​	−z i ​	,...，8：−x i ​	−y i ​	−z i
// ​	
// 可以发现每一种情况对应的x_j, y_j, z_jx j ​	,y j ​	,zj, 一定也能被确定下来（对应符号相反），比如：x_i + y_i - z_ix i ​	+y i ​	−z i ​	
//  这种情况，一定是dist = (x_i + y_i - z_i)+(-x_j - y_j + z_j)dist=(x i ​	+y i ​	−z i ​	)+(−x j ​	−y j ​	+z j ​	)
// 所以我们只需要先用O(n)O(n)的复杂度求出点ii的八种情况分别对应的最大值maxv[k], k=0,..8maxv[k],k=0,..8，然后再用O(n)O(n)的复杂度枚举每一种去绝对值的组合，取八种组合中的最大值即为最终结果
// 进一步可以求d维的曼哈顿距离，情况有2^d2 d 种，时间复杂度为O(2^d n)O(2 d n)

int main()
{
    vector<int> arr1 = {1,2,3,4}, arr2 = {-1,4,5,6};
    printf("%d\n",maxAbsValExpr(arr1,arr2));
    return 0;
}