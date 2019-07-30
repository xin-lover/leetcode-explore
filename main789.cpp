//leetcode 789. 逃脱阻碍者

#include <cstdio>
#include <vector>

using namespace std;

bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
    //先考虑绝对会被抓到的情况，就是ghost在（1，1）这个位置，
    //如果只能往一个方向走，则ghost在前面则肯定会被抓住，
    //因为同时到达目标处也会认为是抓住，所以问题是不是可以转化为谁先到目的地？
    
    int steps = abs(target[0]) + abs(target[1]);
    for(int i=0;i<ghosts.size();++i)
    {
        if(abs(ghosts[i][0] - target[0]) + abs(ghosts[i][1] - target[1]) <= steps)
        {
            return false;
        }
    }

    return true;

}

int main()
{
    vector<vector<int>> ghosts = {{1, 0}, {0, 3}};
    vector<int> target = {0,1};
    ghosts={{1,0}};
    target = {2,0};
    ghosts = {{1,9},{2,-5},{3,8},{9,8},{-1,3}};
    target = {8,-10};
    printf(escapeGhosts(ghosts,target) ? "true\n" : "false\n");
    return 0;
}