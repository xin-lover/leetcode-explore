//1094. 拼车

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool carPooling(vector<vector<int>>& trips, int capacity) {
    //思路：其实可以类比区间，也就是上车下车点之间是一个区间
    //问题可以变为区间中的总容量不能超过车的容量，否则不能完成
    //问题是如何遍历？
    //一个想法是O(n^2)的复杂度，判断当前区间于之后的所有区间重合区域是否超载
    //这个方法默认后面的区间不相交但都跟当前区域相交的情况就不对了
    //我们把区间分成两个点，也就是一个区间变为上车和下车两个动作，用两个数组存储它们，然后按时间点遍历

    sort(trips.begin(),trips.end(),[](vector<int>& a, vector<int>& b)
    {
        if(a[1] == b[1])
        {
            return a[2] < b[2];
        }
        return a[1] < b[1];
    });

    for(auto& a : trips)
    {
        printf("%d %d\n",a[1],a[2]);
    }

    for(int i=0;i<trips.size();++i)
    {
        int c = trips[i][0];
        for(int j=i+1;j<trips.size();++j)
        {
            if(trips[j][1] >= trips[i][1] && trips[j][1] < trips[i][2])
            {
                c += trips[j][0];
            }
        }

        printf("c:%d\n",c);
        if(c > capacity)
        {
            return false;
        }
    }

    return true;
     
}

bool carPooling2(vector<vector<int>>& trips, int capacity) {
    //思路：我们把区间分成两个点，也就是一个区间变为上车和下车两个动作，用两个数组存储它们，然后按时间点遍历
    //优化，我们用一个数组存储，上车是正数，下车时负数，同一个时间点优先下车

    vector<vector<int>> actions;

    for(int i=0;i<trips.size();++i)
    {
        actions.push_back({trips[i][1],trips[i][0]});
        actions.push_back({trips[i][2],-trips[i][0]});
    }

    sort(actions.begin(),actions.end(),[](vector<int>& a,vector<int>& b)
    {
        if(a[0] == b[0])
        {
            return a[1] < b[1];
        }
        return a[0] < b[0];
    });

    // for(auto a : actions)
    // {
    //     printf("%d %d\n",a[0],a[1]);
    // }

    int count = 0;
    for(int i=0;i<actions.size();++i)
    {
        count += actions[i][1];
        if(count > capacity)
        {
            return false;
        }
    }

    return true;
}

//网上的另一种思路还是把上车下车分开，对上车点排序，然后用优先队列存储下车点，到达新上车点前把下车点都找出执行

int main()
{
    vector<vector<int>> trips = {{2,1,5},{3,3,7}};
    int capacity = 4; //false

    printf(carPooling2(trips,capacity) ? "true\n" : "false\n");

    trips = {{2,1,5},{3,3,7}}; capacity = 5; //true;
    printf(carPooling2(trips,capacity) ? "true\n" : "false\n");

    trips = {{2,1,5},{3,5,7}}; capacity = 3; //true
    printf(carPooling2(trips,capacity) ? "true\n" : "false\n");

    trips = {{3,2,7},{3,7,9},{8,3,9}}; capacity = 11;//true;
    printf(carPooling2(trips,capacity) ? "true\n" : "false\n");

    trips = {{9,3,4},{9,1,7},{4,2,4},{7,4,5}}; capacity = 23;
    printf(carPooling2(trips,capacity) ? "true\n" : "false\n");
    return 0;
}