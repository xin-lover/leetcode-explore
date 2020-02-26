//1111. 有效括号的嵌套深度

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

vector<int> maxDepthAfterSplit(string seq) {
    //思路：只有嵌套的括号会影响我们分组，其它的情况我们都可以分到a组
    //因为要使深度最小，那么对于嵌套的情况平分即可
    //策略：遇到（时，深度+1，同时分组，遇到）深度-1，同时分组，但它需要与对应的（一个组
    //所以，使用一个栈来存储分组记录

    stack<int> sk;
    vector<int> flags(seq.size(),0);

    for(int i=0;i<seq.size();++i)
    {
        if(seq[i] == '(')
        {
            flags[i] = (sk.size() &1);
            sk.push(flags[i]);  //优化，可以不实用栈，直接记录深度即可，奇数深度一组，偶数一组即可
        }   
        else
        {
            flags[i] = sk.top();
            sk.pop();
        }
        
    }

    return flags;
}

int main()
{
    string seq = "(()())";
    seq = "()(())()";
    vector<int> res = maxDepthAfterSplit(seq);
    for (auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
    
}