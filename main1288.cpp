//1288. 删除被覆盖区间

#include <cstdio>
#include <vector>

using namespace std;

int removeCoveredIntervals(vector<vector<int>>& intervals) {
    //思路：首先空间的包含是大包小，所以看看能不能包含的话需要知道哪个区间大
    //如果不排序，那就要先判断，用一个集合保留大的那个空间，这样每次都要和所有的比
    //所以先排序，遍历的时候前面的区间的左边界已知是最小的，后一个的边界有以下几种情况：
    //1.左边界一样大，那么前一个区间被后一个包含；
    //2.后一个的左边界大，那么前一个不能被包含，结果+1，此时右边界又有两种情况；
    //3.后一个的左边界大，但右边界小于前一个区间，那么是被前一个包含；
    //4.左边界大，右边界也大，同2，结果+1；


    //排序是耗时点
    sort(intervals.begin(),intervals.end(),[](vector<int>& a, vector<int>& b){
        if(a[0] == b[0])
        {
            return a[1]<b[1];
        }

        return a[0] < b[0];
    });

    int j=0;
    int res = 1;
    for(int i=1;i<intervals.size();++i)
    {
        if(intervals[i][0] > intervals[j][0])
        {
            if(intervals[i][1] > intervals[j][1])
            {
                ++res;
                j=i;
            }
        }
        else
        {
            j=i;
        }
    }

    return res;
}

int removeCoveredIntervals2(vector<vector<int>>& intervals) {
    //思路：用上车和下车的思路来试试，上车+1，下车-1，那么
    //1.两个集合不重合，那么上车时值为0，下车时值都是1；
    //2.如果一个包含另一个，那么上车时一个值为0，一个值为1，下车时，一个值为2，一个值为1；
    //3.如果两个区间部分重合，上车时一个为0，一个为1，下车时，一个为2，一个为1，
    //所以2和3现在无法分辨；

    return -1;
}

int main()
{
    vector<vector<int>> intervals = {{1,4},{3,6},{2,8}}; //2
    printf("%d\n",removeCoveredIntervals(intervals));
    
    return 0;
}