#include <cstdio>
#include <vector>

using namespace std;



void lexicalOrder(int n,int start,vector<int>& res)
{
    if(start <= n)
    {
        res.push_back(start);
        lexicalOrder(n,start * 10,res);
        if(start / 10 == (start+1) / 10)
        {
            lexicalOrder(n,start+1,res);
        }
        
    }
}

vector<int> lexicalOrder(int n)
{
    vector<int> res;
    lexicalOrder(n,1,res);
    return res;
}

int main()
{
    auto res = lexicalOrder(103);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}