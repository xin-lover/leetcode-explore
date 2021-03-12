//675. 为高尔夫比赛砍树

#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

//行不通
void dfs(vector<vector<int>>& forest,int trees,int x,int y,int curHeight,int step,int& mnSteps)
{
    int m = forest.size();
    int n = m==0 ? 0 : forest[0].size();

    if(x>=m || x < 0 || y >=n || y < 0)
    {
        return;
    }

    if(forest[x][y]==0 || forest[x][y] == -1)
    {
        return;
    }

    if(forest[x][y] > 1)
    {
        if(forest[x][y] <= curHeight)
        {
            return;
        }
        trees -= forest[x][y];
        curHeight = forest[x][y];
        if(trees == 0)
        {
            mnSteps = min(step,mnSteps);
            return;
        }
        forest[x][y] = 1;
    }

    forest[x][y]=-1;
    dfs(forest,trees,x+1,y,curHeight,step+1,mnSteps);
    dfs(forest,trees,x-1,y,curHeight,step+1,mnSteps);
    dfs(forest,trees,x,y+1,curHeight,step+1,mnSteps);
    dfs(forest,trees,x,y-1,curHeight,step+1,mnSteps);
    forest[x][y]=1;
}


int steps(vector<vector<int>>& forest, vector<vector<int>>& stepsDP,int x1,int y1,int x2,int y2)
{
    int m = forest.size();
    int n = forest[0].size();

    if(x1 == x2 && y1 == y2)
    {
        return 0;
    }

    if(x1 < 0 || x1 >=m || y1 < 0 || y1 >= n)
    {
        return INT_MAX;
    }

    if(forest[x1][y1] == 0 || forest[x1][y1] < 0)
    {
        return INT_MAX;
    }

    if(stepsDP[x1][y1] == INT_MAX)
    {
        forest[x1][y1] = -forest[x1][y1];
        int t1 = steps(forest,stepsDP,x1+1,y1,x2,y2);
        int t2 = steps(forest,stepsDP,x1-1,y1,x2,y2);
        int t3 = steps(forest,stepsDP,x1,y1+1,x2,y2);
        int t4 = steps(forest,stepsDP,x1,y1-1,x2,y2);
        forest[x1][y1] = -forest[x1][y1];

        int t = min(min(t1,t2),min(t3,t4));
        stepsDP[x1][y1] = t == INT_MAX ? INT_MAX : 1+t;
    }


    return  stepsDP[x1][y1];

}

//bfs。。。。
int steps2(vector<vector<int>>& forest, int x1,int y1,int x2,int y2)
{
    int m = forest.size();
    int n = forest[0].size();

    if(x1 == x2 && y1 == y2)
    {
        return 0;
    }

    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    vector<vector<bool>> flags(m,vector<bool>(n,false));
    queue<pair<int,int>> qu;
    qu.push({x1,y1});
    flags[x1][y1] = true;
    int r = 0;
    while(!qu.empty())
    {
        int sz = qu.size();
        for(int i=0;i<sz;++i)
        {
            auto pos = qu.front();
            qu.pop();

            for(int j=0;j<dirs.size();++j)
            {
                int x = pos.first + dirs[j].first;
                int y = pos.second + dirs[j].second;

                if(x>=0 && x < m && y >=0 && y <n && !flags[x][y] && forest[x][y] != 0)
                {
                    if(x == x2 && y == y2)
                    {
                        return r+1;
                    }
                    flags[x][y] = true; //要在这里做，避免否则当前步的会出现重复遍历。。
                    qu.push({x,y});
                }
            }
        }

        ++r;
    }

    return -1;
}

//A*算法
int steps3(vector<vector<int>>& forest, int x1,int y1,int x2,int y2)
{
    int m = forest.size();
    int n = forest[0].size();

    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};   

    auto cmp = [](const vector<int>& a, const vector<int>& b)
    {
        return a[0] > b[0];
    };
    priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);

    unordered_map<int,int> um;
    um.insert({x1*n+y1,0});

    pq.push({0,0,x1,y1});
    while(!pq.empty())
    {
        auto st = pq.top();
        pq.pop();

        int g = st[1],x=st[2],y=st[3];
        if(x == x2 && y == y2)
        {
            return g;
        }

        for(int i=0;i<dirs.size();++i)
        {
            int nx = x + dirs[i].first;
            int ny = y + dirs[i].second;

            if(nx >=0 && nx < m && ny>=0 && ny<n && forest[nx][ny] > 0)
            {
                int ncost = 1 + g + abs(nx - x2) + abs(ny-y2);
                if(um.find(nx*n+ny) == um.end() || ncost< um[nx*n+ny])
                {
                    pq.push({ncost,g+1,nx,ny});
                    um[nx*n+ny] = ncost;
                }
            }
        }
    }

    return -1;
}

