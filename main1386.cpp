//1386. 安排电影院座位

#include <cstdio>
#include <vector>

using namespace std;

int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    //思路：根据题意，很明显，每一行可供4人家庭位置只有3种情况，[2,5],[4,7],[6,9]
    //方案：优先[2,5],[6,9]的情况，因为这样一行可以坐两个家庭

    vector<vector<int>> seats(n,vector<int>(10,0));
    for(auto a : reservedSeats)
    {
        seats[a[0]-1][a[1]-1] = 1;
    }

    int res = 0;
    for(int i=0;i<n;++i)
    {
        int t1 = seats[i][1] + seats[i][2] + seats[i][3] + seats[i][4];
        int t2 = seats[i][5] + seats[i][6] + seats[i][7] + seats[i][8];

        int t3 = seats[i][3] + seats[i][4] + seats[i][5] + seats[i][6];

        if(t1 == 0 && t2 == 0)
        {
            res +=2;
        }
        else if(t1 == 0 || t2 == 0 || t3 == 0)
        {
            ++res;
        }
    }

    return res;
}

int maxNumberOfFamilies2(int n, vector<vector<int>>& reservedSeats) {
    //思路：n会非常大，使用二维数组存状态超出内存空间了，因为最大是10，使用整数位来优化

    //超时
    vector<int> seats(n,0xffff);
    for(auto a : reservedSeats)
    {
        seats[a[0]-1] &= (~(1 << (a[1]-1)));
    }

    int flag1 = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
    int flag2 = (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8);
    int flag3 = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6);
    int flag4 = flag1 | flag2;

    int res = 0;
    for(int i=0;i<n;++i)
    {
        if((seats[i] & flag4) == flag4)
        {
            res +=2;
        }
        else if((seats[i] & flag1) == flag1 ||(seats[i] & flag2) == flag2 ||(seats[i] & flag3) == flag3)
        {
            ++res;
        }
    }

    return res;


    // 官方题解，同样是位运算，唯一的优化就是map只存储可能能坐一个家庭的排,优化的点有两个
    //1.内存减少了；
    //2.需要遍历的次数减少了
    // int left = 0b11110000;
    // int middle = 0b11000011;
    // int right = 0b00001111;

    // unordered_map<int, int> occupied;
    // for (const vector<int>& seat: reservedSeats) {
    //     if (seat[1] >= 2 && seat[1] <= 9) {
    //         occupied[seat[0]] |= (1 << (seat[1] - 2));
    //     }
    // }

    // int ans = (n - occupied.size()) * 2;
    // for (auto& [row, bitmask]: occupied) {
    //     if (((bitmask | left) == left) || ((bitmask | middle) == middle) || ((bitmask | right) == right)) {
    //         ++ans;
    //     }
    // }
    //     return ans;
}

int main()
{
    int n = 3;
    vector<vector<int>> reservedSeats = {{1,2},{1,3},{1,8},{2,6},{3,1},{3,10}};//4

    // n=2;
    // n = 2, reservedSeats = {{2,1},{1,8},{2,6}};//2

    printf("%d\n",maxNumberOfFamilies2(n,reservedSeats));
    return 0;
}