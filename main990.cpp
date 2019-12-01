//990. 等式方程的可满足性

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int find(vector<int>& dsj,int val)
{
    while(dsj[val] != -1)
    {
        val = dsj[val];
    }

    return val;
}

bool equationsPossible(vector<string>& equations) {
    //思路：因为只有两种等号，所以就相当于分组，但这里可能有多组
    //所以问题主要是未分组的时候如何分组，不相交集不能处理！=的情况
    //一个解决方案是先处理==的情况，再处理！=的情况



    vector<int> dsj(26,-1);
    for(int i=0;i<equations.size();++i)
    {
        if(equations[i][1] == '=')
        {
            int left = equations[i][0]-'a';
            int right = equations[i][3]-'a';
            int lg = find(dsj,left);
            int rg = find(dsj,right);
            // //分配了但不同组则矛盾了
            // if(lg != rg) 
            // {
            //     if((dsj[lg] !=  && rg != right))
            //     {
            //         printf("get:%s\n",equations[i].c_str());
            //         return false;
            //     }
            //     dsj[lg] = rg;
            // }
            if(lg != rg)
            {
                dsj[lg] = rg;
            }

        }
    }

    for(int i=0;i<equations.size();++i)
    {
        if(equations[i][1] == '!')
        {
            int left = equations[i][0]-'a';
            int right = equations[i][3]-'a';
            int lg = find(dsj,left);
            int rg = find(dsj,right);
            //分配了但同组则矛盾了
            if(lg == rg)
            {
                return false;
            }
        }       
    }

    return true;
}

int main()
{
    vector<string> ex = {"a==b","b!=a"};    //false
    ex = {"b==a","a==b"};
    // ex = {"a==b","b==c","a==c"}; //true
    ex = {"a==b","b!=c","c==a"}; //false;
    // ex = {"f==a","a==b","f!=e","a==c","b==e","c==f"};//false
    // ex = {"b==h","j==g","b==h","c!=a","h!=f","b==d","j==h","e!=h","j!=c","j==d","b==a"};
    printf(equationsPossible(ex) ? "true\n" : "false\n");
    return 0;
}

//b,h,d
//j,g
