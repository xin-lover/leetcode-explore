//679. 24 点游戏

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

bool judgePoint24(vector<double>& nums) {

    const double exp = 0.000001;

    if(nums.size() == 1)
    {
        return abs(nums[0] - 24.0) < exp;
    }

    for(int i=0;i<nums.size();++i)
    {
        for(int j=0;j<nums.size();++j)
        {
            if(j == i)
            {
                continue;
            }

            vector<double> tvec;
            for(int k=0;k<nums.size();++k)
            {
                if(k!=i && k!=j)
                {
                    tvec.push_back(nums[k]);
                }
            }

            //四种运算
            double r = nums[i] + nums[j];
            tvec.push_back(r);
            if(judgePoint24(tvec))
            {
                return true;
            }
            tvec.pop_back();

            r = nums[i] - nums[j];
            tvec.push_back(r);
            if(judgePoint24(tvec))
            {
                return true;
            }
            tvec.pop_back();
            tvec.push_back(-r);
            if(judgePoint24(tvec))
            {
                return true;
            }
            tvec.pop_back();

            r = nums[i]*nums[j];
            tvec.push_back(r);
            if(judgePoint24(tvec))
            {
                return true;
            }
            tvec.pop_back();

            if(abs(nums[i]-0.0) > exp)
            {
                r = nums[j] / nums[i];
                tvec.push_back(r);
                if(judgePoint24(tvec))
                {
                    return true;
                }
                tvec.pop_back();
            }

            if(abs(nums[j] - 0.0) > exp)
            {
                r = nums[i] / nums[j];
                tvec.push_back(r);
                if(judgePoint24(tvec))
                {
                    return true;
                }
                tvec.pop_back();
            }
        }
    }

    return false;
}

bool judgePoint24(vector<int>& nums) {
    //思路：考虑不管如何组织，当前操作肯定就是两个数字加减乘除，然后得出的结果在加入到剩余的数字中继续


    vector<double> dnum;
    for(int i=0;i<nums.size();++i)
    {
        dnum.push_back(static_cast<double>(nums[i]));
    }

    return judgePoint24(dnum);
}

int main()
{
    vector<int> nums = {4, 1, 8, 7}; //true
    nums = {1, 2, 1, 2}; //false 
    nums = {1,7,4,5}; //true
    printf(judgePoint24(nums) ? "true\n" : "false\n");

    return 0;
}