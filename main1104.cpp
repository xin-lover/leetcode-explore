//1104. 二叉树寻路
#include <cstdio>
#include <vector>

using namespace std;

vector<int> pathInZigZagTree(int label) {
    //思路：这个树其实是满二叉树，满二叉树儿子节点是2n和2n+1，现在标记变了
    //奇数行与之前一样，而偶数行逆序了，所以我们可以按满二叉树的方法求出路径，然后偶数索引位置再逆序回来

    vector<int> tmp;
    while(label != 0)
    {
        tmp.push_back(label);
        label /= 2;
    }   

    vector<int> res;
    int start = 1;
    for(int i=tmp.size()-1;i>=0;--i)
    {
        if((i & 1) == 0)
        {
            res.push_back(tmp[i]);
        }
        else
        {
            res.push_back(start*2-1 - (tmp[i]-start));
        }
        start *= 2;
    }

    return res;
}

//其它思路：把每一层类比位二进制位，首先是1，然后左移变位两位，也就是到第二层了
//而逆序，在二进制中就相当于取反（除首位外的取反），比如3=11b，它逆序后的表示就是2=10b
//同理14=1110b，就相当与原来的9=1001b;
vector<int> pathInZigZagTree2(int label) {
    vector<int> res;
    while(label != 1)
    {
        res.push_back(label);
        label >>= 1;

        //取反，注意这里没有判断奇偶，只是每次都逆序，其实是基于相对不变的规则的，也就是奇数行和偶数行相对逆序，不会影响最终结果
        //这里的取反基于要知道最高位的位置，c++使用汇编反向扫描的指令"bsr"可以高效进行，其它方式感觉还不如上述重新逆序的简单
        //# 这里我采用异或实现
        //label = label ^(1 << (label.bit_length() - 1)) - 1

        //
    }
    return {};
}

int main()
{
    vector<int> res = pathInZigZagTree(26);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}