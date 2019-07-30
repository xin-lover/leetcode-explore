//leetcode 791. 自定义字符串排序

#include <cstdio>
#include <string>

using namespace std;

string customSortString(string S, string T) {
    //思路：没有出现在S中的字符可以任意排列，所以关键就在与排序时的比较规则如何定义
    //策略：使用一个数组来存字符的排列大小，初始都是26

    int orders[26];
    for(int i=0;i<26;++i)
    {
        orders[i] = 26;
    }

    for(int i=0;i<S.size();++i)
    {
        orders[S[i]-'a'] -= 26 - i;
    }

    // for(int i=1;i<T.size();++i)
    // {
    //     int c = T[i];
    //     int j;
    //     for(j=i;j>0 && orders[c-'a'] < orders[T[j-1]-'a'];--j)
    //     {
    //         swap(T[j],T[j-1]);
    //     }
        
    //     T[j] = c;
    // }

    // return T;

    //优化，使用快排
    sort(T.begin(),T.end(),[&orders](char a,char b){
        return orders[a-'a'] < orders[b-'a'];
    });

    return T;
}

string customSortString2(string S, string T)
{
    //他人解法：每次排列S中的一个字符，所以复杂度是O(m*n),快排是O(n*n)
    int cnt = 0;
    for(int i=0;i<S.size();i++)
    {
        for(int j=cnt;j<T.size();j++)
        {
            if(T[j]==S[i])
            {
                swap(T[j],T[cnt++]);
            }
        }
    }
    return T;
}

//记录T中各字符数量，然后遍历S依次次添加
//这里pos的数组其实不需要，去掉后更简练
string customSortString3(string S, string T) {
    // int pos[S.length()];
    // for (int i = 0; i < S.length(); ++i) {
    //     pos[i] = S[i];
    // }
    int count[26] = {0};
    for (int i = 0; i < T.length(); ++i) {
        count[T[i] - 97]++;
    }
    string res;
    for (int i = 0; i < S.length(); ++i) {
        // res.append(count[pos[i] - 97], pos[i]);
        // count[pos[i] - 97] = 0;

        res.append(count[S[i]-97],S[i]);
        count[S[i]-97]= 0;
    }
    for (int i = 0; i < 26; ++i) {
        if (count[i]) {
            res.append(count[i], i + 97);
        }
    }
    return res;
}

int main()
{
    printf("%s\n",customSortString3("cba","abcd").c_str());
    return 0;
}