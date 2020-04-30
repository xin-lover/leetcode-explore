//1286. 字母组合迭代器

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength) {
        //思路：characters长度最大15，还能接受，一个简单的想法就是吧所有的结果
        //计算出来，这样next和hasnext就变为常数时间

        string cur(combinationLength,'\0');
        backtrace(characters,0,cur,0,words_);
        index_ = 0;

        for(auto a : words_)
        {
            printf("%s\n",a.c_str());
        }
    }
    
    string next() {
        ++index_;
        return words_[index_-1];
    }
    
    bool hasNext() {
        return index_ < words_.size();
    }

    void backtrace(const string& characters,int start,string& cur,int index,vector<string>& res)
    {
        if(index >= cur.size())
        {
            res.push_back(cur);
            return;
        }

        for(int i=start;i<characters.size();++i)
        {
            cur[index] = characters[i];
            backtrace(characters,i+1,cur,index+1,res);
        }
    }

    vector<string> words_;
    int index_;
};

// 通过上面这个例子，我们可以得到一般性的组合生成方法：
// 假设字符串的长度为 l，组合的长度为 k，第一个组合即为字符串中的前 k 个字母；
// 在调用函数 next() 时，我们将当前的组合作为答案返回，并开始寻找下一个组合：
// 我们从组合中的第 k 个位置开始看起，如果当前位置的字母可以增大，则将其增大一次；如果当前位置的字母已经到达最大值，则向前寻找，直到找到可以增大的位置，将其增大一次。如果没有找到，则说明当前已经是最大的组合，我们添加一个标记。对于组合中的第 i 个位置，它的最大值是字符串中的第 l - k + i 个字母；
// 记找到可以增大的字母位置为 i。我们将组合中的第 i + 1 到第 k 个位置的字母减少为满足要求的最小值。具体地，第 i + 1 个位置的字母为第 i 个位置的字母在字符串中的下一个字母，第 i + 2 个位置的字母为第 i + 1 个位置的字母在字符串中的下一个字母，以此类推。


class CombinationIterator2 {
public:
    CombinationIterator2(string characters, int combinationLength) {
        
        characters_ = characters;
        cur_flags_.resize(combinationLength);
        index_ = cur_flags_.size()-1;
        next_ = index_ + 1;
        for(int i=0;i<combinationLength;++i)
        {
            cur_flags_[i] = i;
        }
    }
    
    string next() {

        int k = cur_flags_.size();
        string tmp(k,'\0');
        for(int i=0;i<tmp.size();++i)
        {
            tmp[i] = characters_[cur_flags_[i]];
        }

        int len = characters_.size();
        //位置i的最大值为l-k+i位置的值
        if(next_ >= len)
        {
            --index_;
            while(index_ > -1 && cur_flags_[index_] >= len-k+index_)
            {
                --index_;
            }
            
            if(index_ > -1)
            {
                ++cur_flags_[index_];
                for(int i=index_+1;i<cur_flags_.size();++i)
                {
                    cur_flags_[i] = cur_flags_[i-1]+1;
                }
                index_ = cur_flags_.size()-1;
                next_ = cur_flags_[index_]+1;
            }

        }
        else
        {
            //增大一位
            cur_flags_[index_] = next_++;
        }

        return tmp;
    }
    
    bool hasNext() {
        return index_ >= 0;
    }

    string characters_;
    vector<int> cur_flags_;
    int index_;
    int next_;
};

int main()
{
    CombinationIterator2 iterator("abc",2);
    printf("%s\n",iterator.next().c_str()); // 返回 "ab"
    printf(iterator.hasNext() ? "true\n" : "false\n"); // 返回 true
    printf("%s\n",iterator.next().c_str());  // 返回 "ac"
    printf(iterator.hasNext() ? "true\n" : "false\n"); // 返回 true
    printf("%s\n",iterator.next().c_str()); // 返回 "bc"
    printf(iterator.hasNext() ? "true\n" : "false\n"); // 返回 false

    return 0;
}