#include<cstdio>
#include<vector>
#include<set>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        
        //思路：每次确定一个数，直到k=2计算结果
        
        
        return combinationSum3(k,1,n);
    }
    
    vector<vector<int>> combinationSum3(int k,int start,int n)
    {
        vector<vector<int>> res;
        if(k == 2)
        {
            set<int> st;
            for(int i=start;i<10;++i)
            {
                if(st.find(i) != st.end())
                {
                    res.push_back({n-i,i});
                }
                else
                {
                    st.insert(n-i);
                }
            }
        }
        else
        {
            for(int i=start;i<10;++i)
            {
                printf("start:%d\n",start+1);
                auto st = combinationSum3(k-1,i+1,n-i);
                for(auto v : st)
                {
                    v.insert(v.begin(),i);
                    res.push_back(v);
                }
            }   
        }
        
        return res;
    }
};

int main()
{
    Solution s;
    auto res = s.combinationSum3(3,7);
    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%d ",b);
        }
        printf("\n");
    }
    return 0;
}