//587. 安装栅栏

#include <cstdio>
#include <vector>
#include <stack>
#include <set>

using namespace std;

vector<vector<int>> outerTrees(vector<vector<int>>& points) {
    //思路：这个题目重点在于找边界，算是一道技巧题，没想到什么好的办法
    //一个判断条件就是，所有的点要不在边界上，要不都在边界的一边
    //那么如果判断点都在线的一边了？使用叉乘
    //另一个就是判断共线，利用点乘,不用点乘，叉乘为0就是共线。。。
    //那这样复杂度有点高,O(n^3),果然超时
    //目标是O(n^2)，那如何优化内层的循环？这种判断方法应该是不太可能了
    //所以优化的地方应该是如何判断边界。。。

    if(points.size() < 4)
    {
        return points;
    }

    vector<bool> flags(points.size(),false);
    for(int i=0;i<points.size();++i)
    {
        for(int j=i+1;j<points.size();++j)
        {
            if(flags[j] && flags[i])
            {
                continue;
            }
            vector<int> collinears;
            int dir = 0;
            printf("---------\n");
            for(int k=0;k<points.size();++k)
            {
                int Ax = points[j][0] - points[i][0];
                int Ay = points[j][1] - points[i][1];
                int Bx = points[k][0] - points[i][0];
                int By = points[k][1] - points[i][1];
                
                //叉乘
                int d = Ax * By - Bx * Ay;
                printf("d:%d\n",d);

                if(d == 0) //共线
                {
                    collinears.push_back(k);
                }
                else
                {
                    int rd = d > 0 ? 1 : -1;
                    if(dir != 0 && dir != rd)
                    {
                        dir = 2;
                        break;
                    }
                    else
                    {
                        dir = rd;
                    }
                }
            }

            if(dir != 2)
            {
                flags[i]=true;
                flags[j]=true;
                for(auto a : collinears)
                {
                    flags[a] = true;
                }
            }
        }
    }

    vector<vector<int>> res;
    for(int i=0;i<flags.size();++i)
    {
        if(flags[i])
        {
            res.push_back(points[i]);
        }
    }

    return res;
}

//Jarvis 算法
//先找集合中最左侧的点，然后找这个点逆时针最接近它的点，不断迭代，知道回到这个点
//如何找逆时针最接近它的点？已知了一个点p，随便找集合中的一个点r，假设集合中存在一个点q在向量pr的顺时针方向，那么更新r为q，最后的q就会逆时针最接近p的点

int orientation(vector<int> p,vector<int> q, vector<int> r)
{
    return (q[1]-p[1])*(r[0]-q[0]) - (q[0]-p[0])*(r[1]-q[1]); 
}

int inBetween(vector<int> p,vector<int> q, vector<int> r)
{
    bool a = (q[0] >= p[0] && q[0] <=r[0]) || (q[0] <= p[0] && q[0] >= r[0]);
    bool b = (q[1] >= p[1] && q[1] <=r[1]) || (q[1] >= r[1] && q[1] <= p[1]);

    return a && b; 
}

vector<vector<int>> outerTrees2(vector<vector<int>>& points) {

    if(points.size() < 4)
    {
        return points;
    }

    int left_most = 0;
    for(int i=1;i<points.size();++i)
    {
        if(points[i][0] < points[left_most][0])
        {
            left_most = i;
        }
    }

    vector<bool> flags(points.size(),false);
    int p = left_most;
    do{
        int q = (p+1) % (points.size());
        for(int i=0;i<points.size();++i)
        {
            if(i!=p && i!=q && orientation(points[p],points[i],points[q]) < 0)
            {
                q = i;
            }
        }

        flags[q] = true;
        for(int i=0;i<points.size();++i)
        {
            if(i!=p && i!=q && orientation(points[p],points[q],points[i])==0 && inBetween(points[p],points[i], points[q]))
            {
                flags[i] = true;
            }
        }

        p = q;

    }while(p != left_most);

    vector<vector<int>> res;
    for(int i=0;i<flags.size();++i)
    {
        if(flags[i])
        {
            res.push_back(points[i]);
        }
    }
    return res;
}

//Graham 扫描
//先找到最左侧最下面的点，然后其它点根据与这个点的极角排序，如果在一条直线上则根据距离排序，近的在前面，但最后一条边的共线情况需要另外处理，也就是近的在后面
//形象的描述就是，确定最左侧最下方的点后，逆时针找边界点，如果当前点与上一个点的向量与相对之前的向量是左拐，则入栈，如果是右拐，则上一个点是应该被包含在凸包内的，接着考察上上个点
//最后在栈中的点就是边界点。。。

