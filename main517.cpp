//517. 超级洗衣机

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int findMinMoves(vector<int>& machines) {
    //思路：先看总量是否能平均，不能则直接放回false
    //整体的移动是多的往少的移，唯一的限制就是一次移一件，空的不能移
    //考虑相邻的移动情况，从第3个洗衣机移动一件衣服到第1个洗衣机，第一次需要两步，后面就只需要一步，可以理解为履带传输
    //这里还要考虑，比如中间洗衣机中衣服数量刚好，那这个步数怎么弄？想想火车过隧道，总长度是隧道长度加火车长度
    //不考虑相邻的话，每个位置加1减1，结果就看衣服数最多的洗衣机了
    //我们考虑当前位置的衣服数为p,如果p<avg,假设从下个位置移动衣服过来，那么需要avg-p次操作，到下一个位置同理
    //所以我们的操作就是每次都向平均数移动,多了就往下个位置移，少了就从下个位置移过来,但要处理如果从同一个位置向左右两侧移，那么操作数要累加
    //也就是处理并行性的问题

    int n = machines.size();
    int sum = 0;
    for(int i=0;i<machines.size();++i)
    {
        sum += machines[i];
    }

    if(sum % n != 0)
    {
        return -1;
    }

    int avg = sum / n;
    int res = 0;
    int lastOp = 0;
    for(int i=0;i<n-1;++i)
    {
        //非并行操作
        if(machines[i] > avg && lastOp < 0)
        {
            res = max(res,machines[i]- avg - lastOp); 
        }
        else
        {
            res = max(res, abs(machines[i] - avg));
        }
        machines[i+1] += machines[i] - avg;
        lastOp = machines[i] - avg;
    }

    return res;
}

int findMinMoves2(vector<int>& machines) {
    //
    int n = machines.size();
    int sum = 0;
    for(int i=0;i<machines.size();++i)
    {
        sum += machines[i];
    }

    if(sum % n != 0)
    {
        return -1;
    }

    int avg = sum / n;
    int res = 0;
    int pre_sum = 0;
    for(int i=0;i<n;++i)
    {
        //非并行操作
        int t = machines[i] - avg;
        pre_sum += t;
        res = max(res,abs(pre_sum));
        res = max(res,t);
    }

    return res;
}

int main()
{
    vector<int> machines = {1,0,5}; //3
    // machines = {0,3,0};//2
    // machines = {0,2,0}; //-1
    machines = {4,9,8,4,0}; //6
    printf("%d\n",findMinMoves2(machines));
    return 0;
}