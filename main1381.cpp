//1381. 设计一个支持增量操作的栈

#include <cstdio>
#include <vector>

using namespace std;

class CustomStack {
public:
    CustomStack(int maxSize) {
        //思路：用数组模拟

        arr_.resize(maxSize);
        cur_= 0;
    }
    
    void push(int x) {
        if(cur_ < arr_.size())
        {
            arr_[cur_++] = x;
        }
    }
    
    int pop() {
        if(cur_ >= 1)
        {
            cur_--;
            return arr_[cur_];
        }

        return -1;
    }
    
    void increment(int k, int val) {
        int len = min(k,cur_);  //优化：使用一个辅助数组记录每次的增量，因为只在pop的时候需要知道值，所以每次出栈的时候吧需要递增的值也传递下去
        for(int i=0;i<len;++i)
        {
            arr_[i] += val;
        }
    }

    vector<int> arr_;
    int cur_;

};

int main()
{
    CustomStack sk(3);
    sk.push(1);
    sk.push(2);
    printf("%d\n",sk.pop());
    sk.push(2);
    sk.push(3);
    sk.push(4);
    sk.increment(5,100);
    sk.increment(2,100);
    printf("%d\n",sk.pop());
    printf("%d\n",sk.pop());
    printf("%d\n",sk.pop());
    return 0;
}