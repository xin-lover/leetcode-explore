//1418. 点菜展示表

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

vector<vector<string>> displayTable(vector<vector<string>>& orders) {
    //思路：这个主要考查数据如何组织了，因为桌号要有序排列，所以肯定先统计所有桌号
    //其次，姓名不重要，那么我们使用map，桌号为key能满足我们的需求
    //接下来就是如何确定菜名的列的位置，而且同一桌可以点多个一样的菜
    //所以我们使用额外的一个map记录菜名和其位置

    map<string,int> um;
    map<int,unordered_map<string,int>> tableCards;

    for(int i=0;i<orders.size();++i)
    {
        um.insert({orders[i][2],0});
        tableCards[stoi(orders[i][1])][orders[i][2]]++;
    }

    // for(auto a : tableCards)
    // {
    //     printf("%d \n",a.first);
    //     for(auto b : a.second)
    //     {
    //         printf("%s %d\n",b.first.c_str(),b.second);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    vector<vector<string>> res(tableCards.size()+1,vector<string>(um.size()+1,"0"));
    res[0][0] = "Table";
    int i = 1;
    for(auto& a : um)
    {
        a.second = i;
        res[0][i++] = a.first;
    }

    i = 1;
    for(auto a : tableCards)
    {
        res[i][0] = to_string(a.first);
        for(auto b : a.second)
        {
            int col = um[b.first];
            res[i][col] = to_string(b.second);
        }
        ++i;
    }

    return res;
}

int main()
{
    // map<string,int> mp;
    // mp["d"]=0;
    // mp["b"]=0;
    // mp["c"]=0;
    // mp["a"]=0;
    // for(auto a : mp)
    // {
    //     printf("%s ",a.first.c_str());
    // }
    // printf("\n");
    vector<vector<string>> orders = {{"David","3","Ceviche"},{"Corina","10","Beef Burrito"},{"David","3","Fried Chicken"},{"Carla","5","Water"},{"Carla","5","Ceviche"},{"Rous","3","Ceviche"}};

    for(auto a : displayTable(orders))
    {
        for(auto b : a)
        {
            printf("%s ",b.c_str());
        }

        printf("\n");
    }

    return 0;
}