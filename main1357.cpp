//1357. 每隔 n 个顾客打折

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

class Cashier {
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
        //思路：就一个简单计数
        n_ = n;
        discount_ = discount;
        for(int i=0;i<products.size();++i)
        {
            productPrices_.insert({products[i],prices[i]});
        }
        visitors_ = 0;
    }
    
    double getBill(vector<int> product, vector<int> amount) {
        visitors_++;
        double sum = 0;
        for(int i=0;i<product.size();++i)
        {
            sum += productPrices_[product[i]] * amount[i];
        }
        // printf("sum:%f\n",sum);
        if(visitors_ == n_)
        {
            sum *= (1.0 - discount_/100.0);
            visitors_ = 0;
        }

        return sum;
    }

    int n_;
    int discount_;
    unordered_map<int,int> productPrices_;

    int visitors_;
};

int main()
{
    int n=3,discount=50;
    vector<int> products = {1,2,3,4,5,6,7},prices = {100,200,300,400,300,200,100};

    Cashier cashier(3,50,products,prices);
    printf("%f\n",cashier.getBill({1,2},{1,2}));                        // 返回 500.0, 账单金额为 = 1 * 100 + 2 * 200 = 500.
    printf("%f\n",cashier.getBill({3,7},{10,10}));                      // 返回 4000.0
    printf("%f\n",cashier.getBill({1,2,3,4,5,6,7},{1,1,1,1,1,1,1}));    // 返回 800.0 ，账单原本为 1600.0 ，但由于该顾客是第三位顾客，他将得到 50% 的折扣，所以实际金额为 1600 - 1600 * (50 / 100) = 800 。
    printf("%f\n",cashier.getBill({4},{10}));                           // 返回 4000.0
    printf("%f\n",cashier.getBill({7,3},{10,10}));                      // 返回 4000.0
    printf("%f\n",cashier.getBill({7,5,3,1,6,4,2},{10,10,10,9,9,9,7})); // 返回 7350.0 ，账单原本为 14700.0 ，但由于系统计数再次达到三，该顾客将得到 50% 的折扣，实际金额为 7350.0 。
    printf("%f\n",cashier.getBill({2,3,5},{5,3,2}));                    // 返回 2500.0
    return 0;
}