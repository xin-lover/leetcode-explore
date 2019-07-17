//leetcode 638 大礼包

#include <cstdio>
#include <vector>

using namespace std;

void backtrace(vector<int>& price, vector<vector<int>>& special,vector<int>& needs,vector<int>& specialFlags, int cur, int& cost)
{
    for(int a : specialFlags)
    {
        printf("%d ",a);
    }
    printf("\n");
    for(int i=0;i<needs.size();++i)
    {
        int c = 0;
        for(int j=0;j<special.size();++j)
        {
            c += special[j][i] * specialFlags[j];
        }

        if(c > needs[i])
        {
            return;
        }
    }

    int tc = 0;
    for(int i=0;i<specialFlags.size();++i)
    {
        tc += (*(special[i].end() - 1)) * specialFlags[i];
    }
    for(int i=0;i<needs.size();++i)
    {
        int r = needs[i];
        for(int j=0;j<special.size();++j)
        {
            r -= special[j][i] * specialFlags[j];
        }
        tc += r * price[i];
    }

    if(tc < cost)
    {
        cost = tc;
    }

    printf("cost:%d\n",cost);

    specialFlags[cur]+=1;
    backtrace(price,special,needs,specialFlags,cur,cost); 
    specialFlags[cur]-=1;

    for(int i=cur+1;i<specialFlags.size();++i)
    {
        specialFlags[i] += 1;
        backtrace(price,special,needs,specialFlags,i,cost);
        specialFlags[i] -=1;
    }
}

int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
    
    //思路：用暴力破解可以，但随着礼包数和礼品种类增加，肯定超时

    vector<int> specialFlags(special.size(),0);
    int res = INT_MAX;
    backtrace(price,special,needs,specialFlags,0,res);
    return res;

}

int main()
{
    vector<int> price ={2,5};
    vector<vector<int>> special = {{3,0,5},{1,2,10}};
    vector<int> needs = {3,2};

    printf("res:%d\n",shoppingOffers(price,special,needs));
    return 0;
}