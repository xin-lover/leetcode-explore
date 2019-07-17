#include <cstdio>
#include <string>
#include <vector>
#include <set>

using namespace std;

int longestSubstring(string s, int k) {
    
    //思路：子串应该是连续的，采用分治法，把s分为两部分，最长子串只会出现在左半部分，右半部分，和中间区域
    //这种思路不行，主要中间部分的工作就相当于求解整个子串，没有分治的效果
    //还有一种思路，记录所有字符出现的次数，然后分区间使用动归，比如[1,n-2]，就把0和n-1位置的字符去掉即可
    //

    vector<int> ay(26,0);
    for(int i=0;i<s.size();++i)
    {
        ++ay[s[i]-'a'];
    }

    int n = s.size();
    int left = 0;
    int right = n-1;
    while(left < right)
    {
        int pos = -1;
        for(int i=0;i<ay.size();++i)
        {
            if(ay[i] > 0 && ay[i] < k)
            {
                pos = i;
                break;
            }
        }

        printf("pos:%d\n",pos);
        if(pos < 0)
        {
            return right-left+1;
        }

        int lt=left,rt=right;
        while(ay[pos] > 0)
        {
            char nc = 'a' + pos;
            for(int i=left;i<=right;++i)
            {
                if(s[i] == nc)
                {
                    lt = i-left + 1;
                    break;
                }
            }   

            for(int i=right;i>=left;--i)
            {
                if(s[i] == nc)
                {
                    rt = right-i + 1;
                    break;
                }
            }

            printf("nc:%c lf:%d rt:%d\n",nc,lt,rt);
            if(lt <= rt)
            {
                for(int i=left;i<left+lt;++i)
                {
                    --ay[s[i]-'a'];
                    printf("lll:%c %d\n",s[i],ay[s[i]-'a']);
                }
                left += lt;
            }
            else
            {
                for(int i=right;i>right-rt;--i)
                {
                    --ay[s[i]-'a'];
                }
                right -= rt;
            }

            
            printf("wy nc:%c cc:%d\n",nc,ay[nc-'a']);
            printf("left:%d right:%d\n",left,right);
        }
    }

    return k==1 && left == right ? 1 : 0;
}

int main()
{
    // printf("%d\n",longestSubstring("aaabb",3));
    printf("%d\n",longestSubstring("ababbc",2));
    // printf("%d\n",longestSubstring("ababacb",3));
    return 0;
}