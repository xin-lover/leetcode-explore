//135. 分发糖果

#include <cstdio>
#include <vector>

using namespace std;

int candy(vector<int>& ratings) {
    //思路：我们按照从左到右遍历，每个孩子至少一个糖果
    //那么到第i个孩子时，考虑相邻的孩子
    //1.如果他的评分比前一个高，那么+1；
    //2.如果他的评分比前一个低，那么+0，但前面的孩子糖果必须比第i个多，如果是个递减序列，那么我们需要往前都递增
    //所以整个问题可以变为找递增和递减序列，而要确定如何分，必须让递增配对递减
    //也就是先确定评分最低的那个小孩，分1个，然后按左右递增分
    //所以如何找到谷底小孩。。。左右都比他评分高的小孩就是谷底小孩
    //同样评分的孩子不一定分到同样的糖果。。。。

    int n = ratings.size();
    vector<int> candies(n,0);

    for(int i=0;i<n;++i)
    {
        if(i > 1 && ratings[i] == ratings[i-1] && i+1<n && ratings[i] == ratings[i+1])
        {
            continue;
        }
        if((i==0 || ratings[i]<=ratings[i-1]) && (i==n-1 || ratings[i] <= ratings[i+1]))
        {
            candies[i] = 1;
            int left=i-1;
            while(left >=0 && ratings[left]>=ratings[left+1])
            {
                int d = ratings[left] == ratings[left+1] ? 0 : 1;
                candies[left] = max(candies[left],candies[left+1]+d);
                --left;
            }

            int right =i+1;
            while(right<n && ratings[right] >= ratings[right-1])
            {
                int d = ratings[right] == ratings[right-1] ? 0 : 1;
                candies[right] = max(candies[right],candies[right-1]+d);
                ++right;
            }
        }
    }

    int sum = 0;
    for(auto a : candies)
    {
        printf("%d ",a);
        sum += a;
    }
    printf("\n");

    return sum;
}

int candy2(vector<int>& ratings) {
    //思路：{1,3,2,2,1}; //7
    //从这个例子中，看出同样的评分不一定分得同样的糖果
    //既然这样，不考虑谷底了，只考虑递减递增；
    //记录递减递增序列区间

    int n = ratings.size();
    vector<int> candies(n,1);

    for(int i=0;i<n-1;++i)
    {
        if(ratings[i]<ratings[i+1])
        {
            //递增
            int j=i;
            while(j<n-1 && ratings[j] < ratings[j+1])
            {
                ++j;
            }

            candies[i] = 1;
            for(int k=i+1;k<=j;++k)
            {
                candies[k] = max(candies[k],candies[k-1]+1);
            }

            i = j-1;
        }
        else if(ratings[i]>ratings[i+1])
        {
            //递减
            int j=i;
            while(j<n-1 && ratings[j] > ratings[j+1])
            {
                ++j;
            }

            candies[j] = 1;
            for(int k=j-1;k>=i;--k)
            {
                candies[k] = max(candies[k],candies[k+1]+1);
            }

            i = j-1;
        }
    }

    int sum = 0;
    for(auto a : candies)
    {
        printf("%d ",a);
        sum += a;
    }
    printf("\n");

    return sum;
}

//思路更简单
// class Solution {
//     public：
//    int candy(int[] ratings) {
//         int sum = 0;
//         int[] left2right = new int[ratings.length];
//         int[] right2left = new int[ratings.length];
//         Arrays.fill(left2right, 1);
//         Arrays.fill(right2left, 1);
//         for (int i = 1; i < ratings.length; i++) {
//             if (ratings[i] > ratings[i - 1]) {
//                 left2right[i] = left2right[i - 1] + 1;
//             }
//         }
//         for (int i = ratings.length - 2; i >= 0; i--) {
//             if (ratings[i] > ratings[i + 1]) {
//                 right2left[i] = right2left[i + 1] + 1;
//             }
//         }
//         for (int i = 0; i < ratings.length; i++) {
//             sum += Math.max(left2right[i], right2left[i]);
//         }
//         return sum;
//     }
// }

//常数空间
int count(int n) {
    return (n * (n + 1)) / 2;
}
int candy(vector<int> ratings) {
    if (ratings.size() <= 1) {
        return ratings.size();
    }
    int candies = 0;
    int up = 0;
    int down = 0;
    int old_slope = 0;
    for (int i = 1; i < ratings.size(); i++) {
        int new_slope = (ratings[i] > ratings[i - 1]) ? 1 : (ratings[i] < ratings[i - 1] ? -1 : 0);
        if ((old_slope > 0 && new_slope == 0) || (old_slope < 0 && new_slope >= 0)) {
            candies += count(up) + count(down) + max(up, down);
            up = 0;
            down = 0;
        }
        if (new_slope > 0)
            up++;
        if (new_slope < 0)
            down++;
        if (new_slope == 0)
            candies++;

        old_slope = new_slope;
    }
    candies += count(up) + count(down) + max(up, down) + 1;
    return candies;
}

int main()
{
    vector<int> ratings = {1,0,2}; //5
    ratings = {1,2,2}; //4
    // ratings = {1,3,2,2,1}; //7

    printf("%d\n",candy2(ratings));
    return 0;

}