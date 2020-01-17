//1041. 困于环中的机器人

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

bool isRobotBounded(string instructions) {
    //思路：四个方向，我们使用四个向量来表示，左转右转我们可以使用下标的前进后退来表示
    //注意成环的条件，是会回到原点
    //但这里可能是重复n次后，回到原点，也可能在一次指令内到远点
    //所以我们不能用执行完一次指令后是否在原点来判断
    //需要通过最终的位置和朝向判断，
    //首先我们考虑是否可以通过奇数次重复成环，看这样一个例子，“GRGRGR",很明显是可以的
    //所以也不能通过一次指令的位置和朝向判断
    //我们需要识别重复指令，也就是说我们要简化instruction,比如"GRGRGR"，需要简化为"GR"
    //然后判断这个最简单的指令对位置和朝向的影响，这个指令最多4次就会重复，如果超过4次都不重复，那就不成环
    //这样一想，那我们可以重新

    vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    vector<int> pos = {0,0};
    int cur = 0;
    for(int j=0;j<4;++j)
    {
        for(int i=0;i<instructions.size();++i)
        {
            switch (instructions[i])
            {
            case  'G':
                cur = (cur % 4 + 4)%4;
                pos[0]+=dirs[cur][0];
                pos[1]+=dirs[cur][1];
                break;
            case 'L':
                --cur;
                break;
            case 'R':
                ++cur;
                break;
            default:
                break;
            }
        }

        if(pos[0] == 0 && pos[1] == 0)
        {
            return true;
        }
    }

    return false;
}

bool isRobotBounded2(string instructions) {
    //思路：不用重新移动，根据最后的方向变化位置和朝向即可
    //假设向北为正向，位移(x,y),现在右转，变为向东，坐标系变了，在新坐标系中的(x,y)，映射为原始坐标系的(y,-x)
    //向南则变为(-x,-y),向西则变为(-y,x)
    //所以根据朝向变化位移即可

    vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    // vector<vector<int>> trans = {{1,1},{-1,1},{1,-1},{-1,-1}};
    vector<int> pos = {0,0};
    int cur = 0;
    for(int i=0;i<instructions.size();++i)
    {
        switch (instructions[i])
        {
        case  'G':
            cur = (cur % 4 + 4)%4;
            pos[0]+=dirs[cur][0];
            pos[1]+=dirs[cur][1];
            break;
        case 'L':
            --cur;
            break;
        case 'R':
            ++cur;
            break;
        default:
            break;
        }
    }

    vector<int> offset = pos;
    cur = (cur % 4 + 4)%4;
    int d = cur;
    for(int i=0;i<4;++i)
    {
        if(pos[0] == 0 && pos[1] == 0)
        {
            return true;
        }

        switch (cur)
        {
        case  0:
            pos[0] += offset[0];//*trans[cur][0];
            pos[1] += offset[1];//*trans[cur][1];
            break;
        case 1:
            pos[0] += offset[1];//*trans[cur][0];
            pos[1] += -offset[0];//*trans[cur][1];
            break;
        case 2:
            pos[0] += -offset[0];//*trans[cur][0];
            pos[1] += -offset[1];//*trans[cur][1];
            break;
        case 3:
            pos[0] += -offset[1];//*trans[cur][0];
            pos[1] += offset[0];//*trans[cur][1];
            break;
        default:
            break;
        }

        cur = (cur + d) % 4;
    }

    return false;
}

bool isRobotBounded3(string instructions) {
    //思路：按指令移动，如果之后位置不在原点且方向是初始方向则返回false
    //也就是说如果一次指令后有个位移和朝向，重复这个位移和朝向，我们会方向，只要方向不是初始方向，总能回到原点

    vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    vector<int> pos = {0,0};
    int cur = 0;
    for(int i=0;i<instructions.size();++i)
    {
        switch (instructions[i])
        {
        case  'G':
            cur = (cur % 4 + 4)%4;
            pos[0]+=dirs[cur][0];
            pos[1]+=dirs[cur][1];
            break;
        case 'L':
            --cur;
            break;
        case 'R':
            ++cur;
            break;
        default:
            break;
        }
    }

    cur = (cur % 4 + 4)%4;
    if(pos[0] == 0 && pos[1]==0)
    {
        return true;
    }
    else if(cur == 0)
    {
        return false;
    }
    
    return true;
}


int main()
{
    printf(isRobotBounded2("GGLLGG") ? "true\n" : "false\n");//true
    printf(isRobotBounded2("GG") ? "true\n" : "false\n");//false
    printf(isRobotBounded2("GL") ? "true\n" : "false\n"); //true
    printf(isRobotBounded2("LGL") ? "true\n" : "false\n");//true
    return 0;
}