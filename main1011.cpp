//1011. 在 D 天内送达包裹的能力

#include <cstdio>
#include <vector>

using namespace std;

int shipWithinDays(vector<int>& weights, int D) {
    //思路：因为顺序不能改，而要船的数量小，那么每个船装的数量应该尽量平均
    //同时必须大于每个货物的数量
    //然后验证一下，但是这个值不能作为最终的值，最终的值由前面几个货物决定，其实就是多一个和少一个货物的区别
    //思路不对，必须要考虑每一船货物

    int sum=0;
    int mxWeight = 0; 
    for(int i=0;i<weights.size();++i)
    {
        sum+=weights[i];
        mxWeight = max(weights[i],mxWeight);
    }

    int threshold = max(mxWeight, sum / D + (sum % D == 0 ? 0 : 1));
    int expected1 = -1;
    int expected2 = -1;
    int tmp = 0;
    for(int i=0;i<weights.size();++i)
    {
        tmp += weights[i];
        if(tmp > threshold)
        {
            expected1 = max(threshold,tmp - weights[i]);
            expected2 = tmp;
            break;
        }
    }

    int d = 1;
    tmp = 0;
    for(int i=0;i<weights.size();++i)
    {
        tmp += weights[i];
        if(tmp > expected1)
        {
            tmp = weights[i];
            ++d;
        }
    }

    // printf("d:%d\n",d);
    printf("aa:%d\n",expected2);
    return d > D ? expected2 : expected1;
}

int shipWithinDays2(vector<int>& weights, int D) {
    //思路：上面的思路是一次就确定期望的值，显然不行
    //而且不能以前面的货物来确定最小载重，也不能用最大值，因为两个小一点的值的合重可能是最大的
    //所以，对于每个货物其实我们没有办法确定它应该载在哪条船上
    //唯一能确定的就是第一个货物在第一条船上，之后的每个货物都在i条船和这i+1条船之间选择
    //可以考虑递归，第i个货物选择第k天上船，其实就是max(f(0,i-1,0,k-1),f(i,n-1,k,D))
    //这样选择太多
    //考虑二分，因为最大数量已经确定，而判断条件就是验证使用这个载重需要多少天

    int sum = 0;
    for(auto a : weights)
    {
        sum += a;
    }

    int lower = 0,upper = sum;
    int mnLoad = 0;
    while(lower < upper)
    {
        mnLoad = lower + (upper - lower) / 2;

        int d = 0;
        int tmp = 0;
        for(int i=0;i<weights.size();++i)
        {
            tmp += weights[i];
            if(tmp > mnLoad)
            {
                ++d;
                tmp = weights[i];
                if(tmp > mnLoad)
                {
                    d = D+1;
                }
            }   
        }

        d += (tmp == 0 ? 0 : 1);

        if(d > D)
        {
            lower = mnLoad+1;
        }
        else
        {
            upper = mnLoad;
        }
    }

    return lower;
}

int shipWithinDays3(vector<int>& weights, int D) {
    //考虑二分，因为最大数量已经确定，而判断条件就是验证使用这个载重需要多少天
    //优化，最小载重应该是单个货物的最大值

    int sum = 0;
    int mxw = 0;
    for(auto a : weights)
    {
        sum += a;
        mxw = max(mxw,a);
    }

    int lower = mxw,upper = sum;
    int mnLoad = 0;
    while(lower < upper)
    {
        mnLoad = lower + (upper - lower) / 2;

        int d = 0;
        int tmp = 0;
        for(int i=0;i<weights.size();++i)
        {
            tmp += weights[i];
            if(tmp > mnLoad)
            {
                ++d;
                tmp = weights[i];
            }   
        }

        d += (tmp == 0 ? 0 : 1);

        if(d > D)
        {
            lower = mnLoad+1;
        }
        else
        {
            upper = mnLoad;
        }
    }

    return lower;
}

int main()
{
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    int D = 5; //15
    printf("%d\n",shipWithinDays3(v,D));
    v = {3,2,2,4,1,4}; 
    D = 3; //6
    printf("%d\n",shipWithinDays3(v,D));
    v = {1,2,3,1,1};
    D=4; //3
    printf("%d\n",shipWithinDays3(v,D));

    v = {147,73,265,305,191,152,192,293,309,292,182,157,381,287,73,162,313,366,346,47};
    D = 10;
    printf("%d\n",shipWithinDays3(v,D)); //602
    return 0;
}