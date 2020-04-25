//1268. 搜索推荐系统

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
    //思路：因为要返回字典排序的前三个，那么肯定要排序，排序时机有两种，一种是先选出符合第一个字符的所有字符串
    //一种是开始就排序，这两个的复杂度没变，简单点，选择一开始就排序
    //因为排序后，相当于相近的字符串都几种在了一起，所以找前缀就更好找了，
    //接下来可以有两种选择，一种是寻找符合前缀的区间，然后每次都在这个区间中寻找下一级的前缀
    //一种是只记录区间的开始位置，每次从这个位置遍历找，最多找3个
    //选择第二种，因为只要3个，但实现过程中不想每次都比较前缀所有的字符，配合第一种思路使用
    //另一种思路就是前缀树，这个最简单了，但空间复杂度高,一个优化方案是只存储我们想要的字符
    //也就是符合前缀字符串，同时每个树节点数量不超过3个

    sort(products.begin(),products.end());

    int start = 0,end = products.size()-1;
    vector<vector<string>> res;
    for(int i=0;i<searchWord.size();++i)
    {
        vector<string> tmp;
        for(int j=start;j<=end;++j)
        {
            if(products[j][i] == searchWord[i])
            {
                if(tmp.empty())
                {
                    start = j;
                }
                if(tmp.size() < 3)
                {
                    tmp.push_back(products[j]);
                }
            }
            else if(products[j][i] > searchWord[i])
            {
                end = j-1;
                break;
            }
        }
        if(tmp.empty())
        {
            start = end+1;
        }
        res.push_back(tmp);
    }

    return res;
}

//另一个思路：二分查找。也是先排序，然后查找最小的大于等于prefix的前3个字符串，然后比较前缀即可
//同时二分查找的左边界可以使用上一次的查找结果

// class Solution {
// public:
//     vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
//         sort(products.begin(), products.end());
//         string query;
//         auto iter_last = products.begin();
//         vector<vector<string>> ans;
//         for (char ch: searchWord) {
//             query += ch;
//             auto iter_find = lower_bound(iter_last, products.end(), query);
//             vector<string> selects;
//             for (int i = 0; i < 3; ++i) {
//                 if (iter_find + i < products.end() && (*(iter_find + i)).find(query) == 0) {
//                     selects.push_back(*(iter_find + i));
//                 }
//             }
//             ans.push_back(move(selects));
//             iter_last = iter_find;
//         }
//         return ans;
//     }
// };

//c++ multiset，红黑树，删除代价较小，和我们的思路差不多，就是不断缩小要比较的字符串范围
//只不过我们不需要删除

int main()
{
    //["mobile","moneypot","monitor"],
    // ["mobile","moneypot","monitor"],
    // ["mouse","mousepad"],
    // ["mouse","mousepad"],
    // ["mouse","mousepad"]
    vector<string> products = {"mobile","mouse","moneypot","monitor","mousepad"};
    string searchWord = "mouse";

    //[["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
    products = {"havana"}; 
    searchWord = "havana";

    //[["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
    products = {"bags","baggage","banner","box","cloths"};
    searchWord = "bags";

    //[]
    // products = {"havana"};
    // searchWord = "tatiana";

    for(auto a : suggestedProducts(products,searchWord))
    {
        for(auto b : a)
        {
            printf("%s ",b.c_str());
        }
        printf("\n");
    }

    return 0;
}