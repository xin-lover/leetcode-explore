#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    //把左右矩形的点存入vector，然后使用随机函数pick
    Solution(vector<vector<int>> rects) {
        
        for(int i=0;i<rects.size();++i)
        {
            auto r = rects[i];
            for(int j = r[0];j<=r[2];++j)
            {
                for(int k=r[1];k<=r[3];++k)
                {
                    points_.push_back({j,k});
                }
            }
        }
    }
    
    vector<int> pick() {
        int n = points_.size();
        int index = rand() % n;
        return points_[index];
    }
    
    vector<vector<int>> points_;
};

int main()
{
    vector<vector<int>> rects;
    Solution s({{1,1,5,5}});
    s.pick();
    return 0;
}