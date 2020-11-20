//391. 完美矩形

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

void removeRect(map<vector<int>,int>& um,vector<int>& rect)
{
    //左
    um.erase({0,rect[0],rect[1],rect[0],rect[3]});

    //上
    um.erase({1,rect[0],rect[3],rect[2],rect[3]});

    //右
    um.erase({2,rect[2],rect[1],rect[2],rect[3]});

    //下
    um.erase({3,rect[0],rect[1],rect[2],rect[1]});
}

bool addOrCombineRect(map<vector<int>,int>& um, vector<int>& rect)
{
    //左
    vector<int> left = {0,rect[0],rect[1],rect[0],rect[3]};
    //上
    vector<int> up = {1,rect[0],rect[3],rect[2],rect[3]};
    //右
    vector<int> right={2,rect[2],rect[1],rect[2],rect[3]};
    //下
    vector<int> bottom = {3,rect[0],rect[1],rect[2],rect[1]};

    //左重合
    if(um.find(left) != um.end())
    {
        return false;
    }
    //左结合,0对2
    vector<int> tmp = {2,rect[0],rect[1],rect[0],rect[3]};
    if(um.find(tmp) != um.end())
    {
        //清除
        int len = um[tmp];
        vector<int> rt = {rect[0]-len,rect[1],rect[0],rect[3]};
        removeRect(um,rt);

        vector<int> newRt ={rt[0],rt[1],rect[2],rect[3]};
        //添加新的
        return addOrCombineRect(um,newRt);
    }

    //上重合
    if(um.find(up) != um.end())
    {
        return false;
    }
    //上结合
    tmp = {3,rect[0],rect[3],rect[2],rect[3]}; 
    if(um.find(tmp) != um.end())
    {
        //清除
        int len = um[tmp];
        vector<int> rt = {rect[0],rect[3],rect[2],rect[3]+len};
        removeRect(um,rt);

        vector<int> newRt ={rect[0],rect[1],rt[2],rt[3]};
        //添加新的
        return addOrCombineRect(um,newRt);
    }

    //右重合
    if(um.find(right)!=um.end())
    {
        return false;
    }
    //右结合
    tmp = {0,rect[2],rect[1],rect[2],rect[3]};
    if(um.find(tmp) != um.end())
    {
        //清除
        int len = um[tmp];
        vector<int> rt = {rect[2],rect[1],rect[2]+len,rect[3]};
        removeRect(um,rt);

        vector<int> newRt ={rect[0],rect[1],rt[2],rt[3]};
        //添加新的
        return addOrCombineRect(um,newRt);
    }

    //下重合
    if(um.find(bottom) != um.end())
    {
        return false;
    }
    //下结合
    tmp = {1,rect[0],rect[1],rect[2],rect[1]};
    if(um.find(tmp) != um.end())
    {
        //清除
        int len = um[tmp];
        vector<int> rt = {rect[0],rect[1]-len,rect[2],rect[1]};
        removeRect(um,rt);

        vector<int> newRt ={rt[0],rt[1],rect[2],rect[3]};
        //添加新的
        return addOrCombineRect(um,newRt);
    }

    um.insert({left,rect[2]-rect[0]});
    um.insert({up,rect[3]-rect[1]});
    um.insert({right,rect[2]-rect[0]});
    um.insert({bottom,rect[3]-rect[1]});

    return true;
}

bool isRectangleCover(vector<vector<int>>& rectangles) {
    //思路：可以考虑面积，精确覆盖的意思就是面积和与其覆盖的矩形面积相等
    //但这个不是充分条件，反例就是通过重合可以构建相等的面积
    //先考虑简单的，
    //1.只有一个元素，肯定是；
    //2.两个元素，首先要相邻，然后相邻的一边长度相等；
    //3.三个元素，分为1个和两个，其中两个符合2的情况，把这两个合并为1个，再与第三个组成2的情况
    //4.可分为1个和3个，所以这个情况可以递归
    //这样是不是可以借鉴双数之和的思想，记录可合并的情况，每次遍历到一个新的矩形就让其与之前的矩形合并
    //如果最后剩下一个矩形，那么就是完美矩形

    //没通过，没通过测试例子太大，不好看出来

    map<vector<int>,int> um;
    
    for(auto r : rectangles)
    {
        if(!addOrCombineRect(um,r))
        {
            return false;
        }
    }

    return um.size() == 4 or um.size() == 0;
}

bool isRectangleCover2(vector<vector<int>>& rectangles) {
    //思路：坐标消融法，把矩形的4个点坐标都计算出来，发现完美矩形的4个点只出现一次，其它的都出现多次
    //所以判断条件：出现多次的顶点消除，最后只剩4个点，这4个点构成的矩形的面积等于子矩形的面积和

    map<pair<int,int>,int> um;
    int area = 0;
    for(auto a : rectangles)
    {
        area += (a[2]-a[0])*(a[3]-a[1]);

        um[{a[0],a[1]}]++;
        um[{a[0],a[3]}]++;
        um[{a[2],a[1]}]++;
        um[{a[2],a[3]}]++;
    }

    int count = 0;
    int x1=INT_MAX,y1=INT_MAX,x2=INT_MIN,y2=INT_MIN;
    for(auto a : um)
    {
        if(a.second % 2 == 1)
        {
            ++count;
            x1 = min(x1,a.first.first);
            y1 = min(y1,a.first.second);
            x2 = max(x2,a.first.first);
            y2 = max(y2,a.first.second);
        }
    }

    return count == 4 && area == (x2-x1)*(y2-y1);
}

int main()
{
    vector<vector<int>> rectangles = {
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4}
    }; //true


    // rectangles = {
    //     {1,1,2,3},
    //     {1,3,2,4},
    //     {3,1,4,2},
    //     {3,2,4,4}
    // };  //false;


    // rectangles = {
    //     {1,1,3,3},
    //     {3,1,4,2},
    //     {1,3,2,4},
    //     {3,2,4,4}
    // };  //false

    // rectangles = {
    //     {1,1,3,3},
    //     {3,1,4,2},
    //     {1,3,2,4},
    //     {2,2,4,4}
    // };//false

    rectangles = {{0,0,1,1},{0,1,1,2},{0,2,1,3},{1,0,2,1},{1,0,2,1},{1,2,2,3},{2,0,3,1},{2,1,3,2},{2,2,3,3}}; //false

    printf(isRectangleCover(rectangles) ? "true\n" : "false\n");
    return 0;
}