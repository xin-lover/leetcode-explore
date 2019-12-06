//1003. 检查替换后的词是否有效

#include <cstdio>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isValid(string S) {
    //思路：只需要把遇到的abc剔除，判断剩余的字符串即可
    vector<char> v1(S.begin(),S.end());
    vector<char> v2;
    int sz = -1;
    while(v1.size() != sz)
    {
        sz = v1.size();
        for(int i=0;i<v1.size();++i)
        {
            if(i+2 < v1.size() && v1[i]=='a' && v1[i+1]=='b'&&v1[i+2]=='c')
            {
                i+=2;
            }
            else
            {
                v2.push_back(v1[i]);
            }
            
        }

        swap(v1,v2);
        v2.clear();
    }

    
    return v1.size() == 0;
}

bool isValid2(string S) {
    //优化上面的思路，不使用vector
    //使用栈存储预期的下一个字符，如果不符合预期则返回false

    stack<char> sk;
    char expected = 'a';
    for(int i=0;i<S.size();++i)
    {
        if(S[i] != expected)
        {
            if(expected == 'a')//也就是完成了’abc‘之后才能退栈，也就是上一个字符和下一个字符才能连接
            {
                if(!sk.empty() && S[i] == sk.top())
                {
                    sk.pop();
                    expected = S[i]+1;
                }
                else
                {
                    return false;
                }
            }
            else
            {               
                sk.push(expected);
                expected = 'a';
                --i;
            }
        }
        else
        {
            ++expected;
        }
        if(expected > 'c')
        {
            expected = 'a';
        }
    }

    return sk.empty() && expected == 'a';
}

bool isValid3(string S) {
    //使用栈更简化的写法,遇到c的时候前面必须是abc，
    stack<char> stk;
    for (char c : S) {
        if (c != 'c') {
            stk.push(c);
        } else {
            if (stk.empty() || stk.top() != 'b') return false;
            stk.pop();
            if (stk.empty() || stk.top() != 'a') return false;
            stk.pop();
        }
    }
    return stk.empty();
}

int main()
{
    printf(isValid3("abcab") ? "true\n" : "false\n");//false
    printf(isValid3("aaabcbcbc") ? "true\n" : "false\n");//true;
    printf(isValid3("aabbcc") ? "true\n" : "false\n");//false;
    printf(isValid3("aabcbc") ? "true\n" : "false\n");//true;
    printf(isValid3("abcabcababcc") ? "true\n" : "false\n");//true;
    printf(isValid3("abccba") ? "true\n" : "false\n");//false;
    printf(isValid3("cababc") ? "true\n" : "false\n");//false;
    return 0;
}