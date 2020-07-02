//1401. 圆和矩形是否有重叠

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
    //思路：简单的算法就是分别求4条边与圆的交点，如果在圆内，则重叠
    //如果用开根，则性能太慢了
    //还是分情况：
    //1.如果圆完全在四边形的一条边的一侧，则不可能相交
    //2.另一种不相交则是在圆的外接四边形的某个角
    //互相包含的情况没有考虑

    //考虑投影，如果重叠，那么我们在两个图形的中心连一条线，这条线在x，y轴上的投影肯定相交
    //这个思路也不对，连线的投影和圆的半径以及四边形边在轴上的投影没关系

    // double quad_center_x = (x1+x2)*0.5;
    // double quad_center_y = (y1+y2)*0.5;

    // double vx = quad_center_x - x_center;
    // double vy = quad_center_y - y_center;

    // printf("%f %f\n",vx,(radius + abs(quad_center_x - x1)));
    // return abs(vx) <= (radius + abs(quad_center_x - x1)) && abs(vy) <= (radius + abs(quad_center_y - y1));

    //简单点，在两个中心连一条线，求这条线的方程，求出这条线与4条边的交点，判断是否在圆内,这个思路是默认圆心是在四边形外，所以还要现判定这个条件
    //不对，交点未必在这条连线上

    if(x_center >= x1 && x_center <= x2 && y_center >= y1 && y_center <= y2)
    {
        return true;
    }
    
    double kx = (x1+x2)*0.5 - x_center;
    double ky = (y1+y2)*0.5 - y_center;

    if(kx == 0.0)
    {
        return !(y2 < y_center - radius || y1 > y_center + radius);
    }

    if(ky == 0.0)
    {
        return !(x2 < x_center - radius || x1 > x_center + radius);
    }

    double c = y_center - ky * x_center / kx;

    printf("%f %f %f\n",kx,ky,c);

    double p1_x = x1;
    double p1_y = ky*p1_x/kx+c;
    if(p1_y >= y1 && p1_y <= y2 && (p1_x-x_center)*(p1_x - x_center)+(p1_y-y_center)*(p1_y-y_center) <= radius*radius)
    {
        return true;
    }

    double p2_x = x2;
    double p2_y = ky*p2_x/kx+c;
    if(p2_y >= y1 && p2_y <= y2 && (p2_x-x_center)*(p2_x - x_center)+(p2_y-y_center)*(p2_y-y_center) <= radius*radius)
    {
        return true;
    }

    double p3_y = y1;
    double p3_x = (p3_y - c)*kx / ky;
    if(p3_x >= x1 && p3_x <= x2 && (p3_x-x_center)*(p3_x - x_center)+(p3_y-y_center)*(p3_y-y_center) <= radius*radius)
    {
        return true;
    }

    double p4_y = y1;
    double p4_x = (p4_y - c)*kx / ky;
    if(p4_x >=x1 && p4_x <= x2 && (p4_x-x_center)*(p4_x - x_center)+(p4_y-y_center)*(p4_y-y_center) <= radius*radius)
    {
        return true;
    }

    return false;
}

bool checkOverlap2(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
    //思路：交点未必在连线上，所以我们还是分情况考虑
    //1.圆在四边形内
    //2.圆与四边形的某条边相交
    //3.不相交
    //前两者重叠,所以只需要求4条边与圆的交点即可，存在交点且在边上，则重叠
    //避免求根，wom

    if(x_center >= x1 && x_center <= x2 && y_center >= y1 && y_center <= y2)
    {
        return true;
    }

    if(y2 >= y_center-radius && y2 <= y_center + radius)
    {
        double p = sqrt(radius*radius-(y2-y_center)*(y2-y_center));
        if(!(x_center-p > x2 || x_center + p < x1))
        {
            return true;
        }
    }
    if(y1 >= y_center-radius && y1 <= y_center + radius)
    {
        double p = sqrt(radius*radius-(y1-y_center)*(y1-y_center));
        if(!(x_center-p > x2 || x_center + p < x1))
        {
            return true;
        }
    }

    if(x2 >= x_center-radius && x2 <= x_center + radius)
    {
        double p = sqrt(radius*radius-(x2-x_center)*(x2-x_center));
        if(!(y_center-p > y2 || y_center + p < y1))
        {
            return true;
        }
    }

    if(x1 >= x_center-radius && x1 <= x_center + radius)
    {
        double p = sqrt(radius*radius-(x1-x_center)*(x1-x_center));
        if(!(y_center-p > y2 || y_center + p < y1))
        {
            return true;
        }
    }
    
    return false;
    // return (radius*radius-(y2-y_center)*(y2-y_center) <= min((x1-x_center)*(x1-x_center),(x2-x_center)*(x2-x_center))
    // || radius*radius-(y1-y_center)*(y1-y_center) <= min((x1-x_center)*(x1-x_center),(x2-x_center)*(x2-x_center))
    // || radius*radius-(x1-x_center)*(x1-x_center) <= min((y1-y_center)*(y1-y_center),(y2-y_center)*(y2-y_center))
    // || radius*radius-(x2-x_center)*(x2-x_center) <= min((y1-y_center)*(y1-y_center),(y2-y_center)*(y2-y_center)));

}

