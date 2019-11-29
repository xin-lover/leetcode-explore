//984. 不含 AAA 或 BBB 的字符串

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string strWithout3a3b(int A, int B) {
    //思路：其实就是间隔放置即可
    //方案：假设A>B,则令m=A/B，每m个‘A'放一个’B‘

    char Achar = 'a';
    char Bchar = 'b';
    if(A < B)
    {
        swap(A,B);
        swap(Achar,Bchar);
    }

    int m = A / (B+1); //可以划分为B+1个空间
    int n = A % (B+1);

    if(m >= 3 || (m == 2 && n > 0))
    {
        return "";
    }   

    string res;
    for(int i=0;i<n;++i)
    {
        res.append(m+1,Achar);
        res.append(1,Bchar);
    }
    for(int i=n;i<B;++i)
    {
        res.append(m,Achar);
        res.append(1,Bchar);
    }
    res.append(m,Achar);

    return res;
}

string strWithout3a3b2(int A, int B) {
    //思路：同一个字符最多连续两次，那么我们就按这个思路排列,每个字符写两次
    //不能都写两次,官方题解中有个细节，就是每次写一个字符，但都优先多的那个字符
    //比如A>B，那么就是写a，直到两个a，这时再写一个b，这个时候要比较又要比较A和B的大小，重复这个过程
    //所以下面的这种思路就不行了，不能一直写两次，对于[2,5]的就不行
    //改进的方案是结合上下的两种解法，如果A==B，那么交叉放置即可
    //如果A>B,那么每次都先放两个a，一个b，直到A==B

    char cc[]={'a','b'};
    int ic[]={A,B};
    if(A < B)
    {
        swap(cc[0],cc[1]);
        swap(ic[0],ic[1]);
    }
    string res;
    while(ic[0] > ic[1] && ic[1] > 0)
    {
        res.append(2,cc[0]);
        res.append(1,cc[1]);
        ic[0]-=2;
        ic[1]-=1;
    }
    for(int i=0;i<ic[0];++i)
    {
        res.append(1,cc[0]);
        if(i < ic[1])   //这个是耗时点
            res.append(1,cc[1]);
    }

    return res;
}

string strWithout3a3b3(int A, int B) {
    string res;

    while(A > 0 || B > 0)
    {
        bool writeA = false;
        int len = res.size();
        if(len >= 2 && res[len-1] == res[len-2])
        {
            if(res[len-1] == 'b')
            {
                writeA = true;
            }
        }
        else
        {
            if(A >= B)
            {
                writeA = true;
            }
        }

        if(writeA)
        {
            --A;
            res.append(1,'a');
        }
        else
        {
            --B;
            res.append(1,'b');
        }
    }

    return res;
}

int main()
{
    // printf("%s\n",strWithout3a3b2(1,2).c_str()); // abb,bab,bba
    // printf("%s\n",strWithout3a3b2(4,1).c_str()); // aabaa
    // printf("%s\n",strWithout3a3b2(1,1).c_str()); // ab,ba 
    // printf("%s\n",strWithout3a3b2(1,4).c_str()); // bbabb
    printf("%s\n",strWithout3a3b2(1,5).c_str()); // 
    printf("%s\n",strWithout3a3b2(2,3).c_str()); // 
    printf("%s\n",strWithout3a3b2(4,4).c_str()); // 
    return 0;
}