//282. 给表达式添加运算符

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

// unordered_map<int,vector<string>> backtrace(string& num,int index)
// {
//     if(index >= num.size())
//     {
//         return{};
//     }

//     int d = num[index] - '0';
//     if(index == num.size()-1)
//     {
//         return {d,{num.substr(num.size()-1,1)}};
//     }

//     auto res = backtrace(num,index+1);

// }

vector<string> addOperators(string num, int target) {
    //思路：总共n-1个操作符，操作符乘号是高优先级，特殊处理
    //假设现在处理到num[i],如果num[i]后接+，-，那么只需要计算num{i+1,n-1}的值即可
    //如果后面接*，那么就变成了num[i]*num[i+1]后面再接上后续结果的值
    //可以考虑动归了，dp[i]表示num索引0到索引i的结果
    //dp[i] = {dp[i-1]+num[i],dp[i-1]-num[i],dp[i-j]+{num[i-j+1]*num[i-j+2]....},dp[i-j]+{num[i-1+1]*num[i-j+1]...}
    //还需要考虑组合数字间的乘法
    //所以dp改成dp[i] = {dp[j] {+,-} multiply(j+1,i)}

    int n = num.size();
    if(n == 0)
    {
        return{};
    }
    vector<unordered_map<int,vector<string>>> dp(n);
    for(int i=0;i<n;++i)
    {
        printf("i:%d------------\n",i);
        long long t = 1;
        string ts;
        long long t2 = 0;
        string ts2;
        long long radix = 1;
        for(int j=i;j>0;--j)
        {
            t *= (num[j]-'0');
            if(t < INT_MAX)
            {
                ts = num[j] + ((j==i) ? "" : "*" + ts);
                for(auto a : dp[j-1])
                {
                    for(auto b : a.second)
                    {
                        dp[i][a.first+t].push_back(b.empty() ? ts : b + "+" + ts);  
                        dp[i][a.first-t].push_back(b.empty() ? ts : b + "-" + ts);
                    }
                }
            }

            //问题，没有考虑组合数字的乘法
            //组合数字
            if(t2 < INT_MAX) 
            {
                t2 += (num[j]-'0')*radix; //这里要防止溢出
                radix *= 10;
                if(j<i && num[j] != '0') //j<i 避免重复   避免前置0
                {
                    printf("t2:%d\n",t2);
                    ts2 = num.substr(j,i-j+1);
                    for(auto a : dp[j-1])
                    {
                        for(auto b : a.second)
                        {
                            dp[i][a.first+t2].push_back(b.empty() ? ts2 : b+"+"+ts2);
                            dp[i][a.first-t2].push_back(b.empty() ? ts2 : b+"-"+ts2);
                        }
                    }
                }

            }
        }

        if(t < INT_MAX)
        {
            t *= (num[0]-'0');
            ts = num[0] + (ts.empty() ? "" : "*" + ts);
            dp[i][t].push_back(ts);
        }

        if(radix > 1)
        {
            t2 += (num[0]-'0') * radix;
            printf("t2:%d\n",t2);
            dp[i][t2].push_back(num.substr(0,i+1));
        }

    }
    
    return dp[n-1][target];
}

class Expression
{
public:
    string preExp;
    int leftRes;
    int lastOp;
    int lastVal;
    string lastValExp;

    Expression(const string& pre,int res,int op,int val,const string& valexp)
    :preExp(pre),
    leftRes(res),
    lastOp(op),
    lastVal(val),
    lastValExp(valexp)
    {

    }
};


vector<string> addOperators2(string num, int target) {
    //思路：复杂性在于数字可以组合为新的数字，所以先需要确定数字，在插入操作符
    //使用动归，dp[i]表示索引i位置时的所有表达式
    //那么对于num[i+1]，可以选择独立成一个数字，也可以加入之前的数字，
    //不管那种我们都需要知道之前最后一步的操作，可以用操作数和符合表达
    
    if(num.empty())
    {
        return {};
    }

    int n = num.size();
    vector<vector<Expression>> dp(n);
    dp[0].emplace_back("",0,0,num[0]-'0',num.substr(0,1));

    for(int i=1;i<n;++i)
    {
        //最后一个数字长度
        for(int j=1;j<11 && j<i+1;++j)
        {
            if(j>1 && num[i-j+1] == '0')
            {
                continue;
            }

            string ts = num.substr(i-j+1,j);
            long long t = stoll(ts);
            if(t > INT_MAX)
            {
                break;
            }

            for(auto& a : dp[i-j])
            {
                if(a.lastOp == 0)
                {
                    string pre = (a.preExp.empty() ? a.lastValExp : a.preExp + "+" + a.lastValExp);
                    dp[i].emplace_back(pre,a.leftRes + a.lastVal,0,t,ts);
                    dp[i].emplace_back(pre,a.leftRes + a.lastVal,1,t,ts);
                    dp[i].emplace_back(a.preExp,a.leftRes,a.lastOp,a.lastVal * t,a.lastValExp + "*" + ts);
                }
                else if(a.lastOp == 1)
                {
                    string pre = (a.preExp.empty() ? a.lastValExp : a.preExp + "-" + a.lastValExp);
                    dp[i].emplace_back(pre,a.leftRes - a.lastVal,0,t,ts);
                    dp[i].emplace_back(pre,a.leftRes - a.lastVal,1,t,ts);
                    dp[i].emplace_back(a.preExp,a.leftRes,a.lastOp,a.lastVal * t,a.lastValExp + "*" + ts);
                }
                // else
                // {
                //     dp[i].emplace_back(a.preExp,a.leftRes,a.lastOp,a.lastVal*t,a.lastValExp + "*" + ts);
                // }
                
            }
        }

        if(i < 10 && num[0] != '0')
        {
            long long t = stoll(num.substr(0,i+1));
            if(t<=INT_MAX)
            {
                dp[i].emplace_back("",0,0,t,num.substr(0,i+1));
            }
        }
    }

    vector<string> res;
    for(auto a : dp[n-1])
    {
        // printf("%s %d %d %d %s\n",a.preExp.c_str(),a.leftRes,a.lastOp,a.lastVal,a.lastValExp.c_str());
        if(a.lastOp==0 && a.leftRes + a.lastVal == target)
        {
            res.emplace_back(a.preExp.empty() ? a.lastValExp :  a.preExp + "+" + a.lastValExp);
        }

        if(a.lastOp ==1 && a.leftRes - a.lastVal == target)
        {
            res.emplace_back(a.preExp.empty() ? a.lastValExp : a.preExp + "-" + a.lastValExp);
        }

    }

    return res;
}

int main()
{
    string num = "123";
    int target = 6; //["1+2+3", "1*2*3"] 

    // num = "232", target = 8;    //["2*3+2", "2+3*2"]

    // num = "105", target = 5;    //["1*0+5","10-5"]

    // num = "00", target = 0; //["0+0", "0-0", "0*0"]

    // num = "021",target = 21;

    // num = "3456237490", target = 9191;  //[]
    // num = "1213",target=1213;

    // num = "123456789",target=45;

    num = "2147483647",target= 2147483647;

    for(auto a : addOperators2(num,target))
    {
        printf("%s\n",a.c_str());
    }

    return 0;
}