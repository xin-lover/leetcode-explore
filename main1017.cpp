//1017. 负二进制转换

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string baseNeg2(int N) {
    //思路：从N的二进制入手，N可以分为偶数位部分和奇数位部分
    //现在的情况就是奇数部分变成了负数
    //假设k为奇数，那么我们本来需要2^k，但现在变成了-2^k,我们可以使用-2^(k+1)+-2^k得到
    //如果k+1位置为0，那么就结束了，但假设k+1位置也是1，也就是说我们需要2个2^(k+1),也就是相当2^(k+2)
    //这个时候就有两种情况了，k+2位置为0，那么情况跟k一样了
    //如果k+2位置为1，那么就变成了2*2^(k+2)=2^(k+3)，也就是k+3位置进1,这个时候其实情况并没有太多的变化，还是继续考虑k+3
    //综上，迭代求解即可

    vector<int> s;
    int tmp = N;
    while(tmp > 0)
    {
        s.push_back(tmp&1);
        tmp >>= 1;
    }

    int n = s.size();
    if((n & 1) == 0)
    {
        s.push_back(0);
    }

    //这个时候s是反序的,而我们也需要这个反序遍历
    int carry = 0;
    for(int i=1;i<s.size()-1;++i)
    {
        if(i&1)
        {
            if(s[i] == 1)
            {
                s[i+1]+=1;
            }
            else if(s[i] == 2)
            {
                s[i+1]+=1;
                s[i] = 0;
            }
        }
        else
        {
            if(s[i]==2)
            {
                s[i+1]+=1;
                s[i]=0;
            }
        }
    }

    if(s.back() == 2)
    {
        s.back() = 0;
        s.push_back(1);
        s.push_back(1);
    }

    string res;
    for(int i=s.size()-1;i>=0;--i)
    {
        res.append(1,s[i]+'0');
    }

    return res;

}

//通过数学推导可以得到+K/-K进制的通用转化法
// 无论K是正数还是负数都支持（只支持-10～10进制，因为更高进制需要引入字母）
//这个的思路余商向上取整是一个思路
vector<int> baseK(int N, int K) {
    if (N == 0) return {0};
    vector<int> res;
    while (N != 0) {
        int r = ((N % K) + abs(K)) % abs(K); // 此处为关键
        res.push_back(r);
        N -= r;
        N /= K;
    }
    reverse(res.begin(), res.end());
    return res;
}
string baseNeg2_1(int N) {
    vector<int> nums = baseK(N, -2);
    string res;
    for (auto x : nums) res += to_string(x);
    return res;
}

int main()
{
    printf("%d\n",7%-2);
    printf("%d\n",-7%4);
    printf("%d\n",-3%-2);
    // printf("%s\n",baseNeg2(3).c_str());//111
    // printf("%s\n",baseNeg2(2).c_str());//110
    // printf("%s\n",baseNeg2(4).c_str());//100
    // printf("%s\n",baseNeg2(0).c_str());//100
    printf("%s\n",baseNeg2_1(6).c_str());//11010
    return 0;
}