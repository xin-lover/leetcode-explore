#include <cstdio>
#include <vector>

using namespace std;

int findMinArrowShots(vector<vector<int>>& points) {
    //思路：其实就是找交集，如何使数量最小
    //[[10,16], [2,8], [1,6], [7,12]]
    //先构建一个空集，不断的往里面添加空间，然后计算交集
    
    if(points.size() < 2)
    {
        return points.size();
    }

    sort(points.begin(),points.end(),[](vector<int> a,vector<int> b){
        if(a[0] == b[0])
        {
            return a[1] < b[1];
        }
        else
        {
            return a[0] < b[0];
        }
        
    });
    vector<vector<int>> tmp;
    tmp.push_back(points[0]);
    for(int i=1;i<points.size();++i)
    {
        bool isNew = true;
        for(int j=0;j<tmp.size();++j)
        {
            if((points[i][0] >= tmp[j][0] && points[i][0] <= tmp[j][1])
            || (points[i][1] >= tmp[j][0] && points[i][1] <= tmp[j][1]))
            {
                tmp[j] = {max(points[i][0],tmp[j][0]),min(points[i][1],tmp[j][1])};
                isNew = false;
            }
        }
        if(isNew)
        {
            tmp.push_back(points[i]);
        }
    }

    for(auto a : tmp)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }
    return tmp.size();
}

int finddd(vector<vector<int>> points)
{
    sort(points.begin(),points.end(),[](vector<int> a,vector<int> b){
            return a[1] < b[1];

        });
        for(auto a : points)
        {
            printf("hh:%d %d\n",a[0],a[1]);
        }
        int count = 1;
        int end = points[0][1];
        for(int i=1;i<points.size();++i)
        {
            if(points[i][0] <= end)
            {
                continue;
            }
            end = points[i][1];
            printf("end:%d\n",end);
            ++count;
        }
        
        return count;
}

int main()
{
    vector<vector<int>> points = {
        // {10,16}, {2,8}, {1,6}, {7,12}
        // {1,2},{2,3},{3,4},{4,5}
        {3,9},{7,12},{3,8},{6,8},{9,10},{2,9},{0,9},{3,9},{0,6},{2,8}
        //  {3,9},{7,12},{3,4},
    };

    printf("%d\n",finddd(points));
    return 0;
}