#include <cstdio>
#include <vector>

using namespace std;

struct Trie
{
    struct TrieNode
    {
        bool end;
        TrieNode* child[2];
    };
    
    TrieNode* root;
    Trie()
    {
        root = new TrieNode();
    }
    
    void insert(int n)
    {
        TrieNode* p = root;
        for(int i=31;i>=0;--i)
        {
            int bit = (n >> i) & 1;
            if(!p->child[bit])
            {
                p->child[bit] = new TrieNode();
            }
            p = p->child[bit];
        }
        p->end = true;
    }
    
    int search_max_XOR(int x)
    {
        TrieNode* p = root;
        int ans = 0;
        for(int i=31;i>=0;--i)
        {
            int bit = (x >> i) & 1;
            if(p->child[bit^1])
            {
                p = p->child[bit^1];
                ans = ans | (1 << i);
            }
            else
            {
                p = p->child[bit];
            }
        }
        
        return ans;
    }
};

int findMaximumXOR(vector<int>& nums) {
    
    int n = nums.size();
    if(n ==0 || n == 1)
    {
        return 0;
    }
    
    //思路：使用字典树，整数32位，所以这个字典分为32层，每一层可两个节点，表示0和1，这样我们先使用第一个数字构建这个树
    //使用贪心策略，每次新插入一个树的时候从高位开始遍历，如果两个数在该位的值不同则该位的结果取1，否则取0，
    //每次新插入一个数后，整个树都会更新，
    //所以总体思路就是，每次插入一个数的时候，都查找与这个数异或的最大值，
    //它与暴力解法的区别就是提前剪枝了，也即对于每个数查找最大异或值是o（1）时间，所以整个算法是o（N）的时间复杂度
    Trie t;
    t.insert(nums[0]);
    int ans = INT_MIN;
    for(int i=1;i<n;++i)
    {
        ans = max(ans,t.search_max_XOR(nums[i]));
        t.insert(nums[i]);
    }
    
    return ans;
}



int main()
{
    vector<int> v = {3, 10, 5, 25, 2, 8};
    printf("%d\n",findMaximumXOR(v));
    return 0;

}