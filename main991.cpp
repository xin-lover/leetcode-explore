//991. 坏了的计算器

#include <cstdio>
#include <vector>

using namespace std;

int brokenCalc(int X, int Y) {
    //思路：如果x比y小，只能减
    //使用回溯法，也就是每一步都只有两个选择，那么步数取决于X、Y的相对大小，
    //再思考奇偶性，如果Y为奇数，那么只能通过减1得到
    //再思考减1乘2和乘2减1的区别，(x-1)*2和x*2-1，两者差1
    //再思考x=3，y=10，3->6->5->10
    //x=3,y=8，3->2->4->8,3->6->5->4->8
    //x=3,y=7,3->8->7
    //假设f(x,y)表示x到y的最小操作结果，那么如果y为奇数，我们比较一下f(x,y+1)和f(x,y+3)的结果
    //其实就是比较f(x,(y+1)/2)和f(x,(y+3)/2),令z=(y+1)/2,则变为f(x,z)和f(x,z+1)
    //也就是如果f(x,z+1)+2 < f(x,z)的时候，我们才可能选择+3，而这不可能，因为z+1到z只需要一步，
    //也就是说如果f(x,z+1)较小，那么对于z完全可以先到z+1再减1到达z，那这样f(x,z)=f(x,z+1)+1
    //所以对于y为奇数，我们就直接求f(x,y+1)即可
    //对于偶数，我们的选择就是除2了，减1的效率肯定不如除2，如此递归，直到y=(x-m)*2或y=x*2-m的情况出现,也就是y<x*2
    //这个条件还可以再进一步，也就是y>x的时候，都是如上操作

    printf("%d %d\n",X,Y);
    if(X >= Y)
    {
        return X - Y;
    }

    if(Y < X * 2)
    {
        return min(X - Y/2,X*2-Y)+1;//这里可以再深入一步，X > Y时， return X-Y,也就是去掉这一步
    }

    if(Y&1)
    {
        return brokenCalc(X,Y+1)+1;
    }

    return brokenCalc(X,Y/2)+1;
}

int brokenCalc2(int X, int Y) {
    //贪心，简便的写法
    int ans = 0;
    while(Y > X)
    {
        ans++;
        if(Y & 1)
        {
            ++Y;
        }
        else
        {
            Y /= 2;
        }
        
    }

    return ans + X-Y;
}

int main()
{
    printf("%d\n",brokenCalc(2,3));//2
    printf("%d\n",brokenCalc(5,8));//2
    printf("%d\n",brokenCalc(3,10));//3
    printf("%d\n",brokenCalc(1024,1));//1023
    printf("%d\n",brokenCalc(1,1));//1023
    printf("%d\n",brokenCalc2(1,1000000000));//1023
    return 0;
}