int distance(vector<int> a,vector<int> b)
{
    return (b[1]-a[1])*(b[1]-a[1]) + (b[0]-a[0])*(b[0]-a[0]);
}

vector<vector<int>> outerTrees3(vector<vector<int>>& points) {

    if(points.size() < 4)
    {
        return points;
    }
    int bottomLeft = 0;
    for(int i=0;i<points.size();++i)
    {
        if(points[i][1] == points[bottomLeft][1] && points[i][0] <points[bottomLeft][0])
        {
            bottomLeft = i;
        }
        if(points[i][1] < points[bottomLeft][1])
        {
            bottomLeft = i;
        }
    }

    vector<int> blPoint = points[bottomLeft];
    sort(points.begin(),points.end(),[blPoint](vector<int>& a,vector<int>& b)
    {
        int dif = orientation(blPoint,a,b) - orientation(blPoint,b,a);
        if(dif == 0)
        {
            return distance(blPoint,a) < distance(blPoint,b);
        }

        return dif < 0;
    }
    );

    int i=points.size()-1;
    while(i>=0 && orientation(blPoint,points.back(),points[i])==0)
    {
        --i;
    }

    for(int left=i+1,right=points.size()-1;left<right;++left,--right)
    {
        swap(points[left],points[right]);
    }
    

    stack<int> sk;
    sk.push(0);
    sk.push(1);

    for(int i=2;i<points.size();++i)
    {
        int tt = sk.top();
        sk.pop();
        while(orientation(points[sk.top()],points[tt],points[i]) > 0)
        {
            tt = sk.top();
            sk.pop();
        }

        sk.push(tt);
        sk.push(i);
    }

    vector<vector<int>> res;
    while(!sk.empty())
    {
        int t = sk.top();
        sk.pop();
        res.push_back(points[t]);
    }

    return res;
}

//单调链 
//与Graham差不多，不过排序不一样，单调链按x坐标排序，x相同则按y坐标排
//这样排序后，按Graham算法遍历，第一次得出的是凸包下部分的边界，第二次从后往前遍历，得出上部分边界。。。

vector<vector<int>> outerTrees4(vector<vector<int>>& points) {

    if(points.size() < 4)
    {
        return points;
    }

    sort(points.begin(),points.end(),[](vector<int>& a, vector<int>& b){
        if(a[0]==b[0])
        {
            return a[1] < b[1];
        }

        return a[0] < b[0];
    });
    for(auto a : points)
    {
        printf("%d %d,",a[0],a[1]);
    }
    printf("\n");

    stack<int> sk;
    for(int i=0;i<points.size();++i)
    {
        if(sk.size() < 2)
        {
            sk.push(i);
            continue;
        }
        
        int t = sk.top();
        sk.pop();
        while(sk.size()>=1 && orientation(points[sk.top()],points[t],points[i]) > 0)
        {
            t = sk.top();
            sk.pop();
        }
        
        sk.push(t);
        sk.push(i);
    }

    sk.pop();
    for(int i=points.size()-1;i>=0;--i)
    {
        if(sk.size() < 2)
        {
            sk.push(i);
            continue;
        }
        
        int t = sk.top();
        sk.pop();
        while(sk.size()>=1 && orientation(points[sk.top()],points[t],points[i]) > 0)
        {
            t = sk.top();
            sk.pop();
        }
        
        sk.push(t);
        sk.push(i);
    }
    sk.pop();

    vector<vector<int>> res;
    set<int> st;
    while(!sk.empty())
    {
        int t = sk.top();
        sk.pop();
        if(st.find(t) == st.end())
        {
            res.push_back(points[t]);
        }
        st.insert(t);
    }

    return res;
}


int main()
{
    vector<vector<int>> points = {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}}; //[[1,1],[2,0],[4,2],[3,3],[2,4]]
    // points = {{1,2},{2,2},{4,2}}; //[[1,2],[2,2],[4,2]]
    // points = {{1,2}};
    points = {{1,2},{2,2},{4,2},{5,2},{6,2},{7,2}};
    points = {{0,0},{0,100},{100,100},{100,0}};
    points = {{0,0},{0,100},{100,100},{100,0},{50,50}};
    vector<vector<int>> res = outerTrees4(points);
    for(auto a :res)
    {
        printf("[");
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("],");
    }
    printf("\n");
    return 0;
}