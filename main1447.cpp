//1447. 最简分数

#include <cstdio>
#include <vector>
#include <set>
#include <string>

using namespace std;

int gcd(int x,int y)
{
    if(x == 0 || y == 0)
    {
        return 0;
    }
    while(true)
    {
        if(x>y)
        {
            x-=y;
        }
        else if(x<y)
        {
            y-=x;
        }
        else
        {
            return x;
        }
    }

    return 1;
}

vector<string> simplifiedFractions(int n) {
    //思路：主要在于化简和去重
    //去重使用set和map都可以
    //化简在于找最大公约数

    set<string> tmp;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<i;++j)
        {
            int g = gcd(i,j);
            tmp.insert(to_string(j/g) + "/" + to_string(i/g));
        }
    }

    return vector<string>(tmp.begin(),tmp.end());
}

//如果按照分母和分子都从小到大遍历的话, 每次最先遇到的都是最简形式, 因为假如不是的话一定有一个更小的分母分子组合满足条件, 已经在之前被遍历到了
//这个省略了求最大公约数的过程
vector<string> simplifiedFractions2(int n) {
    vector<string> res;
    set<double> tmp;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<i;++j)
        {
            double d = (double)j / i;
            if(tmp.find(d) == tmp.end())
            {
                res.push_back(to_string(j) + "/" + to_string(i));
                tmp.insert(d);
            }
            
        }
    }

    return res;
}



int main()
{
    for(auto a : simplifiedFractions(4))
    {
        printf("%s ",a.c_str());
    }
    printf("\n");

    return 0;
}