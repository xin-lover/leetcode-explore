//leetcode 880. 索引处的解码字符串

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string decodeAtIndex(string S, int K) {
    //思路：一种方式是暴力破解，性能肯定低
    //另一种就是记录字符串和其重复数量，这样能计算出当前的长度

    vector<vector<int>> substrings; //存储格式：每遇到一个数字是一段，前一阶段的数量,新字符开始结束位置，当前阶段重复次数

    int start = 0;
    long long count = 0;
    for(int i=0;i<S.size();++i)
    {
        if(S[i] >= '0' && S[i] <= '9')
        {
            int num = S[i] - '0';
            substrings.push_back({static_cast<int>(count),start,i,num});
            count = (count +(i - start)) * num;
            
            if(count >= K)
            {
                // for(auto a : substrings)
                // {
                //     for(auto b : a)
                //     {
                //         printf("%d ",b);
                //     }
                //     printf("\n");
                // }
                //递归查找
                for(int j=substrings.size()-1;j>=0;--j)
                {
                    int base = substrings[j][0];
                    int len = substrings[j][2] - substrings[j][1];
                    int repeat = substrings[j][3];

                    K %= (base + len);
                    if(len > 0)
                    {
                        if(K == 0)
                        {
                            return string(1,S[substrings[j][2]-1]);
                        }
                        if(K > base && K <= base + len)
                        {
                            return string(1,S[substrings[j][1] + K - base - 1]);
                        }
                    }
                }
            }

            start = i+1;
        }
    }

    if(count + S.size() - start >= K)
    {
        return string(1,S[start + K - count-1]);
    }

    return "";
}

//思路一样，代码思路简练，内存有优势
string decodeAtIndex2(string S, int K) {
    long long size = 0;
    int N = S.size();

    // Find size = length of decoded string
    for (int i = 0; i < N; ++i) {
        if (isdigit(S[i]))
            size *= S[i] - '0';
        else
            size++;
    }

    for (int i = N-1; i >=0; --i) {
        K %= size;
        if (K == 0 && isalpha(S[i]))
            return (string) "" + S[i];

        if (isdigit(S[i]))
            size /= S[i] - '0';
        else
            size--;
    }

    return "";
}

int main()
{
    printf("%s\n",decodeAtIndex2("leet2code3",10).c_str()); //o
    printf("%s\n",decodeAtIndex("a2345678999999999999999",1).c_str()); //a
    printf("%s\n",decodeAtIndex("ha22",5).c_str()); //h
    printf("%s\n",decodeAtIndex("a2b3c4d5e6f7g8h9",9).c_str()); //
    printf("%s\n",decodeAtIndex("ixm5xmgo78",711).c_str());
    printf("%s\n",decodeAtIndex2("czjkk9elaqwiz7s6kgvl4gjixan3ky7jfdg3kyop3husw3fm289thisef8blt7a7zr5v5lhxqpntenvxnmlq7l34ay3jaayikjps",60).c_str());
    printf("%s\n",decodeAtIndex2("abc",3).c_str());
    return 0;
}