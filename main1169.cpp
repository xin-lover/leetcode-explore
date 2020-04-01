//1169. 查询无效交易

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> invalidTransactions(vector<string>& transactions) {
    //思路：首先是解析数据，怎么存储是关键，这个会涉及如何遍历
    //我们用数组存储解析后的数据
    //因为只有名字会产生联系，所以使用map根据名称来存储

    int n = transactions.size();
    vector<bool> flags(n,false);

    vector<vector<string>> data(n);
    unordered_map<string,vector<int>> records;

    for(int i=0;i<n;++i)
    {
        int t = 0;
        for(int j=0;j<transactions[i].size();++j)
        {
            if(transactions[i][j] == ',')
            {
                data[i].push_back(transactions[i].substr(t,j-t));
                t=j+1;
            }
        }
        data[i].push_back(transactions[i].substr(t,transactions[i].size()-t));

        //判断金额
        if(stoi(data[i][2]) > 1000) //data[i][2].size() >= 4)
        {
            flags[i] = true;
        }

        //这里可以优化，现在是线性求解，可考虑排序后二分查找
        string name = data[i][0];
        int time = stoi(data[i][1]);
        for(int k = 0;k<records[name].size();++k)
        {
            int seq = records[name][k];
            if(data[i][3] != data[seq][3])
            {
                if(abs(time - stoi(data[seq][1])) <= 60)
                {
                    flags[i] = true;
                    flags[seq] = true;
                }
            }
        }
        records[data[i][0]].push_back(i);
    }

    vector<string> res;
    for(int i=0;i<flags.size();++i)
    {
        if(flags[i])
        {
            res.push_back(transactions[i]);
        }
    }

    return res;

}

int main()
{
    vector<string> transactions = {"alice,20,800,mtv","alice,50,100,beijing"};
    transactions = {"alice,20,800,mtv","alice,50,1200,mtv"};
    transactions = {"alice,20,800,mtv","bob,50,1200,mtv"};
    transactions = {"alex,676,260,bangkok",
"bob,656,1366,bangkok",
"alex,393,616,bangkok",
"bob,820,990,amsterdam",
"alex,596,1390,amsterdam"};
    vector<string> res = invalidTransactions(transactions);
    for(auto a : res)
    {
        printf("%s,",a.c_str());
    }

    printf("\n");
    return 0;
}

