//leetcode 593 有效正方形

#include <cstdio>
#include <vector>

using namespace std;

bool isVertical(vector<int>& p1, vector<int>& p2,vector<int>& p3)
{
    int v20 = p2[0] - p1[0];
    int v21 = p2[1] - p1[1];

    int v30 = p3[0] - p1[0];
    int v31 = p3[1] - p1[1];

    return ((v20 != 0 || v21 != 0) && (v30 !=0 || v31 != 0)) && (v20 * v30 + v21 * v31 == 0);
}

bool isVertical2(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
{
    int v0 = p1[0]-p2[0];
    int v1 = p1[1]-p2[1];

    int v2 = p3[0]-p4[0];
    int v3 = p3[1]-p4[1];

    return (v0 != 0 || v1 !=0) && (v2 != 0 || v3 != 0) && v0 * v2 + v1 * v3 == 0;
}

bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
    
    //思路：暴力破解可以，但不高效
    //使用向量垂直，选取p1点，如果有两个点与其构成的向量互相垂直，此时，如果剩下的那个点也是这样，则是正方形
    
    return (isVertical(p1,p2,p3) && isVertical(p4,p2,p3) && isVertical2(p1,p4,p2,p3))
    ||(isVertical(p1,p3,p4) && isVertical(p2,p3,p4) && isVertical2(p1,p2,p3,p4))
    ||(isVertical(p1,p2,p4) && isVertical(p3,p2,p4) && isVertical2(p1,p3,p2,p4));
}

int main()
{
    vector<int> p1 = {0,1};
    vector<int> p2 = {1,0};
    vector<int> p3 = {-1,0};
    vector<int> p4 = {0,-1};
    printf(validSquare(p1,p2,p3,p4) ? "true\n":"false\n");
    return 0;
}