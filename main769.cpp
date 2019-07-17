//leetcode 769. 最多能完成排序的块

#include <cstdio>
#include <vector>

using namespace std;

int maxChunksToSorted(vector<int>& arr) {
    
    //思路：分成块，然后块不动，连接后是一个升序数组
    //很明显，第一块必须包含0到块长度-1的数字，同理，其它块也是一样
    //策略就是，一块一块的分，对于每一块，我们标记要找的最大数和最小数，如果同时找到，则这块完成
    //最小数很简单，即前面块的元素的数量总和，最大数则由已碰到的最大数和当前的数量为准

    int start=0,end=0;
    bool find_start = false;
    int count=0;
    for(int i=0;i<arr.size();++i)
    {
        end = max(end,arr[i]);
        if(arr[i] == start)
        {
            find_start= true;
        }

        if(find_start && i == end)
        {
            ++count;
        }
    }

    return count;
}

int maxChunksToSorted2(vector<int>& arr)
{
    //比上面的思路更精炼一些，不需要找到块的最开始的数，因为最大数和块的数量确定后，最小数其实也就确定了
    //这三个数存在start+count=end,所以确定其中两个就行，其中for循环中的i可以理解为数量
    int cnt = 0;
    int maxValue = 0;
    for(int i=0;i<arr.size();i++){
        maxValue = max(maxValue,arr[i]);
        if(maxValue==i) 
            cnt++;
    }
    return cnt;
}

int main()
{
    vector<int> v = {1,0,2,3,4};
    // v = {4,3,2,1,0};
    printf("%d\n",maxChunksToSorted(v));
    return 0;
}