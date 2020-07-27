//1452. 收藏清单

#include <cstdio>
#include <vector>
#include <string>
#include <set>

using namespace std;

bool isSub(vector<string>& a,vector<string>& b)
{
    // set<string> st(b.begin(),b.end());
    // for(auto& s : b)
    // {
    //     st.insert(s);
    // }

    // for(auto& s : a)
    // {
    //     if(st.find(s) == st.end())
    //     {
    //         return false;
    //     }
    // }
    // st.insert(a.begin(),a.end());

    // return st.size() == b.size();

    return includes(b.begin(),b.end(),a.begin(),a.end());   //includes 效率高。。。。。
}
vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
    //思路：关键在于如何判断子集，考虑最简单的情况，只有两个集合
    //如何判断a是否为b的子集？一个方案是把较大的那个集合用set和map保存，然后查找，性能不会太高
    //另一种是把a和b的元素都插入set中，如果set的size等于较大集合的size，即为子集
    //两者复杂度相同
    //同时，我们再考虑多个集合的情况，可以一个一个去比对，但我们可以考虑并查集
    //这样可以降低需要比对的次数

    for(auto& v : favoriteCompanies)
    {
        sort(v.begin(),v.end());
    }

    vector<int> pos(favoriteCompanies.size());
    for(int i=0;i<favoriteCompanies.size();++i)
    {
        pos[i] = i;
    }
    sort(pos.begin(),pos.end(),[&favoriteCompanies](int a,int b)
    {
        return favoriteCompanies[a].size() > favoriteCompanies[b].size();
    });
    vector<int> dsj;
    for(int i=0;i<pos.size();++i)
    {
        bool sub= false;
        for(int j=0;j<dsj.size();++j)
        {
            if(isSub(favoriteCompanies[pos[i]],favoriteCompanies[dsj[j]]))
            {
                sub = true;
                break;
            }
        }

        if(!sub)
        {
            dsj.push_back(pos[i]);
        }
    }

    vector<int> res(dsj.begin(),dsj.end());
    sort(res.begin(),res.end());
    return res; 
}

int main()
{
    vector<vector<string>> favoriteCompanies = {{"leetcode","google","facebook"},{"google","microsoft"},{"google","facebook"},{"google"},{"amazon"}}; //0,1,4
    // favoriteCompanies = {{"leetcode"},{"google"},{"facebook"},{"amazon"}}; //0,1,2,3
    favoriteCompanies = {{"arrtztkotazhufrsfczr","knzgidixqgtnahamebxf","zibvccaoayyihidztflj"},{"cffiqfviuwjowkppdajm","owqvnrhuzwqohquamvsz"},{"knzgidixqgtnahamebxf","owqvnrhuzwqohquamvsz","qzeqyrgnbplsrgqnplnl"},{"arrtztkotazhufrsfczr","cffiqfviuwjowkppdajm"},{"arrtztkotazhufrsfczr","knzgidixqgtnahamebxf","owqvnrhuzwqohquamvsz","qzeqyrgnbplsrgqnplnl","zibvccaoayyihidztflj"}};//1,3,4

    for(auto a : peopleIndexes(favoriteCompanies))
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}