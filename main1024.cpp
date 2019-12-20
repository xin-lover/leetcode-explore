//1024. 视频拼接

#include <cstdio>
#include <vector>

using namespace std;

int videoStitching(vector<vector<int>>& clips, int T) {
    //思路：关键是最少片段，考虑排序+贪心
    //对于预期的时间点，下一个片段的开始时间点必须小于等于它
    //然后，对于符合要求的时间点我们选取结束时间最长的
    //所以：排序规则，开始时间从小往大排，结束时间小到大和打到小都行，不过是取第一个和最后一个的区别
    //需要注意的是片段是左闭右开的区间，即下一个片段的开始时间需要等于上一个片段的结束点

    sort(clips.begin(),clips.end(),[](vector<int>& a, vector<int>& b)
    {
        if(a[0]==b[0])
        {
            return a[1] > b[1];
        }

        return a[0] < b[0];
    });

    int expectedStart = 0;
    int tmpEnd = 0;
    int count = 0;
    for(int i=0;i<clips.size();++i)
    {
        if(clips[i][0] > expectedStart)
        {
            if(clips[i][0] > tmpEnd)
            {
                return -1;
            }
            else
            {
                ++count;
                expectedStart = tmpEnd;
                // printf("hh:%d\n",expectedStart);
                if(expectedStart >= T)
                {
                    return count;
                }
            }
            
        }
        else if (clips[i][0] == expectedStart)
        {
            expectedStart = clips[i][1]; //贪心，那范围最大的
            // printf("expectedStart:%d\n",expectedStart);
            ++count;
            if(expectedStart >= T)
            {
                return count;
            }
        }
        else
        {
            //同样贪心
            if(clips[i][1] > tmpEnd)
            {
                tmpEnd = clips[i][1];
                if(tmpEnd >= T)
                {
                    return count+1;
                }
            }
        }
    }

    return -1;
}

int main()
{
    vector<vector<int>> clips = {{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}};
    int T = 10; //3

    clips = {{0,1},{1,2}};
    T = 5; //-1

    clips = {{0,1},{6,8},{0,2},{5,6},{0,4},{0,3},{6,7},{1,3},{4,7},{1,4},{2,5},{2,6},{3,4},{4,5},{5,7},{6,9}};
    T = 9; //3

    // clips = {{0,4},{2,8}};
    // T = 5; //2

    // clips = {{0,5},{6,8}};
    // T = 7; //-1

    // clips = {{0,0},{9,9},{2,10},{0,3},{0,5},{3,4},{6,10},{1,2},{4,7},{5,6}};
    // T = 5;//1

    printf("%d\n",videoStitching(clips,T));
    return 0;


}