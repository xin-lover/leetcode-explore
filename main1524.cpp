//1524. 和为奇数的子数组数目

#include <cstdio>
#include <vector>

using namespace std;

int numOfSubarrays(vector<int>& arr) {
    //思路：总共n*(n+2)/2个子数组,暴力破解性能不行
    //考虑3个数,{1,1,0},{1,0,1}的情况是不同的，前者是3个奇数和，后者是4个
    //考虑dp{i,j}中的奇数和数量为a,偶数和数量为b
    //现在新加一个数，根据该数的奇偶性能求出新的奇数和和偶数和
    
    static const int kLimit = 1e9 + 7;
    int even = 0;
    int odd = 0;

    long long res = 0;
    for(int i=0;i<arr.size();++i)
    {
        if(arr[i] & 1)
        {
            int t = even;
            even = odd;
            odd = t + 1;
            res += odd;
            res %= kLimit;
        }
        else
        {
            int t = even;
            even = even + 1;
            odd = odd;
            res += odd;
            res %= kLimit;
        }
        
    }

    return res;
}

int main()
{
    vector<int> arr = {1,3,5}; //4
    arr = {1,2,3,4,5,6,7};  //16
    arr = {2,4,6};  //0
    printf("%d\n",numOfSubarrays(arr));

    return 0;
}