#include <cstdio>
#include <vector>

using namespace std;

class NumArray {
public:
    //思路：使用线段树
    void buildSegTree(vector<int>& values,vector<int>& nums,int pos,int left,int right)
    {
        if(left == right)
        {
            values[pos] = nums[left];
            return;
        }
        
        int mid = left + (right - left) / 2;
        buildSegTree(values,nums,2 * pos + 1,left,mid);
        buildSegTree(values,nums,2 * pos + 2,mid+1,right);
        values[pos] = values[2 * pos + 1] + values[2 * pos + 2];
    }
    
    void updateSegTree(vector<int>& values,int pos, int left,int right,int index,int newval)
    {
        if(left == right)
        {
            values[pos] = newval;
            return;
        }
        
        int mid = left + (right - left) / 2;
        if(index <= mid && index >= left)
        {
            updateSegTree(values,2*pos+1,left,mid,index,newval);
        }
        else
        {
            updateSegTree(values,2*pos+2,mid+1,right,index,newval);
        }
        
        values[pos] = values[2*pos+1] + values[2*pos+2];
    }
    
    int sumSegRange(vector<int>& values,int pos,int left,int right,int qleft,int qright)
    {
        if(qleft > right || left > qright)
        {
            return 0;
        }
        
        if(left >= qleft && right <= qright)
        {
            return values[pos];
        }
        
        int mid = left + (right - left) / 2;
        return sumSegRange(values,2*pos + 1,left,mid,qleft,qright) 
            + sumSegRange(values,2*pos + 2,mid+1,right,qleft,qright);
        
    }
    
    NumArray(vector<int> nums) {
        //思路：简单的累加，估计不符合这题的本意
        //使用动归，实践略长 
        // if(!nums.empty())
        // {
        //     sum_ = vector<int>(nums.size() + 1,0);
        //     for(int i=0;i<nums.size();++i)
        //     {
        //         sum_[i+1] = sum_[i] + nums[i]; 
        //     }
        // }
        count_ = nums.size();
        if(count_ > 0){
            values_ = vector<int>(2*nums.size(),0);
        
            buildSegTree(values_,nums,0,0,nums.size()-1);
        }

    }
    
    void update(int i, int val) {
        
        // if(sum_.size()-1 > i)
        // {
        //     int offset = val - (sum_[i+1] - sum_[i]);
        //     for(int j=i+1;j<sum_.size();++j)
        //     {
        //         sum_[j] += offset;
        //     }
        // }
        if(count_>0 && i> 0 && i < count_)
            updateSegTree(values_,0,0,count_-1,i,val);
    }
    
    int sumRange(int i, int j) {
//         if(sum_.size()-1 > j && i >= 0)
//         {
//             return sum_[j+1] - sum_[i];
//         }
        
        // return 0;
        return i<0 || j < i ? 0 : sumSegRange(values_,0,0,count_-1,i,j);
    }
    
private:
    // vector<int> sum_;
    vector<int> values_;
    int count_;
};

int main()
{
    NumArray na({-1});
    printf("%d\n",na.sumRange(0,0));
    na.update(0,1);
    printf("%d\n",na.sumRange(0,0));
    // printf("%d\n",na.sumRange(6,7));

    // na.update(1,-82);
    // na.update(3,-72);
    // printf("%d\n",na.sumRange(3,7));
    // printf("%d\n",na.sumRange(1,8));

    // na.update(5,13);
    // na.update(4,-67);
    return 0;
}