#include <cstdio>
#include <string>
#include <stack>

using namespace std;

void lengthLongestPath(const string& input,int index,stack<int>& sk,int& res)
{
    if(index >= input.size())
    {
        return;
    }

    int i=index;
    int t = 0;
    for(;i<input.size() && input[i] == '\t';++i)
    {
        ++t;
    }

    while(sk.size() > t)
    {
        sk.pop();
    }

    int len = 0;
    bool isFile = false;
    for(;i<input.size() && input[i] != '\n';++i)
    {
        if(input[i] == '.')
        {
            isFile = true;
        }
        ++len;
    }

    int lastLen = sk.empty() ? 0 : sk.top();
    if(isFile)
    {
        res = max(res,lastLen + len);
    }
    else
    {
        sk.push(lastLen + len + 1);
    }
    
    lengthLongestPath(input,i+1,sk,res);
}

int lengthLongestPath(string input) {
    
    //思路：\n\t表示的是结构
    //\n表示目录开始，\t表示占位符,也可以理解为目录级数一个\t即二级目录，两个三级
    //对每一个目录递归查找最长路径
    
    stack<int> sk;
    int res = 0;
    lengthLongestPath(input,0,sk,res);
    return res;

}

int main()
{
    printf("res:%d\n",lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"));
    printf("res:%d\n",lengthLongestPath(""));
    return 0;
}