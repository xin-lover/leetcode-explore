//1138. 字母板上的路径

#include <cstdio>
#include <string>

using namespace std;

//board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"].
//abcde
//fghij
//klmno
//pqrst
//uvwxy
//z

//leet
//DDR!UURRR!!DDD!

//code
//RR!DDRR!UUL!R!
string alphabetBoardPath(string target) {
    //思路：根据题意，我们也没有其它的选择，就是一个字母一个字母的去爬
    //起点是a，每个字母的下标可以很容易确定，根据下标确定行动路线即可
    //需要特殊对待的也就是z了，在z上，我们只有一种操作，就是U
    //而如果要到达z，则需要先回到第一列,所以采用优先左右移动的策略

    int cur_x=0,cur_y=0;
    string res;
    for(int i=0;i<target.size();++i)
    {
        char c = target[i];
        int p = c - 'a';
        int x = p / 5;
        int y = p % 5;

        //当前在z上，要去往其它地方
        if(cur_x == 5  && cur_y == 0 && c != 'z')
        {
            res.append(1,'U');
            cur_x = 4;
            cur_y = 0;
        }

        char lr = y >= cur_y ? 'R' : 'L';
        res.append(abs(y-cur_y),lr);
        char ud = x >= cur_x ? 'D' : 'U';
        res.append(abs(x-cur_x),ud);
 
        res.append(1,'!');
        cur_x = x;
        cur_y = y;
    }

    return res;
}

int main()
{
    printf("%s\n",alphabetBoardPath("leet").c_str()); //DDR!UURRR!!DDD!
    printf("%s\n",alphabetBoardPath("code").c_str()); //RR!DDRR!UUL!R!
    printf("%s\n",alphabetBoardPath("z").c_str()); //RR!DDRR!UUL!R!
    printf("%s\n",alphabetBoardPath("zb").c_str()); //RR!DDRR!UUL!R!
    return 0;
}