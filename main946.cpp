//leetcode 946. 验证栈序列

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    //思路：1,2,3,4,5  4,5,3,2,1  4,3,5,1,2
    //push的顺序确定了，所以我们可以一步一步push，如果栈顶是popped当前位置的数字，则执行pop，否则push

    stack<int> sk;

    int j=0;
    for(int i=0;i<pushed.size();++i)
    {
        while(!sk.empty() && sk.top() == popped[j])
        {
            sk.pop();
            ++j;
        }
        sk.push(pushed[i]);
    }

    while(!sk.empty() && sk.top() == popped[j])
    {
        sk.pop();
        ++j;
    }

    return sk.empty();
}

int main()
{
    vector<int> pushed = {1,2,3,4,5};
    vector<int> popped = {4,5,3,2,1};
    popped = {4,3,5,1,2};

    pushed = {2,1,0};
    popped = {1,2,0};
    printf(validateStackSequences(pushed,popped) ? "true\n" : "false\n");
    return 0;
}