//hadlock 算法。。。
// int hadlocks(List<List<Integer>> forest, int sr, int sc, int tr, int tc) {
//     int R = forest.size(), C = forest.get(0).size();
//     Set<Integer> processed = new HashSet();
//     Deque<int[]> deque = new ArrayDeque();
//     deque.offerFirst(new int[]{0, sr, sc});
//     while (!deque.isEmpty()) {
//         int[] cur = deque.pollFirst();
//         int detours = cur[0], r = cur[1], c = cur[2];
//         if (!processed.contains(r*C + c)) {
//             processed.add(r*C + c);
//             if (r == tr && c == tc) {
//                 return Math.abs(sr-tr) + Math.abs(sc-tc) + 2 * detours;
//             }
//             for (int di = 0; di < 4; ++di) {
//                 int nr = r + dr[di];
//                 int nc = c + dc[di];
//                 boolean closer;
//                 if (di <= 1) closer = di == 0 ? r > tr : r < tr;
//                 else closer = di == 2 ? c > tc : c < tc;
//                 if (0 <= nr && nr < R && 0 <= nc && nc < C && forest.get(nr).get(nc) > 0) {
//                     if (closer) deque.offerFirst(new int[]{detours, nr, nc});
//                     else deque.offerLast(new int[]{detours+1, nr, nc});
//                 }
//             }
//         }
//     }
//     return -1;
// }

int cutOffTree(vector<vector<int>>& forest) {
    //思路：先dfs试试,这个不行，主要因为，第一砍树有要求，先矮后高
    //第二，有树的位置，当前可以选择砍，可以不砍（后面砍），所以同一个位置可以经过多次。。。
    //不考虑dfs，根据从低到高砍，那么直接排序树的高度，因为没有相同高度，所以砍的顺序是固定的。。。
    //那么问题在于如何从当前点越过障碍到目标点。。。
    //所以问题变成了如何求(a,b)到(c,d)的最少步数。
    //用dfs求。。。复杂度有点高。。。

    if(forest.empty() || forest[0].empty())
    {
        return 0;
    }

    vector<vector<int>> trees;
    for(int i=0;i<forest.size();++i)
    {
        for(int j=0;j<forest[i].size();++j)
        {
            if(forest[i][j] > 1)
            {
                trees.push_back({forest[i][j],i,j});
            }
        }
    }

    sort(trees.begin(),trees.end(),[](const vector<int>& a,const vector<int>& b)
    {
        return a[0] < b[0];
    });

    vector<vector<int>> stepsDP(forest.size(),vector<int>(forest[0].size(),INT_MAX));
    int res = 0;
    int lastX=0,lastY=0;
    for(auto a : trees)
    {
        //第一种
        // for(int i=0;i<stepsDP.size();++i)
        // {
        //     for(int j=0;j<stepsDP[i].size();++j)
        //     {
        //         stepsDP[i][j] = INT_MAX;
        //     }
        // }
        // int t = steps(forest, stepsDP,lastX,lastY,a[1],a[2]);
        // if(t == INT_MAX)
        // {
        //     return -1;
        // }

        int t =  steps3(forest,lastX,lastY,a[1],a[2]);
        if(t == -1)
        {
            return -1;
        }

        res += t;
        lastX = a[1];
        lastY = a[2];
    }

    return res;
}

int main()
{
    vector<vector<int>> forest = {{1,2,3},{0,0,4},{7,6,5}}; //6
    // forest = {{1,2,3},{0,0,0},{7,6,5}}; //-1
    // forest = {{2,3,4},{0,0,5},{8,7,6}}; //6
    forest = {{54581641,64080174,24346381,69107959},{86374198,61363882,68783324,79706116},{668150,92178815,89819108,94701471},{83920491,22724204,46281641,47531096},{89078499,18904913,25462145,60813308}}; //57
    printf("%d\n",cutOffTree(forest));

    return 0;
}