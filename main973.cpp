//leetcode 973. 最接近原点的 K 个点

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    //思路：使用优先队列保存最近的k个点即可   

    auto cmp =[](const pair<int,int>& a,const pair<int,int>& b){return a.second < b.second;};
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> pq(cmp);

    for(int i=0;i<points.size();++i)
    {
        pq.push({i,points[i][0]*points[i][0] + points[i][1]*points[i][1]});
    }

    vector<vector<int>> res;
    while(!pq.empty())
    {
        if(pq.size() <= K)
        {
            int seq =(pq.top()).first;
            res.push_back(points[seq]);
        }
        pq.pop();
    }

    return res;
}

void work(vector<vector<int>>& points,int i,int j,int K)
{
    if(i>=j)
    {
        return;
    }

    int oi=i,oj=j;
    int seq = rand() % (j-i+1) + i;//[i,j]，保证随机i到j的每一个数，不然对于两个数的时候，可能会一直取第一个或第二个，陷入无限循环
    printf("i:%d j:%d seq:%d\n",i,j,seq);
    int pivot = (points[seq][0]*points[seq][0] + points[seq][1] * points[seq][1]);
    while(i < j)
    {
        //i==j时，没有比较,也就是说如果j之前的都小于等于pivot，那么j位置就被剔除了。。
        // while(i<j && (points[i][0]*points[i][0]+points[i][1]*points[i][1]) <= pivot) ++i;
        // while(i<j && (points[j][0]*points[j][0]+points[j][1]*points[j][1]) > pivot) --j;
        while(i<=j && (points[i][0]*points[i][0]+points[i][1]*points[i][1]) <= pivot) ++i;
        while(i<=j && (points[j][0]*points[j][0]+points[j][1]*points[j][1]) > pivot) --j;
        if(i<j)
        {
            swap(points[i],points[j]);
        }
    }

    printf("pivot:%d\n",pivot);
    for(auto a : points)
    {
        printf("%d ",a[0]*a[0]+a[1]*a[1]);
    }
    printf("\n");
    if(K < i-oi)
    {
        work(points,oi,i-1,K);
    }
    else if(K > i-oi)
    {
        work(points,i,oj,K-(i-oi));
    }
    
}
vector<vector<int>> kClosest2(vector<vector<int>>& points, int K) 
{
    //思路：分治法,和快排一个思路，但问题在于碰到相同距离的点时如何处理
    for(auto a : points)
    {
        printf("%d ",a[0]*a[0]+a[1]*a[1]);
    }
    printf("\n");
    srand(10);
    work(points,0,points.size()-1,K);
    vector<vector<int>> res(points.begin(),points.begin()+K);
    return res;
}

int main()
{
    vector<vector<int>> points = {{1,3},{2,2}};
    int K = 1;//[2,2]
    // points = {{3,3},{5,-1},{-2,4}};
    // K = 2; //[[3,3],[-2,4]]
    // points={{0,1},{1,0}};
    // K=2;
    points = {{89,6},{-39,-4},{-13,91},{97,-61},{1,7},{-66,69},{-51,68},{82,-6},{-21,44},{-58,-83},{-40,73},{-88,-24}};
    K=8;
    points = {{-6,-8},{4,-2},{4,5},{5,7},{3,1}};
    K = 4;
    vector<vector<int>> res = kClosest2(points,K);

    for(auto a : res)
    {
        printf("[%d,%d] ",a[0],a[1]);
    }
    printf("\n");
    return 0;
}