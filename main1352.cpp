//1352. 最后 K 个数的乘积

#include <cstdio>
#include <vector>

using namespace std;

class ProductOfNumbers {
public:
    ProductOfNumbers() {
        //思路：前缀和的思路,但0如何处理？
        //num>=0,可以把0当成-1处理
        //还有一个问题是如何处理多个0？也就是最后k个0中有偶数个0，
        //改变策略：记录最后一个0的位置，同时0不记录前缀积中，那么有两种情况
        //1.如果最后k个数中有0，那么返回0
        //2.否则利用前缀积求出

        //溢出，积太大了
        //我们不需要记录所有的积，在遇到0时，积都为0
        //使用一个数组记录前缀积，在遇到0后清空，如果前缀积的这个数组长度小于k直接返回0，其它的还是同样的方式

        products_.push_back(1);
        // lastZeroPos = -2;
    }
    
    void add(int num) {
        // if(num == 0)
        // {
        //     lastZeroPos = products_.size()-1;
        //     products_.push_back(products_.back());  
        // }
        // else
        // {
        //     products_.push_back(products_.back() * num);  
        // }

        if(num == 0)
        {
            products_.clear();  //可以优化，不动态分配内存
            products_.push_back(1);
        }
        else
        {
            products_.push_back(products_.back()*num);
        }
        
    }
    
    int getProduct(int k) {

        // if(lastZeroPos >= (int)(products_.size()-k-1))
        // {
        //     return 0;
        // }
        // int pre = products_[products_.size()-k-1];
        // int res = products_.back() / pre;   
        // return res;

        if(products_.size() < k+1)
        {
            return 0;
        }

        return products_.back() / products_[products_.size()-k-1];
    }

    vector<int> products_;
    int lastZeroPos;
};

//这里有个思路很有意思：乘法的结果是移位，假设乘以2，因为结果不大于整形，也就是说最多移31次
//使用一个数组记录0的个数的前缀和，便于获取最后的k个数中是否有0，
//对于没有0的情况，直接乘获取结果，下面的算法用额外的一个数组存储非0，非1的位置，顶多就是避免了乘1，不知道性能怎么样
// class ProductOfNumbers {
// public:
//     vector<int>vec,zero,pre;
//     int n;
//     ProductOfNumbers() {
//         vec.clear();
//         zero.clear();
//         pre.clear();
//         n=0;
//     }
    
//     void add(int num) {
//         n++;
//         vec.push_back(num);
//         pre.push_back(-1);
//         if (n>1){
//             if (vec[n-2]!=1 && vec[n-2]!=0) pre[n-1]=n-2;
//             else pre[n-1]=pre[n-2];
//         }
//         zero.push_back(num==0?1:0);
//         if (n>1) zero[n-1]+=zero[n-2];
//     }
    
//     int getProduct(int k) {
//         int tot=zero[n-1];
//         if (n-k>=1) tot-=zero[n-1-k];
//         if (tot>0) return 0;
//         int ans=1;
//         for (int i=n-1;i>=n-k;){
//             ans*=vec[i];
//             i=pre[i];
//         }
//         return ans;
//     }
// };

int main()
{
    ProductOfNumbers productOfNumbers;
    productOfNumbers.add(3);        // [3]
    productOfNumbers.add(0);        // [3,0]
    productOfNumbers.add(2);        // [3,0,2]
    productOfNumbers.add(5);        // [3,0,2,5]
    productOfNumbers.add(4);        // [3,0,2,5,4]
    printf("%d\n",productOfNumbers.getProduct(2)); // 返回 20 。最后 2 个数字的乘积是 5 * 4 = 20
    printf("%d\n",productOfNumbers.getProduct(3)); // 返回 40 。最后 3 个数字的乘积是 2 * 5 * 4 = 40
    printf("%d\n",productOfNumbers.getProduct(4)); // 返回  0 。最后 4 个数字的乘积是 0 * 2 * 5 * 4 = 0
    productOfNumbers.add(8);        // [3,0,0,5,4,8]
    printf("%d\n",productOfNumbers.getProduct(2)); // 返回 32 。最后 2 个数字的乘积是 4 * 8 = 32 


    // productOfNumbers.add(3);        // [3]
    // productOfNumbers.add(0);        // [3,0]
    // productOfNumbers.add(0);        // [3,0,0]
    // productOfNumbers.add(8);        // [3,0,0,8]
    // productOfNumbers.add(3);        // [3,0,0,8,3]
    // printf("%d\n",productOfNumbers.getProduct(1)); // 返回 3 
    // productOfNumbers.add(7);        // [3,0,0,8,3,7]
    // printf("%d\n",productOfNumbers.getProduct(5)); // 返回 0
    // productOfNumbers.add(3);        // [3,0,0,8,3,7,3]

    // productOfNumbers.add(1);
    // printf("%d\n",productOfNumbers.getProduct(1));
    return 0;
}