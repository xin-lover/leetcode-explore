//335. 路径交叉

#include <cstdio>
#include <vector>

using namespace std;

bool isSelfCrossing(vector<int>& x) {
    //思路：如何判断相交？这里直线简单，只有横竖，但横线也可能共线，如果存所有的直线判断
    //那么复杂度O(n^2)
    //由简到繁，先考虑3条边，在考虑4条边，5条边。。。。。最后发现只有3种相交模型

    for(int i=3;i<x.size();++i)
    {
        if(x[i]>=x[i-2] && x[i-1]<=x[i-3])
        {
            return true;
        }
        else if(i >= 4 && x[i-1] == x[i-3] && x[i] >= x[i-2]-x[i-4])
        {
            return true;
        }
        else if(i >= 5 && x[i-2] > x[i-4] && x[i] >= x[i-2] - x[i-4] && x[i-1] >= x[i-3] - x[i-5] && x[i-3]>x[i-1])
        {
            return true;
        }
    }

    return false;    
}

// class Solution {
// public:
//     bool isSelfCrossing(vector<int>& x) {
//         int x_size=x.size();
//         for (int i=3;i<x_size;++i)
//         {
//             if (i>=3 && x.at(i-1)<=x.at(i-3) && x.at(i)>=x.at(i-2))
//                 return true;
//             if (i>=4 && x.at(i-3)==x.at(i-1) && x.at(i)+x.at(i-4)>=x.at(i-2))
//                 return true;
//             if (i>=5 && x.at(i)+x.at(i-4)>=x.at(i-2) && x.at(i-1)+x.at(i-5)>=x.at(i-3) && x.at(i-2)>x.at(i-4) && x.at(i-3)>x.at(i-1))
//                 return true;
//         }
//         return false;
//     }
// };

int main()
{
    vector<int> nums = {2,1,1,2}; //true

    nums = {1,2,3,4};   //false

    // nums = {1,1,2,1,1}; //true

    // nums = {3,3,3,2,1,1};   //false;

    printf(isSelfCrossing(nums) ? "true\n" : "false\n");
    return 0;
}