//1344. 时钟指针的夹角

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

double angleClock(int hour, int minutes) {
    //思路：计算两个指针所在的角度，相减即可
    //重点在于时针角度计算，是本身代表角度+指针代表的额外角度

    //时针角度
    double hourAngle = hour * (360.0 / 12.0);
    double minutesAngle = minutes * (360.0 / 60.0);

    //一小时只占30度，根据minutes计算时针在这个区域类的角度
    hourAngle += (minutes / 60.0 * (360.0/ 12.0));

    double dif = abs(hourAngle - minutesAngle);
    return min(dif, abs(360.0 - dif));
}

int main()
{
    printf("%lf\n",angleClock(12,30));//165
    printf("%lf\n",angleClock(3,30));//75;
    printf("%lf\n",angleClock(3,15));//7.5

    return 0;
}