//440. 字典序的第K小数字

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int findKthNumber(int n, int k)
{
    //思路：字典序，先比较的高位，也就是前缀，前缀相同才比较后面的
    //所以可用前缀和二分的思想来找
    //比如：以1为前缀的两位数有10个，而以10为前缀的三位数字还是有10个，这就有点像树了，10叉树，根为空字符
    //参照深度优先遍历，得到的就是字典序，问题就是确定遍历的深度，这个可以通过n来确定
    //可以借鉴二分的思想，先确定1开始的数字有多少，如果大于k，那么可以确定是1开头的数字
    //然后确定10开始的多少，其次11，顺序递推

    int ascertain = 0; //已确定的
    int count = 0; 
    int radix = 1;   //10进制
    long long pre = 1; //前缀,避免溢出
    int res = 0;
    while(k>1)
    {
        while(pre * radix + radix-1 < n)
        {
            count += radix;
            radix *= 10;
        }

        if(n >= pre*radix)
        {
            count += n-pre*radix + 1;
            if(count == k)
            {
                return n;
            }
        }
        else
        {
            if(count == k)
            {
                return pre * radix / 10 + radix / 10 - 1;
            }
        }
        

        if(count > k) //在内部
        {
            pre *= 10;
            --k; //往前递进一位，比如1，递进一位是10，它刚好排在1后。。。
            count=0;
            radix=1;
        }
        else
        {
            pre+=1;
            k-=count;
            count = 0;
            radix = 1;
        }
        
    }

    return pre;
}

// int findKthNumber2(int n, int k) {
//     //思路：字典序，先比较的高位，也就是前缀，前缀相同才比较后面的
//     //所以可用前缀和二分的思想来找
//     //比如：以1为前缀的两位数有10个，而以10为前缀的三位数字还是有10个，这就有点像树了，10叉树，根为空字符
//     //参照深度优先遍历，得到的就是字典序，问题就是确定遍历的深度，这个可以通过n来确定
//     //用递归的方式求比较简单

//     vector<int> arr;
//     int tmp = n;
//     while(tmp > 0)
//     {
//         arr.push_back(tmp % 10);
//         tmp /= 10;
//     }

//     reverse(arr.begin(),arr.end());

//     //首字符大于tmp的数字长度小于len，对于每一个前缀，总共有10^k种情况，其中k为后面位数
//     //一个一个位置确定
//     int seq = 0;
//     int curIndex = 0;
//     int suffixLen = 0;
//     int firstDigit = 1;
//     int res = 0;
//     while(true)
//     {
//         int tt = pow(10,suffixLen);
//         if(seq + tt < k)
//         {
//             int maxLen = firstDigit < arr[curIndex] ? arr.size() : arr.size()-1;
//             if(suffixLen == maxLen)
//             {
//                 ++firstDigit;
//             }
//             else
//             {
//                 ++suffixLen;
//             }
            
//             seq += tt;
//         }
//         else if(seq + tt > k)   //可以确定当前字符了
//         {
//             res = res * 10 + curIndex; 

//             //新一轮的开始
//             k-= seq;
//             seq = 0;
//             curIndex = 1;
//             digits = 0;
//         }
//         else
//         {
//             res = res * 10 + tt - 1;
//             break;
//         }
//     }

//     return res;
// }

int main()
{
    printf("%d\n",findKthNumber(13,2)); //10
    // printf("%d\n",findKthNumber(10,3)); //2
    // printf("%d\n",findKthNumber(10,2)); //10
    return 0;
}