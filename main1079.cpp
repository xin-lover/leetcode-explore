//1079. 活字印刷

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int numTilePossibilities(const vector<int>& words,int index,const vector<int>& factorials,int count,int dem)
{
    if(index >= words.size())
    {
        return factorials[count] / dem;
    }
    int res = 0;
    for(int i=0;i<=words[index];++i)
    {
        res += numTilePossibilities(words,index+1,factorials,count+i,dem * factorials[i]);
    }

    return res;
}

int numTilePossibilities(string tiles) {
    //思路：就是排列组合，但这里有重复字符，所以需要额外计算
    //先统计各个字符的数量
    //遍历时先确定本次用的字模数量，然后根据排列原理求出结果
    //问题是如何确定使用的字模是哪些？
    //两个字模时，我们可以从任意两堆选取一个，也可以在一堆中选取两个
    //3个时，同理，组合1-3，{1,1,1-2},{1-1,1-1,1-1}
    //4个时，{1-4},{1-1,1-3},{1-2,1-2},{1-1,1-1,1-2},{1-1,1-1,1-1,1-1}
    //所以一个直观的做法就是回溯

    vector<int> factorials(tiles.size()+1,1);
    for(int i=1;i<=tiles.size();++i)
    {
        factorials[i] = factorials[i-1]*i;
    }
    vector<int> words(26,0);
    for(int i=0;i<tiles.size();++i)
    {
        ++words[tiles[i]-'A'];
    }

    vector<int> flags;
    for(int i=0;i<words.size();++i)
    {
        if(words[i] > 0)
        {
            flags.push_back(words[i]);
        }
    }

    return numTilePossibilities(flags,0,factorials,0,1)-1;
}

int main()
{
    printf("%d\n",numTilePossibilities("AAB"));//8
    printf("%d\n",numTilePossibilities("AAABBC"));//188
    return 0;
}