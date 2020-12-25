//466. 统计重复个数
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;


int getMaxRepetitions(string s1, int n1, string s2, int n2) {
    //思路：因为s1重复，s2也重复，所以问题在于如何获取到由s1组成的一段区域
    //这段区域刚好是一个S2的开始，和一个S2的结束，这样就可以直接计算数量而不用重复遍历
    //可能的问题在于找这样的区域时间太长。。。而且还要处理剩余部分
    //这里想法都有个问题就是没有充分利用s1和s2重复这个前提，基于这个重复的特点，其实问题就变为了在s1中找s2
    //但问题在于可能多个s1组合后才能找到s2,这个时候分类：
    //1.s1=其它+k个s2+其它，这种最简单，结果就是(n1*k)/n2
    //2.s1=s2后面一部分+k个s2+s2前面一部分，这样首尾相接可以得到新的s2，这个时候结果是(n1*k+n1-1)/n2
    //注意，这里没有递归，也就是首尾连接最多一个s2，所以问题变成了如何在s1中找s2了


    if(s1.empty() || s2.empty())
    {
        return 0;
    }
    // unordered_map<char,int> s1chars;
    // for(auto a : s1)
    // {
    //     s1chars[a]++;
    // }

    // unordered_map<char,int> s2chars;
    // for(auto a : s2)
    // {
    //     s2chars[a]++;
    // }

    // int mnNeed = 0;
    // for(auto a : s2chars)
    // {
    //     if(s1chars.find(a.first) == s1chars.end() || s1chars[a.first]*n1 < s2chars[a.first]*n2)
    //     {
    //         return 0;
    //     }
    //     // mnNeed = max(mnNeed, (s2chars[a.first]/s1chars[a.first] + (s2chars[a.first] % s1chars[a.first] > 0 ? 1 : 0)));
    // }

    vector<vector<int>> areas;
    for(int i=0;i<s1.size();++i)
    {
        if(s1[i] == s2.back())
        {
            int cc1 = 1;// (i==s1.size()-1 ? 1 : 0);
            int k = i;// (cc1 == 1 ? 0 : i+1);
            for(int k=i,j=s2.size()-1;cc1 < n1;--k)
            {
                if(s1[k] == s2[j])
                {
                    --j;
                    if(j == -1)
                    {
                        areas.push_back({k,i,cc1});
                        printf("push:%d %d %d\n",k,i,cc1);
                        break;
                    }
                }

                if(k == 0)
                {
                    k = s1.size()-1;
                    ++cc1;
                }
            }
        }
    }

    //选择一个区间为起点，直到一圈回来看看多少个区间,注意，这里区间有个特性，肯定是有序的,假设i<j,那么sub(i,end1)==s2,sub(j,end2)==s2，那么end2>=end1。。。
    //找循环
    if(areas.empty())
    {
        return 0;
    }

    unordered_map<int,pair<int,int>> st;
    st.insert({0,{1,areas[0][2]}});
    int loopStart= -1;
    int loopEnd = -1;
    int pre = 0;
    int count = 1;
    int cc1 = areas[0][2];
    while(cc1 <= n1 && loopStart == -1)
    {
        bool haveNext = false;
        for(int i=0;i<areas.size();++i)
        {
            if(areas[i][0] > areas[pre][1] && areas[i][2] == areas[pre][2])
            {
                haveNext = true;
                cc1 += areas[i][2]-1;
                ++count;
                printf("gwy\n");
                if(st.find(i) != st.end())
                {
                    loopStart = i;
                    loopEnd = pre;
                    break;
                }
                pre = i;
                st.insert({i,{count,cc1}});
            }
        }
        if(!haveNext)
        {
            loopStart = 0;
            loopEnd = 0;
            ++count;
            cc1 += areas[0][2]-1;
        }
    }

    if(loopStart == -1)
    {
        return (count-1) / n2;
    }

    int s2cc = count - st[loopStart].first;
    int s1cc = cc1 - st[loopStart].second + 1;
    printf("count:%d s1cc:%d s2cc:%d\n",count,s1cc,s2cc);

    //循环部分 
    int group = n1 / s1cc;
    int remain = n1 % s1cc;
    int res =  group * s2cc; 

    //前面的部分
    for(int i=0;i<areas.size() && areas[i][2] == 1;++i)
    {
        if((i==0 || areas[i][0] > areas[pre][1]) && areas[i][1] < areas[loopStart][0])
        {
            ++res;
            pre = i; 
        }
    }


    //后面的部分
    cc1=0;
    remain = loopStart == 0 ? remain : remain + 1;
    printf("res:%d remain:%d\n",res,remain);
    for(int i=loopStart;i<areas.size();++i)
    {
        if((i==loopStart || areas[i][0] > areas[pre][1]) && cc1 + areas[i][2] <=remain)
        {
            ++res;
            pre = i;
            cc1 += areas[i][2]-1;
        }
    }

    return res / n2;
}

