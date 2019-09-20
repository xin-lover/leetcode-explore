//leetcode 900. RLE 迭代器

#include <cstdio>
#include <vector>

using namespace std;

class RLEIterator {
public:
    RLEIterator(vector<int>& A) {
        //思路：一个思路就是构建时把序列还原出来，然后使用一个标志位即可
        //但这种方式占用的内存是跟着原始序列走的
        //另一种就是换算了

        arr_ = A;
        curIndex_ = 0;
        remain_ = arr_[curIndex_];
    }
    
    int next(int n) {
        while(curIndex_ < arr_.size() && n > 0)
        {
            if(n <= remain_)
            {
                remain_ -= n;
                return arr_[curIndex_+1];
            }
            else
            {
                n-= remain_;
                curIndex_ += 2;
                if(curIndex_ >= arr_.size())
                {
                    remain_ = 0;
                    break;
                }
                remain_ = arr_[curIndex_];
            }
        }
        
        return -1;
    }

    vector<int> arr_;
    int curIndex_;
    int remain_;
};

int main()
{
    vector<int> v = {3,8,0,9,2,5};
    RLEIterator* obj = new RLEIterator(v);
    printf("%d\n",obj->next(2));
    printf("%d\n",obj->next(1));
    printf("%d\n",obj->next(1));
    printf("%d\n",obj->next(2));
    return 0;
}