//1503. 所有蚂蚁掉下来前的最后一刻

#include <cstdio>
#include <vector>

using namespace std;

int getLastMoment(int n, vector<int>& left, vector<int>& right) {
    //思路：我们考虑一只对多只的情况，假设a,b,c,d只蚂蚁，a向右，其它向左
    //那么第一次碰撞在a+(b-a)/2,第二次在a+(b-a)/2+(c-b)/2,第三次在a+(b-a)/2+(c-b)/2+(d-c)/2
    //同理a,b,c,d,e5只蚂蚁，a,b向右，c,d,e向左
    //最后abc向左，de向右，而碰撞点在第二次时右变化，取决于a,b的间距和c,d的间距
    //a,b的间距大，则c，d先碰,在b+(c-b)/2+(d-c)/2,之后c和b同向，等a,b碰(先不考虑d,e碰)
    //这是b,c间是d-c,所以下一次碰撞会在b+(c-b)/2+(d-c)/2-((b-a)-(d-c)) -(d-c)/2
    //=》b+(c-b)/2-((b-a)-(d-c))，也就是第一个碰撞点往间距大的方向移动了间距差的距离
    //而这种状态会一直持续直到没有碰撞
    //集合一只对多只的情况我们得出一个通用的结论，就是第一个碰撞点是最内侧两只相向蚂蚁的位置中点
    //然后碰撞点会根据两侧蚂蚁的间距往大间距方向移动，如果不对称，可以假设没有蚂蚁的那一边间距为0

    //哈哈，这个思路牛逼啊，两只蚂蚁碰到后反向，有点像回家拼车，到达县城后换一辆车。。。。新车把人拉回家，而自己则继续回去拉人。。。
    //注意到题目要求的是最后一只蚂蚁从木板上掉下来的时刻，所以并不需要区分每只蚂蚁。注意到题目中的信息，
    //由于改变移动方向不花费额外时间，而且改变移动方向后的移动速度不变，
    //因此，两只相遇的蚂蚁同时改变移动方向之后的情形等价于两只蚂蚁都不改变移动方向，
    //继续按照原来的方向和速度移动，这样问题就简化成根据每只蚂蚁的初始位置和移动方向得到最后一只蚂蚁到达木板边界的时刻。

    int lastMoment = 0;
    for (int ant : left) {
        lastMoment = max(lastMoment, ant);
    }
    for (int ant : right) {
        lastMoment = max(lastMoment, n - ant);
    }
    return lastMoment;
}

int main()
{
    int n = 7;
    vector<int> left = {}, right = {0,1,2,3,4,5,6,7};

    printf("%d\n",getLastMoment(n,left,right));

    return 0;
}