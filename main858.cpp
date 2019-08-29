//leetcode 858. 镜面反射

#include <cstdio>
#include <vector>

using namespace std;

int mirrorReflection(int p, int q) {
    //思路：根据反射定理，每次反射回来，光线相当于上升2q，当不足2q时，会经过顶部镜子反射向下
    //相当于反向，那光线进入收集器的可以根据上升或下降的高度来判断，如果刚好为p，则进入搜集器
    //反向后的递推公式：q=q-r


    if(q == 0)
    {
        return 0;
    }

    bool right = true;
    bool up = true;
    int start = 0;
    while(true)
    {
        int t = (p-start)%(2*q);
        if(t == 0)
        {
            if(up)
            {
                return right ? 2 : 1;
            }
            else
            {
                return 0;
            }
            
        }
        else if(t == q)
        {
            if(up)
            {
                return right ? 1 : 2;
            }
            else
            {
                return 0;
            }
        }
        else if(t < q)
        {
            right = !right;
            up = !up;
            start = q-t;
        }
        else
        {
            // right = !right;
            up = !up;
            start = q- (t-q);
            printf("start:%d\n",start);
        }
    }

    return 0;

}

//我们可以假设没有北面的墙壁，无限延长东西两面镜子的长度，则光线会通过东西两面镜子的反射一直往北走，每次增加的纵向距离为 qq。
// 当光线走过的纵向距离为p的整数倍时，光线到达某个接收器。现在问题转化为了怎么求纵向距离以及怎么通过这个距离来判断光线最终将到达哪一个接收器。
// 通过思考不难发现，光线最终向上走的距离即为 pp 和 qq 的最小公倍数，设其为 kk。当 kk 是 pp 的奇数倍时，光线到达北墙；而当 kk 为 pp 的偶数倍时，光线到达南墙。
// 因为题中保证了光线最终会遇到一个接收器，所以光线最终到达南墙必定会遇到接收器 0。若光线最终到达北墙，我们可以通过光线与东西墙接触的次数的奇偶性即 k\%qk%q 来确定光线最终会到达接收器 1 还是 2。
// 若 kk 是 qq 的奇数倍，则光线最终会遇到接收器 1，否则会遇到接收器2。

int gcd(int m,int n)
{
    while(n!=0)
    {
        int t = n;
        n=m%n;
        m = t;
    }

    return m;
}
int mirrorReflection2(int p, int q) {
    int k = (p*q) / gcd(p,q);
    int t1 = k / p;
    int t2 = k / q;

    if((t1 & 1) == 0)
    {
        return 0;
    }

    if((t2 & 1) == 0)
    {
        return 2;
    }

    return 1;
}

int main()
{
    // printf("%d\n",mirrorReflection(2,1));
    printf("%d\n",mirrorReflection2(4,3));
    return 0;
}