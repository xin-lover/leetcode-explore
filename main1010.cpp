//1010. 总持续时间可被 60 整除的歌曲

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int numPairsDivisibleBy60(vector<int>& time) {
    //思路：其实就是找被整除的数对，直观的想法就是O(n2)遍历了
    //另一种思路就是上次使用同余方式解决问题的想法了
    //方案：遍历每个数，求余60得k，使用一个map存60-k，在存之前在结果res上加上这个值的数量
    //也就是表示现在这个数与之前的数成为符合要求的数对的数量

    int res = 0;
    unordered_map<int,int> um;
    for(int i=0;i<time.size();++i)
    {
        int t = time[i] % 60;
        if(um.find(t) != um.end())
        {
            res += um[t];
        }

        ++um[t == 0 ? t :60 - t];
    }

    return res;
}

int main()
{
    vector<int> time = {60,60,60}; //3
    time = {30,20,150,100,40}; //3
    printf("%d\n",numPairsDivisibleBy60(time));
    return 0;
}