//leetcode 721. 账户合并

#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

// void merge(set<string>& set1,set<string>& set2)
// {
//     for(auto& a : set2)
//     {
//         set.insert(a);
//     }
// }

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    
    //思路：一个人只有一个名称，使用邮箱就可以标识人
    //这里唯一的问题就是多个邮箱都标识同一个人怎么处理，
    //因为有共同邮箱就是同一个人，而且邮箱顺序排列，所以可以使用set，查找可能多点时间，但还能接受
    //还有就是合并的情况，也就是两条信息之前是代表两个人，因为没有公共邮箱，但后来一条信息把这两条信息联系上后，就变成一个人了

    vector<pair<string,set<string>>> um;
    for(auto a : accounts)
    {
        string& name = a[0];
        for(int i=1;i<a.size();++i)
        {
            int mergeId=-1;
            bool have = false;
            for(int j=0;j<um.size();++j)
            {
                if(um[j].second.find(a[i]) != um[j].second.end())
                {
                    //合并
                    if(mergeId==-1)
                    {
                        mergeId=j;
                        printf("mergeId:%d\n",mergeId);
                        for(int k =1;k<a.size();++k )
                        {
                            um[j].second.insert(a[k]);
                        }
                    }
                    else if(j != mergeId)
                    {
                        for(auto b : um[j].second)
                        {
                            um[mergeId].second.insert(b);
                        }

                        um[j].second.clear();
                    }

                    have = true;
                }

            }
            
            if(!have)
            {
                set<string> t(a.begin()+1,a.end());
                um.push_back(pair<string,set<string>>(name,t));
                printf("get:%s\n",name.c_str());
            }
        }
    }

    //挑出数量不为0的set
    vector<vector<string>> res;
    for(auto a : um)
    {
        if(!a.second.empty())
        {
            vector<string> t = {a.first};
            t.insert(t.begin()+1,a.second.begin(),a.second.end());
            res.push_back(t);
        }
    }

    return res;
}

vector<vector<string>> accountsMerge2(vector<vector<string>>& accounts) 
{
    //优化：使用不相交集
    // vector<string> names;
    vector<int> flags(accounts.size(),-1);
    unordered_map<string,int> um;
    for(int k=0;k<accounts.size();++k)
    {
        // string& name = accounts[k][0];
        // names.push_back(name);
        auto& a = accounts[k];
        for(int i=1;i<a.size();++i)
        {
            if(um.find(a[i]) == um.end())
            {
                um[a[i]] = k;
            }
            else
            {
                if(flags[k] != -1)
                { 
                    //找到树根
                    int t = k;
                    while(flags[t]!=-1)
                    {
                        t = flags[t];
                    }

                    int t2 = um[a[i]];
                    while(flags[t2] != -1)
                    {
                        t2 = flags[t2];
                    }

                    if(t != t2)
                    {
                        flags[t] = t2;
                    }
                    
                    printf("t:%d t2:%d\n",t,t2);
                }
                else
                {
                    // printf("%s %d\n",a[i].c_str(),um[a[i]]);
                    // printf("befor;flags[%d]:%d\n",k,flags[k]);
                    if(um[a[i]] != k)
                    {
                        flags[k] = um[a[i]];
                    }
                    
                    // printf("flags[%d]:%d\n",k,flags[k]);
                }
            }
        }
        // printf("flags[%d]:%d\n",k,flags[k]);
    }
    printf("get\n");

    vector<set<string>> tempRes(flags.size());
    for(int i=0;i<flags.size();++i)
    {
        int t = i;
        while(flags[t]!=-1)
        {
            // printf("t:%d\n",t);
            t = flags[t];
        }        

        if(tempRes[t].empty())
        {
            tempRes[t].insert(accounts[i][0]);
        }
        
        for(int j=1;j<accounts[i].size();++j)
        {
            tempRes[t].insert(accounts[i][j]);
        }
    }

    printf("get\n");
    vector<vector<string>> res;
    for(int i=0;i<tempRes.size();++i)
    {
        if(!tempRes[i].empty())
        {
            res.emplace_back(tempRes[i].begin(),tempRes[i].end());
        }
    }

    return res;
}

int main()
{
    vector<vector<string>> accounts = {{"John", "johnsmith@mail.com", "john00@mail.com"}, {"John", "johnnybravo@mail.com"}, {"John", "johnsmith@mail.com", "john_newyork@mail.com"}, {"Mary", "mary@mail.com"}};
    accounts = {{"Alex","Alex5@m.co","Alex4@m.co","Alex0@m.co"},{"Ethan","Ethan3@m.co","Ethan3@m.co","Ethan0@m.co"},{"Kevin","Kevin4@m.co","Kevin2@m.co","Kevin2@m.co"},{"Gabe","Gabe0@m.co","Gabe3@m.co","Gabe2@m.co"},{"Gabe","Gabe3@m.co","Gabe4@m.co","Gabe2@m.co"}};
    vector<vector<string>> res = accountsMerge2(accounts);

    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%s ",b.c_str());
        }
        printf("\n");
    }

    printf("\n");

    return 0;
}