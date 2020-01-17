//1053. 交换一次的先前排列

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

vector<int> prevPermOpt1(vector<int>& A) {
    //思路：根据题意，如果i<j,那么A[i]是要大于A[j]的，
    //所以，如果A本来就是从小到大排列的话，那么没有这样的数
    //对于A[i],我们要找什么样数了？
    //首先i应该尽量大，其次A[i]也尽量大，A[j]尽量靠近A[i]
    //所以我们从右向左遍历，使用栈记录递减的序列，直到A[i]大于栈顶的值，然后出栈找最接近A[i]的值

    stack<int> sk;
    for(int i=A.size()-1;i>=0;--i)
    {
        int t=i;
        while(!sk.empty() && A[i] > A[sk.top()])
        {
            t = sk.top();
            sk.pop();
        }

        if(A[t] < A[i])
        {
            //处理相同元素的情况
            while(t>1 && A[t] == A[t-1])
            {
                --t;
            }
            swap(A[i],A[t]);
            break;
        }
        
        sk.push(i);
    }

    return A;
}

vector<int> prevPermOpt2(vector<int>& A) {
    //思路：优化上面的方案，我们发现是要用递减栈找一个最大的但小于A[i]的数
    //其实可以用二分，然后我们不需要栈，因为第一个非递减的情况就能得出最后的答案

    for(int i=A.size()-2;i>=0;--i)
    {
        if(A[i] > A[i+1])
        {
            //找第一个大于等于A[i]的数
            int left = i+1,right=A.size()-1;
            while(left < right)
            {
                int mid = left + (right-left) / 2;
                if(A[mid] < A[i])
                {
                    left = mid+1;
                }
                else
                {
                    right = mid;
                }
            }

            if(A[right] >= A[i])
            {
                --right;
            }
            while(right>1 && A[right]==A[right-1])
            {
                --right;
            }   

            swap(A[i],A[right]);
            break;
        }
    }

    return A;
}

int main()
{
    vector<int> A = {3,2,1}; //3,1,2
    A = {1,1,5}; //1,1,5
    // A = {1,9,4,6,7};//1,7,4,6,9
    // A = {3,1,1,3};//1,3,1,3
    vector<int> res = prevPermOpt2(A);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    
    return 0;
}