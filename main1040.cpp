//1040. 移动石子直到连续 II

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> numMovesStonesII(vector<int>& stones) {
    //思路：每次从左右两侧选择一个石子往中间的空位上放
    //正常情况下，每移动一个石子，会移除一个空位，但如果边上石子就是一个，那么用这个石子构成的空位在移动了石子之后就消失了
    //所以在这里就有了分歧，也就是如果边上有两颗或以上的石子，我们可以使用滚动的方式不断向前推，那么最多空位数的步数就能够连续
    //如果边上的石子数少于空位数，那么只要移动石子数的步数就能连续，这是最少的步数
    //但当石子数量为1的时候，我们就不能向前滚动了，这个时候只能往中间的空位插入，而由它构成的那一段空位消失了
    //我们现在要考虑插入的位置是否对结果有影响
    //如果插入的位置和原有的石子相连，空位-1，如果插入的位置让它还是独立的石子，那么很明显，对结果是有影响的
    //但我们这么考虑，我们最多就是移动空位数那么多步，而唯一会对这个有影响的就是一开始边上只有一个石子的情况，这个时候不能用这个石子滚动到第一段空位上
    //而之后我们可以任意组成一段连续石子，滚动经过所有空位，所以最大的移动步数能确定
    //而最小步数我们就可以理解为每次移动石子，我们要能移除最多的空位或者让之后能移除更多的空位
    //我们考虑选择一个石子为基准，让其它所有的石子都往这个石子上靠，最后得到一段连续的石子，最好的情况就是移动 n-2石子，也就是n-2步
    //但很多时候不可能刚好有这么一段空位，所以第一步应该是构建这样的空位区间
    //我们总能构建这样的区间，区别就是在哪构建，对于石子+空位+石子这样的结构，我们选择两端石子少的那个往多的那个去靠
    //但如果中间有很多石子段，那么我们如何选择？这样不好考虑，但我们最终是要一段连续但石子
    //我们可以使用窗口，如何让这个窗口中原来石子的数量最多即可

    if(stones.empty())
    {
        return {0,0};
    }
    unordered_map<int,int> um;
    int mnv=stones[0],mxv = stones[0];
    for(int i=0;i<stones.size();++i)
    {
        um[stones[i]] = 1;
        mnv = min(mnv,stones[i]);
        mxv = max(mxv,stones[i]);
    }

    int mx = mxv -mnv + 1 - stones.size();
    if(um.find(mnv+1) == um.end() && um.find(mxv-1) == um.end())
    {
        int t1 = 1;
        for(int i=mnv+2;um.find(i) != um.end();++i)
        {
            ++t1;
        }

        int t2 = 1;
        for(int i=mxv-2;um.find(i) != um.end();--i)
        {
            ++t2;
        }

        mx -= min(t1,t2);
    }

    //确定填充区间，也就是把左右的石子填到这个区间中
    int left_count = 0,right_count=stones.size();
    for(int i=mnv;i<mnv+stones.size();++i)
    {
        if(um.find(i) != um.end())
        {
            --right_count;
        }
    }

    int mn = right_count;
    if(right_count == 1 && um.find(mnv+stones.size()-1) == um.end())
    {
        mn = right_count+1;
    }
    int left = mnv;
    for(int i=mnv+stones.size();i<=mxv;++i)
    {
        int lf = (um.find(left)==um.end() ? 0 : 1);
        int rf = (um.find(i) ==um.end() ? 0 : 1);
        left_count += lf;
        right_count -= rf;
        ++left;

        int cc = left_count + right_count;
        if((left_count == 1 && right_count == 0 && um.find(left) == um.end()) || (right_count == 1 &&  left_count == 0 && um.find(i) == um.end()))
        {
            cc+=1;
        }
        // printf("i:%d lfc:%d rfc:%d cc:%d\n",i,left_count,right_count,cc);   

        mn = min(mn,cc);
    }
    
    return {mn, mx};
}

vector<int> numMovesStonesII2(vector<int>& stones) {
    //思路：上面的方法超时，也就是石子的位置会非常大，所以固定窗口的方式需要的遍历时间会很长
    //我们改为直接遍历数字，也就是我们的窗口右移的时候直接越过空位，那么我们需要知道在某个数字之前有多少个石子
    //我们使用排序的方式来确定

    int n = stones.size();
    if(n < 3)
    {
        return {0,0};
    }
    sort(stones.begin(),stones.end());
    // unordered_map<int,int> um;
    // for(int i=0;i<n;++i)
    // {
    //     um[stones[i]] = i+1;
    // }

    int mx = stones.back() - stones.front()+1-n; //空位数量
    if(stones[1]-stones[0] > 1 && stones[n-1] - stones[n-2] > 1)
    {
        mx -= (min(stones[1]-stones[0],stones[n-1]-stones[n-2]) - 1); //两侧选取少空位的那个
    }

    int mn = n;
    for(int i=0;i<n;++i)
    {
        int front = stones[i]-n;
        printf("front:%d\n",front);
        int frontPos = 0;
        if(front >= stones[0])
        {
            int left=0,right=i;
            while(left < right)
            {
                int mid = left + (right - left) / 2;
                if(stones[mid] > front)
                {
                    right = mid;
                }
                else
                {
                    left = mid+1;
                }
            }

            if(stones[right] >= front)
            {
                frontPos = right;
            }
            
        }

        
        int leftStones = frontPos;
        int rightStones = n - 1 - i;

        int cc = leftStones + rightStones;
        if((leftStones == 1 && rightStones == 0 && stones[frontPos] != front+1) || (leftStones == 0 &&  rightStones == 1 && stones[i]+1 != stones[n-1]))
        {
            cc+=1;
        }
        mn = min(cc,mn);
    }

    return {mn,mx};
}

vector<int> numMovesStonesII3(vector<int>& stones) {
    //思路：观察发现，其实求最小移动步数的时候，只有一种额外情况，就是其它石子连续，剩下的一个距离这段石子一个以上的空位
    //我们考虑一下非连续的石子排列中，是否有两个n的窗口，其中能覆盖n-1个石子，
    //这个是有的，但这样就意味这有两个空位，而且对称，这种情况是不需要额外的步数的

    int n = stones.size();
    if(n < 3)
    {
        return {0,0};
    }
    sort(stones.begin(),stones.end());

    int empty = stones.back() - stones.front()+1-n;//空位数量
    int mx = empty; 
    if(stones[1]-stones[0] > 1 && stones[n-1] - stones[n-2] > 1)
    {
        mx -= (min(stones[1]-stones[0],stones[n-1]-stones[n-2]) - 1); //两侧选取少空位的那个
    }

    
    int left=0;
    int subMaxLen = 0;
    int mn = n;
    for(int i=0;i<n;++i)
    {        
        while(stones[i]-stones[left]+1 > n)
        {
            ++left;
        }
        
        int len = i - left + 1;
        int t = n - len;
        if(len == n-1 && stones[i]-stones[left]+1 != n)
        {
            t +=1;
        }
        mn = min(mn,t);
    }

    return {mn,mx};
}



int main()
{
    vector<int> stones = {6,5,4,3,10};//{2,3}
    // stones = {7,4,9};//{1,2}
    // stones = {100,101,104,102,103};//{0,0}
    // stones = {8,7,6,5,1000000000};//[2,999999991]
    // stones = {8,7,6,5,10}; //{1,1}
    // stones = {1,500000000,1000000000}; //[2,499999999]
    vector<int> res = numMovesStonesII3(stones);
    printf("%d %d\n",res[0],res[1]);
    return 0;
}