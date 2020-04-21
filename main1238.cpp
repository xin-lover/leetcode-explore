//1238. 循环码排列

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

vector<int> circularPermutation2(int n) {

    if(n == 1)
    {
        return {0,1};
    }

    vector<int> res = circularPermutation2(n-1);
    int sz = res.size();
    for(int i=0;i<sz;++i)
    {
        res.push_back(res[sz-1-i] + pow(2,n-1));
    }
    return res;
}
vector<int> circularPermutation(int n, int start) {
    //思路：首尾也仅差一位，那么其实就是一个环了
    //差一个二进制位，也就是差2的j次方
    //考虑2位的时候:00,01,10,11,如果开始为0，我们只有一个选择，把01和10放在0的下一位和末位
    //那么序列也就确定了[00,01,11,10]或[00,10,11,01]
    //考虑3位：000,001,010,011,100,101,110,111,我们会发现n位，那么起始位的下一位有n中选择
    //当我们选择之后，也就是确定了2位，那么对于当前的首尾，我们考虑它的可能有多种，不好确定
    //我们考虑成环，那么这个序列其实start就不重要了，我们可以都考虑0开始，最后在移动一下结果序列，让start开始就行
    //那么从能0开始的话，我们可以考虑考虑最后一位是1+n-1个0，也就是首尾只有最高位不同
    //那么整个序列可以分成两部分，前半部分高位是0，后半部分高位是1，而子序列在这两部分中是互相逆序
    //很明显，数量是对的，那么问题其实就是递归了


    vector<int> tmp = circularPermutation2(n);
    int sz = tmp.size();
    vector<int> res(sz,0);
    int j = 0;
    for(int i=0;i<tmp.size();++i)
    {
        if(tmp[i] == start)
        {
            j = i;
        }
    }

    for(int i=0;i<res.size();++i)
    {
        res[i] = tmp[(j+i+sz)%sz];
    }

    return res;
}

//另一个思路：异或。。。。。找规律
//十进制      二进制          操作
// 3          011             
//                            ^= 1  
// 2          010             
//                            ^= (1 << 1)  
// 0          000             
//                            ^= 1  
// 1          001             
//                            ^= (1 << 2)
// 5          101             
//                            ^= 1  
// 4          100             
//                            ^= (1 << 1)
// 6          110             
//                            ^= 1  
// 7          111    

//leetcode 89.格雷码
//异或方式：G(n) = B(n+1)xorB(n)
//int* grayCode(int n, int* returnSize){
//     int total=pow(2.0,n);
//     int *a=malloc(sizeof(int)*total);
//     *returnSize=total;
//     for(int i=0;i<total;i++){
//         a[i]=(i>>1)^i;
//     }
//     return a;
// }

int main()
{
    vector<int> res = circularPermutation(2,3); //[3,2,0,1]
    res = circularPermutation(3,2);//[2,6,7,5,4,0,1,3]
    for(auto a : res)
    {
        printf("%d,",a);
    }
    printf("\n");
    return 0;
}