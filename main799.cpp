//leetcode 799. 香槟塔

#include <cstdio>

using namespace std;

double calcChampagneIn(int poured, int query_row, int query_glass)
{
    if(query_row == 0)
    {
        return poured;
    }

    int lastRowCount = query_row;    //上一层的杯子数
    double left = query_glass-1 < 0 ? 0 : calcChampagneIn(poured,query_row-1,query_glass-1)-1;
    left = left <=0 ? 0 : left;
    double right = query_glass >= lastRowCount ? 0 : calcChampagneIn(poured,query_row-1,query_glass)-1;
    right = right <=0 ? 0 : right;
    return (left+right)/2.0;
}

double calcChampagneIn(int query_row, int query_glass,double * dp,int col_count)
{
    if(query_row == 0)
    {
        return dp[0];
    }

    int left_index = query_row*(col_count) + query_glass-1;
    int right_index = left_index+1;
    double left = 0.0;
    if(query_glass-1 >=0)
    {
        if(dp[left_index] < 0.0)
        {
            double r = calcChampagneIn(query_row-1,query_glass-1,dp,col_count)-1;
            dp[left_index] = r < 0.0 ? 0.0 : r;
        }
        left = dp[left_index];
        
    }

    int lastRowCount = query_row;    //上一层的杯子数
    double right = 0.0;
    if(query_glass < lastRowCount)
    {
        if(dp[right_index] < 0.0)
        {
            double r = calcChampagneIn(query_row-1,query_glass,dp,col_count)-1;
            dp[right_index] = r < 0.0 ? 0.0 : r;
        }

        right = dp[right_index];
    }

    return (left+right)/2.0;
}


double champagneTower(int poured, int query_row, int query_glass) {
    //思路：下标从0开始，第n层有n+1个杯子，一瓶香槟倒满一杯
    //假设倒入最上面那一个杯子的流速是1，则可以发现满了后溢出则分流为两个0.5的支流，同理，到第二层3个杯子，第一个的支流是0.25，而第二个杯子有两个支流，是0.25+0.25，第三个是0.25
    //也就是说外侧杯子的流入量是按1/2递减的，没满的话不会溢出，所以第1个杯子（从0开始数）需要它上面的那个杯子满了之后才会有两个流流入
    //那我们开始找规律，第1层的两个杯子同时满，第2层的中间的先满，而旁边的只有1/2，所以如果旁边的两个都满了，则中间的其实流入了2杯，有一杯流入了下一层
    //很明显，一个杯子上面最多两个杯子，假设流入两个杯子的量为a和b，则流入到这个杯子的量为(a-1)/2+(b-1)/2，如果a小于1，表示杯子没满，不会流入下面的杯子
    //这样我们就可以使用递归的方式求解

    //超时，应该和斐波那契数列求值的问题一样，使用动归解决
    // double count_in = calcChampagneIn(poured,query_row,query_glass);
    // return count_in >1.0 ? 1.0 : count_in;

    //动归算法，直观的是使用二维数组，空间复杂度高一点，可以使用vector，每一层长度不一样，这样会节省一半空间
    //但复杂度还是o(n2)
    int len = (query_row+1)*(query_row+1);
    double dp[len];
    for(int i=0;i<len;++i)
    {
         dp[i] = -1.0;
    }

    dp[0] = poured;
    double count_in = calcChampagneIn(query_row,query_glass,dp,query_row+1);
    return count_in >1.0 ? 1.0 : count_in;

    //另一种思路是计算每一层的所有杯子的结果，这样只需要一维数组就可以，这样空间复杂度降下来，
    //但所有的杯子都要计算，所以算是时间换空间
}

int main()
{
    // printf("%f\n",champagneTower(1,1,1));
    // printf("%f\n",champagneTower(2,1,1));
    // printf("%f\n",champagneTower(2,0,0));
    // printf("%f\n",champagneTower(4,1,0));
    // printf("%f\n",champagneTower(4,2,0));
    // printf("%f\n",champagneTower(6,2,0));
    // printf("%f\n",champagneTower(6,3,2));
    printf("%f\n",champagneTower(6,3,0));
    printf("%f\n",champagneTower(6,3,1));
    printf("%f\n",champagneTower(6,3,2));
    return 0;
}