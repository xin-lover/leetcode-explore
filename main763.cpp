//leetcode 763. 划分字母区间

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<int> partitionLabels(string S) {
    //思路：首先第一个字符肯定在第一个片段中，如果后面有第一个片段的字符，则需要吧这个字符前的所有片段都合并为第一个片段
    //所以我们的策略是开始时每一个字符都是一个片段，然后看新字符是否在前面的片段中出现，如果出现，则合并前面的所有片段
    //使用不相交集的思路合并

    vector<int> endPoints(26,0);
    vector<int> flags(26,-1);
    int count = 0;

    for(int i=0;i<S.size();++i)
    {
        printf("%c\n",S[i]);
        int seq = flags[S[i]-'a'];
        if(seq != -1)
        {
            printf("a seq %d\n",seq);
            for(int i=0;i<flags.size();++i)
            {
                if(flags[i] > seq)
                {
                    flags[i] = seq;
                }
            }

            count=seq+1;
            printf("seq %d\n",seq);
            endPoints[seq] = i;
        }
        else
        {
            flags[S[i]-'a'] = count;
            endPoints[count] = i;
            ++count;
        }
        
    }
    printf("count:%d\n",count);

    vector<int> res(count,0);
    res[0] = endPoints[0]+1;
    for(int i=1;i<count;++i)
    {
        res[i] = endPoints[i] - endPoints[i-1];
    }
    return res;
}

int main()
{
    vector<int> res = partitionLabels("ababcbacadefegdehijhklij");
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
}