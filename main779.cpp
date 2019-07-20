//leetcode 779. 第K个语法符号

#include <cstdio>

using namespace std;

int kthGrammar(int N, int K) {
    
    //思路：暴力破解，空间复杂度太高
    //可以看出所以行排列起来就是一颗完全二叉树，子节点依赖父节点
    //策略：根据k从最后一行往前推，判断其属于哪个子树，再根据父节点即可得出
    
//         if(K > pow(2,N-1))
//         {
//             return -1;
//         }
    
//         if(N == 1)
//         {
//             return 0;
//         }
//         int half = pow(2,N-2);
//         if(K <= half)
//         {
//             return kthGrammar(N-1,K);
//         }
//         else
//         {
//             
//             int t = 1 + kthGrammar(N-1,K-half);
//                //优化，可以变为return 1-t；
//             return t >= 2 ? t-2 : t;
//         }
    
    //K每一步都除2 再与1，与1可以理解求改节点是左儿子和是右儿子，同时r存储了上一步结果，也就是可以理解为父节点
    //其实这个求解的顺序是反的，也就是先求的最后一层是左儿子还是右儿子，然后不断迭代向上
    //但题目特殊，配合异或运算刚好能得到正确结果，比如
    //父节点是0，左右的正反结果一样，而左左，右右的结果不同，分别为0->0->0，1->1->1，但异或后，这个两个结果相同，父节点是1，同理，
    K--;    //counting from 0 instead of 1
    bool r = 0;
    while(K){
        r ^= (K&1);//r异或1或0，
        K/=2;
    }
    return r;
}

int main()
{
    printf("%d\n",kthGrammar(3,2));
    return 0;   
}