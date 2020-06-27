//1390. 四因数

#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int sumFourDivisors(vector<int>& nums) {
    //思路：枚举求解因数 

    int res = 0;
    for(auto a : nums)
    {
        int sum = 0;
        int count = 0;
        int i=1;
        for(;i*i<a;++i)
        {
            if(a % i == 0)
            {
                count+=2;
                sum += (i + a / i);
            }
        }

        if(i*i ==a)
        {
            ++count;
            sum += i;
        }

        if(count == 4)
        {
            res += sum;
        }
    }

    return res;
}

//预处理
// class Solution {
// public:
//     int sumFourDivisors(vector<int>& nums) {
//         // C 是数组 nums 元素的上限，C3 是 C 的立方根
//         int C = 100000, C3 = 46;
        
//         vector<int> isprime(C + 1, 1);
//         vector<int> primes;

//         // 埃拉托斯特尼筛法
//         for (int i = 2; i <= C; ++i) {
//             if (isprime[i]) {
//                 primes.push_back(i);
//             }
//             for (int j = i + i; j <= C; j += i) {
//                 isprime[j] = 0;
//             }
//         }

//         // 欧拉筛法
//         /*
//         for (int i = 2; i <= C; ++i) {
//             if (isprime[i]) {
//                 primes.push_back(i);
//             }
//             for (int prime: primes) {
//                 if (i * prime > C) {
//                     break;
//                 }
//                 isprime[i * prime] = 0;
//                 if (i % prime == 0) {
//                     break;
//                 }
//             }
//         }
//         */
        
//         // 通过质数表构造出所有的四因数
//         unordered_map<int, int> factor4;
//         for (int prime: primes) {
//             if (prime <= C3) {
//                 factor4[prime * prime * prime] = 1 + prime + prime * prime + prime * prime * prime;
//             }
//         }
//         for (int i = 0; i < primes.size(); ++i) {
//             for (int j = i + 1; j < primes.size(); ++j) {
//                 if (primes[i] <= C / primes[j]) {
//                     factor4[primes[i] * primes[j]] = 1 + primes[i] + primes[j] + primes[i] * primes[j];
//                 }
//                 else {
//                     break;
//                 }
//             }
//         }

//         int ans = 0;
//         for (int num: nums) {
//             if (factor4.count(num)) {
//                 ans += factor4[num];
//             }
//         }
//         return ans;
//     }
// };

int main()
{
    vector<int> nums = {21,4,7};

    printf("%d\n",sumFourDivisors(nums));
    return 0;
}