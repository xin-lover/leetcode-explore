//1472. 设计浏览器历史记录

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class BrowserHistory {
public:
    BrowserHistory(string homepage) {
        //思路：这个的问题的思路很简单，问题主要在于visit清空前进记录
        //如果要高效的处理，应该要避免内存的动态分配，所以我们使用标记
        //不直接释放vector的空间


        //就是模拟栈。。。。。

        records_.push_back(homepage);
        curIndex_ = 0;
        lastIndex_ = 0;
    }
    
    void visit(string url) {
        // printf("%d %d\n",curIndex_,lastIndex_);
        if(curIndex_+1 >= records_.size())
        {
            records_.push_back(url);
        }
        else
        {
            records_[curIndex_+1] = url;
        }

        curIndex_ +=1;
        lastIndex_ = curIndex_;
    }
    
    string back(int steps) {        
        // printf("cur:%d\n",curIndex_);
        curIndex_ -= steps;
        curIndex_ = curIndex_ < 0 ? 0 : curIndex_;
        return records_[curIndex_];
    }
    
    string forward(int steps) {
        // printf("f cur:%d\n",curIndex_);
        curIndex_ += steps;
        curIndex_ = curIndex_ > lastIndex_ ? lastIndex_ : curIndex_;
        return records_[curIndex_];
    }

    vector<string> records_;
    int lastIndex_;
    int curIndex_;
};

int main()
{
    BrowserHistory browser("leetcode.com");
    browser.visit("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");

    printf("%s\n",browser.back(1).c_str());
    printf("%s\n",browser.back(1).c_str());
    printf("%s\n",browser.forward(1).c_str());
    browser.visit("linkedin.com");
    printf("%s\n",browser.forward(2).c_str());
    printf("%s\n",browser.back(2).c_str());
    printf("%s\n",browser.back(7).c_str());

    return 0;
}