//面试题 16.13. 平分正方形

#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
    //思路：这个题还是考的业务能力，算法体现一般，而且题目描述不清楚
    //看英文表述是分成相等的两半，那第一个问题是，是否肯定存在这样一条直线。。。。
    //我们先看直线切分正方形，要切开的两半相等，直线必须通过正方形中心
    //那么如果题目是吧两个正方形都切成相等的两半，那返回两个正方形中心连线即可。。。。
    //两个正方形，我们考虑其位置，吧一个放正中间，那么只需要考虑另一个正方形的相对位置

    double center1_x = square1[0]+square1[2]*0.5;
    double center1_y = square1[1]+square1[2]*0.5;

    double center2_x = square2[0]+square2[2]*0.5;
    double center2_y = square2[1]+square2[2]*0.5;

    if(abs(center1_x - center2_x) < 0.0000000000001)
    {
        int yBottom = square1[1] < square2[1] ? square1[1] : square2[1];
        int yTop = square1[1] + square1[2] > square2[1] + square2[2] ? square1[1]+square1[2] : square2[1] + square2[2];
        return {center1_x,yBottom*1.0,center1_x,yTop*1.0};
    }
    //kx+a=y
    double k = (center2_y - center1_y) / (center2_x - center1_x);
    double c = center1_y - k * center1_x;

    //根据正方形下方的两个点计算两个刚好与左右两边相交的斜率,正方形，1和-1.。。。
    double kRightTop1 = 1.0;//(center1_y - square1[1]) / (center1_x - square1[0]);
    double kRightBottom1= -1.0;//(center1_y - square1[1]) / (center1_x - square1[0]+square1[2]);

    // double kRightTop2 = (center2_y - square2[1]) / (center2_x - square2[0]);
    // double kRightBottom2= (center2_y - square2[1]) / (center2_x - square2[0]+square2[2]);

    //过中心在两个斜率间
    if(k < kRightTop1 && k > kRightBottom1)
    {
        double xLeft,yLeft,xRight,yRight;
        xLeft = square1[0] < square2[0] ? square1[0] : square2[0];
        yLeft = xLeft * k + c;
        
        xRight = square1[0]+square1[2] > square2[0] + square2[2] ? square1[0] + square1[2] : square2[0] + square2[2];
        yRight = xRight*k+c;

        return {xLeft,yLeft,xRight,yRight};
    }
    else
    {
        double xTop,yTop,xBottom,yBottom;
        yTop = square1[1] + square1[2] > square2[1] + square2[2] ? square1[1] + square1[2] : square2[1] + square2[2];
        xTop = (yTop-c) / k;

        yBottom = square1[1] < square2[1] ? square1[1] : square2[1];
        xBottom = (yBottom-c)/k;
        if(xTop < xBottom)
        {
            return {xTop,yTop,xBottom,yBottom};
        }
        else
        {
            return {xBottom,yBottom,xTop,yTop};
        }
        
    }
}

int main()
{
    vector<int> square1 = {-1, -1, 2}, square2 = {0, -1, 2}; //输出： {-1,0,2,0}

    square1={-2,-2,5},square2= {-3,-3,7}; //0.5 -3.0 0.5 4.0
    square1={68,130,64},square2={-230,194,7}; //[-230.0,197.88055,132.0,158.52067]
    for(auto a : cutSquares(square1,square2))
    {
        printf("%f ",a);
    }
    printf("\n");

    return 0;
}