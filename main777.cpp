//leetcode 777. 在LR字符串中交换相邻字符

#include <cstdio>
#include <string>

using namespace std;

bool canTransform(string start, string end) {
    
    //思路：暴力破解，回溯，肯定超时
    //可以发现X是可以到达下一个X之前的任意位置，而L和R可以往一侧移动的步数和那一侧与它们相连的X的数量的一样的
    //同时，任意一个L和R是不可能通过移动而逆转它们的顺讯的，即如果L在R的左边，则不可能把R移到L的右边，例如LXXXXXR，
    //所以可以知道，在i位置，如果start和end不同，且都不为X的话，它们是不能通过操作达成一致的
    //同样，如果end[i]不为X，start[i]是X的话，则在start中在i之后查找end[i],如果遇到不为'X'的字符，也不可能
    //同理，end[i]为X，start[i]不为X，则只需j>i,start[j]=X，即可
    //注意，只能使用XR替换RX，LX替换XL，也就是R向又移动，L向左移动


// RXXLRXRXL ->
// XRXLRXRXL ->
// XRLXRXRXL ->
// XRLXXRRXL ->
// XRLXXRRLX

    for(int i=0;i<end.size();++i)
    {
        if(start[i] != end[i])
        {
            if(start[i] != 'X' && end[i] != 'X')
            {
                printf("1\n");
                return false;
            }
            else if(end[i] == 'X')
            {
                if(start[i] == 'L')
                {
                    return false;
                }
                int j;
                for(j=i+1;j<start.size();++j)
                {
                    if(start[j] == 'X')
                    {
                        for(int k=j;k>i;--k)
                        {
                            start[k] = start[k-1];
                        }

                        start[i] = 'X';
                        break;
                    }
                }

                printf("start:%s\n",start.c_str());
                if(j == start.size())
                {
                    printf("2\n");
                    return false;
                }
            }
            else
            {
                if(end[i] == 'R')
                {
                    return false;
                }
                int j;
                for(j=i+1;j<start.size();++j)
                {
                    if(start[j] == end[i])
                    {
                        swap(start[i],start[j]);
                        break;
                    }
                    else
                    {
                        if(start[j] != 'X')
                        {
                            printf("3 i:%d start[j]:%c\n",i,start[j]);
                            return false;
                        }
                    }
                }

                if(j == start.size())
                {
                    printf("4\n");
                    return false;
                }
            }
        }
    }

    return true;
}

bool canTransform2(string start,string end)
{
    //这个算法简洁，记录R和L的数量，当start碰到R时+1，当end喷到R时减1，其实可以理解为start的R向右移动，end的R向左移动
    //这里的关键就是遇到R时，要把L的计数重置为0，因为之前L和R是不可能交换顺序的，也就是说如果遇到R了，之前的L还没匹配，这个时候不可能把这个L移动到R的左边解决L的匹配问题。所以我们重置为0，表示这些L不存在
    //重置为0后，也就意味着有一些L和R消失了，这样，start和end中的L和R最后的计数就不能相等，只要不相等，则是false
    int r = 0, l = 0;
    for (int i = 0; i < start.size(); i++) {
        if (start[i] == 'R')
            { r++; l = 0;}
        else if(start[i] == 'L')
            { l--; r = 0;}
        if (end[i] == 'R')
            { r--; l = 0;}
        else if (end[i] == 'L')
            { l++; r = 0;}
        if (r < 0 || l < 0)
            return false;
    }
    return l==0&&r==0;
}

int main()
{
    printf(canTransform("RXXLRXRXL","XRLXXRRLX") ? "true\n" : "false\n");
    printf(canTransform("RXX","XXR") ? "true\n" : "false\n");
    printf(canTransform("RXX","LXR") ? "true\n" : "false\n");
    printf(canTransform("XXRXXLXXXX","XXXXRXXLXX") ? "true\n" : "false\n");
    return 0;
}