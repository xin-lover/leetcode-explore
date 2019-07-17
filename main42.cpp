#include <cstdio>
#include <vector>
// #include <map>
#include <unordered_map>

using namespace std;

int leastBricks(vector<vector<int>>& wall) {
    //思路：记录每一块砖的右端点，右端点重合数量最多的点即划线点

    unordered_map<int,int> um;
    for(int i=0;i<wall.size();++i)
    {
        int right = 0;
        for(int j =0;j<wall[i].size()-1;++j)
        {
            right += wall[i][j];
            printf("right%d\n",right);
            if(um.find(right) == um.end())
            {
                um[right] = 1;
            }
            else
            {
                ++um[right];
            }
        }
    }

    int mx = 0;
    for(auto it = um.begin();it != um.end();++it)
    {
        printf("end:%d\n",it->second);
        if(it->second > mx)
        {
            mx = it->second;
        }
    }

    return wall.size() - mx;
}

int main()
{
    vector<vector<int>> v = {{1,2,2,1},
      {3,1,2},
      {1,3,2},
      {2,4},
      {3,1,2},
      {1,3,1,1}};

    printf("%d\n",leastBricks(v));
    return 0;
}