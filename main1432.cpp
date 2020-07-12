//1432. 改变一个整数能得到的最大差值

#include <cstdio>
#include <vector>

using namespace std;

int maxDiff(int num) {
    //思路：差值最大，很明显，数字的高位最重要，不管变大变小都优先选择高位
    //一个变为9，一个变为1，如果原本就是9或1，那么考虑第二位
    //策略：选择高位第一个非9非1的位进行替换,需要注意可替换位0的情况

    vector<int> bits;
    int tmp = num;
    while(tmp > 0)
    {
        bits.push_back(tmp % 10);
        tmp /= 10;
    }

    int index_a = -1;
    for(int i=bits.size()-1;i>=0;--i)
    {
        if(bits[i] != 9)
        {
            index_a = i;
            break;
        }
    }

    int index_b = -1;
    int b_rep = 0;
    if(bits.back() != 1)
    {
        index_b = bits.size()-1;
        b_rep = 1;
    }
    else
    {
        for(int i=bits.size()-2;i>=0;--i)
        {
            if(bits[i] != 0 && bits[i] != 1)
            {
                index_b = i;
                b_rep = 0;
                break;
            }
        }
    }

    auto getNum=[](vector<int>& arr,int index,int replaceValue)
    {
        int res = 0;
        for(int i=arr.size()-1;i>=0;--i)
        {
            res *=10;
            res += arr[i] == arr[index] ? replaceValue : arr[i];
        }

        return res;
    };

    int a = index_a > -1 ? getNum(bits,index_a,9) : num;
    int b = index_b > -1 ? getNum(bits,index_b, b_rep) : num;
    // printf("b:%d %d %d\n",b,index_b,b_rep);
    // printf("a:%d b:%d\n",a,b);

    return a - b;
}

int main()
{
    printf("%d\n",maxDiff(555));    ///888
    printf("%d\n",maxDiff(9));    ///8
    printf("%d\n",maxDiff(123456));    ///820000
    printf("%d\n",maxDiff(10000));    ///80000
    printf("%d\n",maxDiff(9288));    ///8700
    printf("%d\n",maxDiff(111));    ///888

    return 0;
}