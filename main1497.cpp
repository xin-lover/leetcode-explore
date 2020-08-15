//1497. 检查数组对是否可以被 k 整除

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

bool canArrange(vector<int>& arr, int k) {
    //思路：这个有点像是两数之和，但因为是整除k，所以符合要求的和有很多
    //那么看看这两个数，i与i+k*m，它们两个在数组中是等价的。不会影响结果
    //所以，方案就是线对数组元素求余处理，然后在用两数之和的思路

    unordered_map<int,int> um;
    for(auto num : arr)
    {
        num %= k;
        num = num < 0 ? num + k : num;  //可优化为num = (num%k+k)%k;
        int r = num == 0 ? 0 : k - num;
        if(um.find(r) != um.end() && um[r] > 0)
        {
            um[r]--;
        }
        else
        {
            um[num]++;
        }
    }

    for(auto it : um)
    {
        if(it.second > 0)
        {
            return false;
        }
    }

    return true;
}

//用数组代替哈希。。。
bool canArrange2(vector<int>& arr, int k) {
    vector<int> mod(k);
    for (int num: arr) {
        ++mod[(num % k + k) % k];
    }
    for (int i = 1; i + i < k; ++i) {
        if (mod[i] != mod[k - i]) {
            return false;
        }
    }
    return mod[0] % 2 == 0;
}

int main()
{
    vector<int> arr = {1,2,3,4,5,10,6,7,8,9}; //true
    int k = 5;
    arr = {1,2,3,4,5,6}, k = 7; //true
    arr = {1,2,3,4,5,6}, k = 10;    //false
    arr={-1,1,-2,2,-3,3,-4,4},k=3;  //true

    printf("%d\n",-1%3);
    printf(canArrange(arr,k) ? "true\n" : "false\n"); //true

    return 0;
}