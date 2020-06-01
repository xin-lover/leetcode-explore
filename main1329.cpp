//1329. 将矩阵按对角线排序

#include <cstdio>
#include <vector>

using namespace std;

void SortDiagonal(vector<vector<int>>& mat,int x,int y) {

    int m = mat.size();
    int n = mat[0].size();
    for(int i=0;x+i<m&&y+i<n;++i)
    {
        for(int j=i;x+j-1>=0 && y+j-1>=0 && mat[x+j][y+j] < mat[x+j-1][y+j-1];--j)
        {
            swap(mat[x+j][y+j],mat[x+j-1][y+j-1]);
        }
    }
}

vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
    //思路：就按题目的思路做，涉及提取对角线和重新构建矩阵
    //不复杂，需要额外的空间
    //另一种就是原地排序了，使用插入排序或者桶排序（因为元素区间[1,100])
    
    if(mat.empty() || mat[0].empty())
    {
        return {};
    }
    int m = mat.size();
    int n = mat[0].size();
    for(int i=0;i<m;++i)
    {
        SortDiagonal(mat,i,0);
    }

    for(int i=1;i<n;++i){
        SortDiagonal(mat,0,i);
    }

    return mat;
}

//其它思路：大体思路都一样，没什么特殊的，其中对角线下标的特性有点意思
//左对角线，i-j值相等，右对角线i+j相等

int main()
{
    vector<vector<int>> mat = {{3,3,1,1},{2,2,1,2},{1,1,1,2}};
    auto res = diagonalSort(mat);

    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }

    return 0;
}