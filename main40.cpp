#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Solution {
public:
    Solution(double radius, double x_center, double y_center) {
        radius_ = radius;
        x_center_ = x_center;
        y_center_ = y_center;
    }
    
    vector<double> randPoint() {
        //思路：随机数，如果点不在圆范围内，则重新随机


        uniform_real_distribution<double> rd(0.0,radius_);
        double x = radius_;
        double y = radius_;
        while(x*x + y*y > radius_ * radius_)
        {
            x = rd(e);
            y = rd(e);
        }

        return {x+x_center_,y + y_center_};
    }

    double radius_;
    double x_center_;
    double y_center_;
    default_random_engine e;
    
};

int main()
{
    Solution s(1.0,0.0,0.0);
    for(int i=0;i<3;++i)
    {
        for(auto a : s.randPoint())
        {
            printf("%f ",a);
        }
        printf("\n");
    }
}