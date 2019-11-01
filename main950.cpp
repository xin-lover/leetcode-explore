//leetcoce 950. 按递增顺序显示卡牌

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void insert(vector<int>& deck,int left,int right,vector<int>& res)
{
    if(left == right)
    {
        res[left] = deck[left];
        return;
    }
    int mid = left + (right - left) / 2;
    insert(deck,mid+1,right,res);

    if(mid-left+1 > right - mid)//处理奇数个元素的情况
    {
        int t = res[right];
        for(int i=right;i>=mid+2;--i)
        {
            res[i] = res[i-1];
        }

        res[mid+1] = t;
    }

    for(int i=1,p1=mid+1;p1<=right;i+=2,++p1)
    {
        res[left+i] = res[p1];
    }

    for(int i=0,p1=left;p1<=mid;i+=2,++p1)
    {
        res[left+i] = deck[p1];
    }


}

vector<int> deckRevealedIncreasing(vector<int>& deck) {
    //思路：不断的对后一半倒序，然后插入到前半部分，但要注意奇偶，如果前半部分是奇数，则后半部分第一个数会被压入最后
    //但这是错误的，这并不是一个栈，而是一个队列，压入底部后，它还是顺序的
    //对于偶数个元素的数组，不断的把后半部分插入前半部分即可，对于奇数个元素的数组，第一个分组后，后半部分就变成了偶数个
    //但取前半部分最后一张牌的时候，会把后一张也就是后半部分的第一张压入牌底部，所以后半部分应该是把最后一个元素移到第一个
    //之后就是不断把数组分为两半，后半部分插入前半部分

    sort(deck.begin(),deck.end());

    vector<int> res(deck.size());
    insert(deck,0,deck.size()-1,res);
    return res;
}

vector<int> deckRevealedIncreasing2(vector<int>& deck)
{
    //思路：模拟取牌
    int N = deck.size();
    queue<int> index;
    for (int i = 0; i < N; ++i)
        index.push(i);

    vector<int> ans(deck.size());
    sort(deck.begin(),deck.end());
    for (int card: deck) {
        int k = index.front();
        ans[k] = card;
        index.pop();
        if (!index.empty())
        {
            k = index.front();
            index.pop();
            index.push(k);
        }
    }

    return ans;
}

int main()
{
    vector<int> deck = {17,13,11,2,3,5,7};
    // deck = {2,3,5,4};
    // deck = {1,2,3,4,5,6};
    vector<int> rr = deckRevealedIncreasing2(deck);
    for(auto a : rr)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}