//LCP 03. 机器人大冒险

#include <cstdio>
#include <vector>
#include <string>
#include <set>

using namespace std;


bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
    //思路：只有两个方向，也就是x，y必须大于0，现在的问题是，如何判断是否能到终点
    //而路径上有障碍点，所以问题就变为障碍点是否也可达，所以问题统一为某个点是否可达
    //因为指令无限循环，所以我们采用逼近法，看看到x或y最近的位置需要执行几次

    if(command.empty())
    {
        return x==0 && y==0;
    }

    int xOneLoop = 0,yOneLoop = 0;
    set<vector<int>> steps;
    steps.insert({0,0});
    for(int i=0;i<command.size();++i)
    {
        if(command[i] == 'U')
        {
            yOneLoop++;
        }
        else
        {
            xOneLoop++;
        }

        steps.insert({xOneLoop,yOneLoop});
        printf("%d %d\n",xOneLoop,yOneLoop);
    }

    auto calcStep = [](int x,int y, int xStep,int yStep){
        if(xStep == 0)
        {
            return y / yStep;
        }
        else if(yStep == 0)
        {
            return x / xStep;
        }
        return min(x/xStep,y/yStep);
    };

    int p = calcStep(x,y,xOneLoop,yOneLoop);
    printf("p:%d\n",p);
    int xr = x - xOneLoop * p;
    int yr = y - yOneLoop * p;
    printf("yy:%d %d\n",xr,yr);
    if(steps.find({xr,yr}) == steps.end())
    {
        printf("get\n");
        return false;
    }

    for(int i=0;i<obstacles.size();++i)
    {
        if(obstacles[i][0] + obstacles[i][1] > x+y)
        {
            continue;
        }
        int op = calcStep(obstacles[i][0],obstacles[i][1],xOneLoop,yOneLoop);
        xr = obstacles[i][0] - xOneLoop * op;
        yr = obstacles[i][1] - yOneLoop * op;

        if(op<=p && steps.find({xr,yr}) != steps.end())
        {
            return false;
        }
    }

    return true;
}

int main()
{
    string command = "URR";
    vector<vector<int>> obstacles = {};
    int x = 3, y = 2; //true

    command = "URR", obstacles = {{2, 2}}, x = 3, y = 2; //false
    command = "URR", obstacles = {{4, 2}}, x = 3, y = 2;    //true;

    command = "URRURRR", obstacles={{7, 7}, {0, 5}, {2, 7}, {8, 6}, {8, 7}, {6, 5}, {4, 4}, {0, 3}, {3, 6}},x=4915, y=1966; //true
    command= "URR", obstacles={{4, 2}}, x=3, y=2;//true

    printf(robot(command,obstacles,x,y) ? "true\n" : "false\n");


    return 0;
}