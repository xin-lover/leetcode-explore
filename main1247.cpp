//1247. 交换字符使得字符串相同

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int minimumSwap(string s1, string s2) {
    //思路：第一直觉就是动态规划，但问题是交换的字符是任意位置的，我们如何推到递推公式
    //交换必须在s1和s2之间进行，而隐含的一个情况就是两者字符肯定不同
    //所以对于s1中的x，有效的交换位置是s2中所有的y位置
    //而从s1 = "xy", s2 = "yx"的例子中可以看出可以通过2步交换同一字符串中的两个位置的字符
    //所以一个令s1和s2相同的方案就出来了，先让s1和s2含有相同数量的x和y，然后交换其中一个字符串，比如s1令其与s2相同
    //但如何保证最少步数
    //我们先考虑第一个位置，如果相同就递进到下一个位置，不同，那么我们的选择肯定是拿其中的一个字符与另一个字符串中不同位置的一个不同字符交换
    //这个时候选择的顾虑有：
    //1.就是如果那个位置两个字符串相同，那么肯定不能选它
    //2.如果没有这样的位置，也就是字符全部相同，那么我们就需要通过2步法把s2中的预期字符移过去，如果s2中也没有，那么结束了，不可能相同
    //考虑让s1变成s2和s2变为s1会有什么不同？它们应该是相同的，因为交换不同字符都是相对来说的，s1[i]!=s2[i],也就是s2[i]!=s1[i]
    
    int step = 0;
    int n = s1.size();
    for(int i=0;i<n;++i)
    {
        if(s1[i] == s2[i])
        {
            continue;
        }

        bool have = false;
        for(int j=i+1;j<n;++j)
        {
            if(s1[j] == s1[i] && s1[j] != s2[j])
            {
                have = true;
                s1[j] = s2[i];
                s2[i] = s1[i];
                ++step;
                break;
            }
        }

        if(!have)
        {
            for(int j=i+1;j<n;++j)
            {
                if(s2[j] == s1[i] && s2[j] != s1[j])
                {
                    //s1[j]肯定==s2[i]，以它为轴点交换
                    swap(s2[i],s2[j]);
                    step+=2;
                    have = true;
                    break;
                }
            }
        }

        if(!have)
        {
            return -1;
        }
    }

    return step;
}

//思路2:统计数量xy,yx数量即可，也就是说
//1.对于s1=xx,s2=yy的情况，一步搞定；
//2.对于s1=xy,s2=yx的情况，两步搞定
//所以，也就是说偶数个xy可以经过交换相同，同理yx
//所以最后就剩下xy和yx，如果是偶数个，可以交换成相同字符串，只不过一对需要两步，否则剩余一个xy或yx无法相同
int minimumSwap2(string s1, string s2) {
    int ans = 0, n = s1.size();
    int cnt1 = 0,cnt2 = 0;//统计有多少对x-y和y-x
    for(int i = 0; i < n; i++){
        if(s1[i]=='x'&&s2[i]=='y') cnt1++;
        else if(s1[i]=='y'&&s2[i]=='x') cnt2++;
    }
    //对于每一对 x-y 和 x-y 以及 y-x 和 y-x 都只需要一次操作即可完成匹配
    ans += cnt1/2+cnt2/2;//所需要的操作数
    cnt1%=2;//剩余未匹配的对数
    cnt2%=2;
    if(cnt1+cnt2==1) return -1;//只剩一个时无法匹配
    else if(cnt1+cnt2==2) ans+=2;//只剩了 x-y和y-x 需要两次匹配
    return ans;
}

int main()
{
    // printf("%d\n",minimumSwap("xx","yy"));//1
    // printf("%d\n",minimumSwap("xy","yx"));//2
    // printf("%d\n",minimumSwap("xx","xy"));//-1
    // printf("%d\n",minimumSwap("xxyyxyxyxx","xyyxyxxxyx"));//4
    printf("%d\n",minimumSwap("xyyyyx","xxxxyy"));//3
    return 0;
}