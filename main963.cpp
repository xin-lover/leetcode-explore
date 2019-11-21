//leetcode 963. 最小面积矩形 II

#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

double minAreaFreeRect(vector<vector<int>>& points) {
    //思路：这里还是查找矩形问题，可以确定两个点，查找另外两个点
    //所以如何存储点和遍历点就是关键
    //按行组织点，因为限制坐标大小就是40000，直接构建固定大小数组即可，也可以使用map+set，这样内存占用少一些
    //也可以确定对角线的点
    //这个方案优化点一个点是把两个左边通过x*40000+y的方式变为一个整数
    //当本题中，矩形不一定是正放的，所以矩形的情况还要多考虑一种,也就是选取的两个点为边和为对角线
    //循环太多

    const int kNum = 40001;
    vector<vector<bool>> graph(kNum,vector<bool>(kNum,false));

    for(int i=0;i<points.size();++i)
    {
        graph[points[i][0]][points[i][1]] = true;
    }

    double res = INT_MAX;
    for(int i=0;i<kNum;++i)
    {
        for(int j=i+1;j<kNum;++j)
        {
            int h = j-i;
            for(int c1=0;c1<kNum;++c1)
            {
                if(!graph[i][c1] || !graph[j][c1])
                {
                    continue;
                }

                //边
                //优化，剪枝
                for(int c2=c1+1;c2 < kNum;++c2)
                {
                    if(!graph[i][c2] || !graph[j][c2])
                    {
                        continue;
                    }
                    double w = c2 - c1;
                    res = min(res, h * w);
                }

                //对角线
                int half = h / 2;
                // for(int x = c1+1;x<=c1+half;++x)
                // {
                //     for(int y=i;y<=j;++y)
                //     {
                //         if(!graph[x][y] || !graph[c1+c1-x][j-y+i])
                //         {
                //             continue;
                //         }

                //         if((c1-x)*(c1-x) + (i-y) * (j-y) == 0)
                //         {
                //             double area = (c1-x) * (j-y) - (c1-x) * (i-y);
                //             res = min(area,res);
                //         }
                //     }
                // }
            }
        }
    }

    return res == INT_MAX ? 0 : res;

}

double minAreaFreeRect2(vector<vector<int>>& points) {
    //思路：这个矩形判断没有之前那么简单了，不能选取两点为边求了，必须是对角线
    //所以使用优化思路，把两个坐标点按公式换成整数，然后求其它亮点，使用垂直向量公式求
    //第三个点比较难确定，所以直接枚举

    const int kNum = 40000;
    set<int> cds;
    for(int i=0;i<points.size();++i)
    {
        cds.insert(points[i][0] * kNum + points[i][1]);
    }

    int res = INT_MAX;
    for(int i=0;i<points.size();++i)
    {
        for(int j=i+1;j<points.size();++j)
        {
            for(int k=j+1;k<points.size();++k)
            {
                //p4 = p2+p3-p1 假设p2,p3处于对角线

                int x = points[j][0] + points[k][0] - points[i][0];
                int y = points[j][1] + points[k][1] - points[i][1];

                //判断垂直
                //(p3-p1) * (p2-p1)==0

                pair<int,int> v1 = {points[k][0] - points[i][0],points[k][1]-points[i][1]};
                pair<int,int> v2 = {points[j][0] - points[i][0],points[j][1]-points[i][1]};
                if(v1.first * v2.first + v1.second * v2.second == 0)
                {
                    //判断是否存在
                    if(cds.find(x*kNum+y) != cds.end())
                    {
                        //计算面积
                        int area = abs(v1.first * v2.second - v1.second * v2.first);
                        res = min(area,res);
                    }
                }
            }   
        }
    }

    return res == INT_MAX ? 0 : res;
}

double minAreaFreeRect3(vector<vector<int>>& points) {
    //思路：枚举中心，记录点对的中点，只有中点相同的两个点对才可能是矩形，也就是说这两个点对是对角线，然后再看对角线的长度，
    //如果长度也相等，则4个点组成矩形

    const int kNum = 40000;
    unordered_map<int,unordered_map<long long,vector<pair<int,int> > > > um;

    for(int i=0;i<points.size();++i)
    {
        for(int j=i+1;j<points.size();++j)
        {
            pair<int,int> center = {points[i][0] + points[j][0],points[i][1] + points[j][1]};
            int r2 = (points[j][0]-points[i][0]) * (points[j][0]-points[i][0]) + (points[j][1]-points[i][1])*(points[j][1]-points[i][1]);

            um[r2][static_cast<long long>(center.first) * kNum + center.second].push_back({points[i][0],points[i][1]});
        }
    }

    double res = kNum * kNum;
    for(auto it = um.begin();it!=um.end();++it)
    {
        for(auto it2 = it->second.begin();it2!=it->second.end();++it2)
        {
            int center_x = it2->first / kNum;
            int center_y = it2->first % kNum;
            for(int i=0;i<it2->second.size();++i)
            {
                for(int j=i+1;j<it2->second.size();++j)
                {
                    auto a = (it2->second)[i];
                    auto b = (it2->second)[j];

                    //b的对角线点
                    int cx = center_x - b.first;
                    int cy = center_y - b.second;

                    //向量叉乘求面积(b-a)x(center-a)
                    long long area = (b.first - a.first) * (cy - a.second) - (b.second - a.second) * (cx- a.first);
                    if(area < 0)
                    {
                        area = - area;
                    }
                    if(area < res)
                    {
                        res = area;
                    }
                }
            }
        }
    }

    return res < kNum * kNum ? res : 0;
}

int main()
{
    vector<vector<int>> v = {{1,2},{2,1},{1,0},{0,1}}; //2
    // v = {{0,1},{2,1},{1,1},{1,0},{2,0}}; //1
    // v = {{0,3},{1,2},{3,1},{1,3},{2,1}};//0
    printf("%f\n",minAreaFreeRect3(v));

    int a = 9,b=9;
    int h = a * 10 + b;
    a = h / 10;
    b = h % 10;
    printf("%d %d\n",a,b);
    return 0;

}