// 划分区域：
// 我们很容易想到应该使用划分区域的方法，划分区域的方法有很多，这里介绍其中一种方法。
// 将矩形分为9个区域，判定圆心的位置在哪个区域：
// 如果圆心在矩形的内部，则一定相交；
// 如果圆心位于矩形的上下左右四个区域当中，检测圆心到边的距离，判定是否相交；
// 如果圆心位于四个角对应的区域，只要检测矩形的四个顶点是否在圆的内部即可。


// 思路
// 计算矩形的中心点 (x0, y0)
// 11. 将这个点定义为坐标轴原点

// 计算矩形的中心点到圆心的向量 p
// 21. 通过绝对值，将圆心转移至第一象限
// 22. 在哪个象限并不重要，他们之间是相对关系

// 计算矩形的中心点到矩形右上角的向量 q

// 通过 p - q 得到从矩形右上角到圆心的向量 u
// 41. 将分量为负数设置为 0
// 42. 分量为负，说明可以找到更短的距离，设置为 0 相当于做垂线
// 43. 当 x 和 y 都为负，说明圆心在矩形内

// 比较 u 和圆形半径 radius 的长度

// 解题思路
// 先计算矩形中心，边长；
// 把矩形中心，圆心投影到坐标轴上；
// 计算矩形中心与圆心在坐标轴上的距离；
// 判断，圆心超出矩形的距离是否小于等于圆的半径;

// class Solution {
// public:
//     bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
//         double x= 0.5*(x1+x2),y=0.5*(y1+y2);
//         double lenx = x2-x1,leny = y2-y1;
//         double disx = abs(x_center-x);
//         double disy = abs(y_center-y);
//         double dis = max(disx-lenx/2,0.0)*max(disx-lenx/2,0.0)+max(disy-leny/2,0.0)*max(disy-leny/2,0.0);
//         return dis<=radius*radius;
//     }
// };

bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) 
{
    double x0 = (x1 + x2) / 2.0;
    double y0 = (y1 + y2) / 2.0;

    vector<double> p = { abs(x_center - x0) , abs(y_center - y0) };
    vector<double> q = { x2 - x0, y2 - y0 };
    
    vector<double> u = { max(p[0] - q[0], 0.0), max(p[1] - q[1], 0.0) };

    return sqrt(u[0] * u[0] + u[1] * u[1]) <= radius;   
}



int main()
{
    int radius = 1, x_center = 0, y_center = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1; //true;
    // radius = 1, x_center = 1, y_center = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1;   //false;
    // radius = 1, x_center = 1, y_center = 1, x1 = -3, y1 = -3, x2 = 3, y2 = 3;   //true;
    // radius = 5,x_center = 8,y_center = 8,x1=9,y1=5,x2=12,y2=8;  //true
    radius =1415, x_center=807, y_center = -784, x1=-733, y1=623, x2=-533, y2=1005; //false;
    radius = 2,x_center=2,y_center=1,x1=4,y1=1,x2=5,y2=5;//true
    radius = 15,x_center=44,y_center=69,x1=46,y1=17,x2=49,y2=20; //false
    printf(checkOverlap2(radius,x_center,y_center,x1,y1,x2,y2) ? "true\n" : "false\n"); 

    return 0;
}