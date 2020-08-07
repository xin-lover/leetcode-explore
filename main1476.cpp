//1476. 子矩形查询

#include <cstdio>
#include <vector>

using namespace std;


class SubrectangleQueries {
public:
    SubrectangleQueries(vector<vector<int>>& rectangle) {
        rectangle_ = rectangle;
    }
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        //其它思路：不实际更新，记录更新操作，在查询的时候找最后一个操作
        for(int i=row1;i<=row2;++i)
        {
            for(int j=col1;j<=col2;++j)
            {
                rectangle_[i][j]= newValue;
            }
        }
    }
    
    int getValue(int row, int col) {
        return rectangle_[row][col];
    }

    vector<vector<int>> rectangle_;
};

int main()
{
    vector<vector<int>> rectangle = {{1,2,1},{4,3,4},{3,2,1},{1,1,1}};
    SubrectangleQueries sq(rectangle);
    printf("%d\n",sq.getValue(0,2));
    sq.updateSubrectangle(0,0,3,2,5);
    printf("%d\n",sq.getValue(0,2));
    printf("%d\n",sq.getValue(3,1));
    sq.updateSubrectangle(3,0,3,2,10);
    printf("%d\n",sq.getValue(3,1));
    printf("%d\n",sq.getValue(0,2));

    return 0; 

}

