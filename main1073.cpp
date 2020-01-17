//1073. 负二进制数相加

#include <cstdio>
#include <vector>

using namespace std;

vector<int> addNegabinary(vector<int> arr1, vector<int> arr2) {
    //思路：直接让二进制相加会怎么样？
    //比如01和01相加，得到10，也就是-2，但实际上应该是1+1=2
    //所以还是使用之前的方式，奇数位置n上的1，2^n = (-2)^(n+1)+(-2)^n获得
    //对于相应位置上的进位我们可以用高两位的11代替，也就是说:2*(-2)^n = (-2)^(n+2)+(-2)^(n+1)
    //注意12这样的情况，它表述的是0

    if(arr1.size() < arr2.size())
    {
        swap(arr1,arr2);
    }
    int n = arr1.size();
    int m = arr2.size();
    vector<int> tmp(n+2,0);
    for(int i=0;i<n;++i)
    {
        int t =tmp[i]+ arr1[n-1-i] + (i >= m ? 0 : arr2[m-1-i]);
        while(t >= 2)
        {
            if(tmp[i+1]>0)
            {
                tmp[i+1]-=1;
            }
            else
            {
                tmp[i+1]+=1;
                tmp[i+2]+=1;
            }
            
            t-=2;
        }

        tmp[i]=t;
    }

    vector<int> res;
    for(int i=tmp.size()-1;i>=0;--i)
    {
        if(tmp[i]!=0)
        {
            for(int j=i;j>=0;--j)
            {
                res.push_back(tmp[j]);
            }
            break;
        }
    }
    
    if(res.empty())
    {
        res.push_back(0);
    }
    return res;
    
}

int main()
{
    vector<int> arr1 = {1,1,1,1,1}, arr2 = {1,0,1}; //[1,0,0,0,0]
    arr1={1,1};
    arr2={1};//0
    auto res = addNegabinary(arr1,arr2);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}