int getMaxRepetitions2(string s1, int n1, string s2, int n2) {
    //思路：因为s1重复，s2也重复，所以问题在于如何获取到由s1组成的一段区域
    //这段区域刚好是一个S2的开始，和一个S2的结束，这样就可以直接计算数量而不用重复遍历
    //可能的问题在于找这样的区域时间太长。。。而且还要处理剩余部分
    //这里想法都有个问题就是没有充分利用s1和s2重复这个前提，基于这个重复的特点，其实问题就变为了在s1中找s2
    //但问题在于可能多个s1组合后才能找到s2,这个时候分类：
    //1.s1=其它+k个s2+其它，这种最简单，结果就是(n1*k)/n2
    //2.s1=s2后面一部分+k个s2+s2前面一部分，这样首尾相接可以得到新的s2，这个时候结果是(n1*k+n1-1)/n2
    //注意，这里没有递归，也就是首尾连接最多一个s2，所以问题变成了如何在s1中找s2了


    if(s1.empty() || s2.empty())
    {
        return 0;
    }

    vector<vector<int>> areas;
    for(int i=0;i<s1.size();++i)
    {
        if(s1[i] == s2[0])
        {
            int cc1 = 0;// (i==s1.size()-1 ? 1 : 0);
            int k = i;// (cc1 == 1 ? 0 : i+1);
            for(int j= 0; cc1 < n1;)
            {
                if(s1[k] == s2[j])
                {
                    ++j;
                    if(j == s2.size())
                    {
                        areas.push_back({i,k,cc1+1});
                        printf("push:%d %d %d\n",i,k,cc1+1);
                        break;
                    }
                }

                ++k;
                if(k == s1.size())
                {
                    k = 0;
                    ++cc1;
                }
            }
        }
    }

    if(areas.empty())
    {
        return 0;
    }

    //通过areas的最后一个元素可以知道最少需要几个s1才能找到一个s2，这样我们可以计算出一个结果,这个结果不考虑连接共用
    //如果知道最少要n个s1组成一个s2，那么考虑开始位置，最多也就是n+1个s1可以找到一个s2，所以areas中只有这两种情况
    //对于每一步的选择，我们采用贪心算法，尽量使结束位置靠前，这样有更多的选择，而areas中的区间是有序的，排在前面的一定是早结束的
    int cc1=areas[0][2],cc2=1;
    vector<pair<int,int>> flags(areas.size(),pair<int,int>(-1,-1));
    flags[0] = {cc1,cc2};
    int res = 0;
    int pre = 0;

    while(true)
    {
        bool next = false;
        for(int i=0;i<areas.size() && cc1 + areas[i][2]-1<=n1;++i)
        {
            if(areas[i][0] > areas[pre][1])
            {
                pre = i;
                next = true;
                cc1 += areas[i][2]-1;
                ++cc2;
                break;
            }
        }

        if(!next)//没找到意味着又从0开始了
        {
            printf("cc1:%d cc2:%d\n",cc1,cc2);
            res = n1 / cc1 * cc2;
            int remain = n1 % cc1;
            if(remain >= areas[0][2])
            {
                pre = 0;
                ++res;
                cc1 = areas[0][2];
                for(int i=0;i<areas.size();++i)
                {
                    if(areas[i][0] > areas[pre][1] && cc1 + areas[i][2]-1 <= remain)
                    {
                        ++res;
                        cc1 += areas[i][2]-1;
                        i = -1;//重新开始
                    }
                }
            }

            break;
        }
        else if(flags[pre].first > -1) //循环了
        {
            int t1 = cc1 - flags[pre].first;
            int t2 = cc2 - flags[pre].second;

            int units = (n1 - flags[pre].first) / t1; //组数
            res = flags[pre].second + units * t2;

            //处理剩余的
            int remain = (n1 - flags[pre].first) % t1;
            cc1 = 0;
            for(int i=0;i<areas.size() ;++i)
            {
                if(areas[i][0] > areas[pre][1] && cc1+areas[i][2]-1<= remain)
                {
                    pre = i;
                    cc1 += areas[i][2]-1;
                    ++res;
                    i=-1;
                }
            }

            break;
        }

        flags[pre]={cc1,cc2};
    }
    printf("res:%d\n",res);
    return res / n2;
    
}

int main()
{
    printf("%d\n",getMaxRepetitions2("acb",4,"ab",2)); //2
    printf("%d\n",getMaxRepetitions2("aaa",3,"aa",1)); //4
    printf("%d\n",getMaxRepetitions2("acb",1,"acb",1)); //1
    printf("%d\n",getMaxRepetitions2("bacaba",3,"abacab",1)); //2
    printf("%d\n",getMaxRepetitions2("baba",11,"baab",1)); //7
    printf("%d\n",getMaxRepetitions2("nlhqgllunmelayl" ,2,"lnl",1)); //3
    printf("%d\n",getMaxRepetitions2("ecbafedcba", 4, "abcdef", 1)); //1
    // printf("%d\n",getMaxRepetitions2("lovelive", 0, "lovelive", 10));
    printf("%d\n",getMaxRepetitions2("niconiconi", 99981, "nico", 81)); //2468
    printf("%d\n",getMaxRepetitions2("aaa", 20,"aaaaa",1)); //12


    return 0;
}