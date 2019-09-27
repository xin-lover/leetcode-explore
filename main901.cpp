//leetcode 901. 股票价格跨度

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

class StockSpanner {
public:
    StockSpanner() {
        //思路：如果按照题意直接求解，很简单，性能的话一般，因为每次都要向前遍历
        //考虑其一天的跨度，如果今天的比它大，则前一天跨度内的都符合要求，然后迭代前进即可，
        //所问题就是要额外存储跨度
    }
    
    int next(int price) {
        int sp = 1;
       if(!stocks_.empty())
       {
           int index = stocks_.size()-1;
           while(index >= 0 && price >= stocks_[index])
           {
               index -=spans_[index];
           }

            sp = stocks_.size() - index;
       }
       
        stocks_.push_back(price);
        spans_.push_back(sp);
        return sp;
    }

    vector<int> stocks_;
    vector<int> spans_;
};

class StockSpanner2 {
public:
    StockSpanner2() {
        //思路：可以类比波峰波谷，使用递减栈来求解
    }
    
    int next(int price) {
       int res = 0;
       while(!sk_.empty() && price >= stocks_[sk_.top()])
       {
           sk_.pop();
       }

       stocks_.push_back(price);
       if(sk_.empty())
       {
           res = stocks_.size();
       }
       else
       {
           res  = stocks_.size() - sk_.top()-1;
       }

       sk_.push(stocks_.size()-1);
       return res;
    }

    stack<int> sk_;
    vector<int> stocks_;
};

class StockSpanner3 {
public:
    StockSpanner3() {
        //思路：单调栈另一种写法,本质没有变化
    }
    
    int next(int price) {
       int w = 1;
       while(!prices_.empty() && prices_.top() <= price)
       {
           prices_.pop();
           w += weights_.top();
           weights_.pop();
       }

       prices_.push(price);
       weights_.push(w);
       return w;
    }

    stack<int> prices_;
    stack<int> weights_;
};

int main()
{
    StockSpanner3 obj;
    // printf("%d\n",obj.next(100));
    // printf("%d\n",obj.next(80));
    // printf("%d\n",obj.next(60));
    // printf("%d\n",obj.next(70));
    // printf("%d\n",obj.next(60));
    // printf("%d\n",obj.next(75));
    // printf("%d\n",obj.next(80));

    
    printf("%d\n",obj.next(31));
    printf("%d\n",obj.next(41));
    printf("%d\n",obj.next(48));
    printf("%d\n",obj.next(59));
    printf("%d\n",obj.next(79));
    return 0;
}