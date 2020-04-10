//1202. 交换字符串中的元素

#include <cstdio>
#include <vector>
#include <string>
#include <queue>

using namespace std;

string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    //思路：因为可以任意多次交换，也就意味着可以复原，
    //同时使用图的思路，每个位置相当于1个节点，数对就是通路，
    //因为是字典顺序，所以我们从前往后确定字符就行，也就是说第一位肯定是放能放的最小值，后面的位同理
    //现在的问题就是第二位会不会依赖第一位？可以发现如果第二位需要通过第一个位置转换，那么只要第二位的值不是第一位要的那个
    //先转换第二位即可，在转换第一位就可以保证第一第二位都是最小
    //还有一种情况就是第一位最小值有多种可能，如何确定用哪种？
    //换一种方式，不根据位置，而是根据字符来排，也就是小的字符优先排
    //比如，a，我们先把a尽量往前排，不然就不是最小的

    //超时

    string res(s.size(),'0');
    vector<vector<int>> nodes(s.size());
    for(int i=0;i<pairs.size();++i)
    {
        nodes[pairs[i][0]].push_back(pairs[i][1]);
        nodes[pairs[i][1]].push_back(pairs[i][0]);
    }

    vector<vector<int>> poses(26);
    for(int i=0;i<s.size();++i)
    {
        poses[s[i]-'a'].push_back(i);
    }

    //深度遍历
    vector<vector<int>> dp(s.size());
    for(int i=0;i<poses.size();++i)
    {
        //一个一个的排
        for(int q : poses[i])
        {
            vector<bool> visited(s.size(),false);
            queue<int> qu;
            qu.push(q);

            while(!qu.empty())
            {
                int p = qu.front();
                qu.pop();
                if(!visited[p])
                {
                    visited[p]=true;
                    for(int j=0;j<nodes[p].size();++j)
                    {
                        qu.push(nodes[p][j]);
                    }
                }
            }

            // if(i+'a' == 'v')
            // {
            // for(int k=0;k<visited.size();++k)
            // {
            //     printf(visited[k] ? "true,":"false,");
            // }
            // printf("\n");
            // }

            
            for(int k=0;k<visited.size();++k)
            {
                if(visited[k] && res[k] == '0')
                {
                    res[k] = i + 'a';
                    break;
                }
            }
        }

    }

    return res;
}

int findRoot(vector<int>& flags,int v)
{
    int tmp=v;
    while(flags[tmp] >= 0)
    {
        printf("tmp:%d\n",tmp);
        tmp = flags[tmp];
    }

    //压缩路径  //这一步很关键，因为链可能很长
    int t=v;
    while(flags[t] >= 0)
    {
        int tt = flags[t];
        flags[t] = tmp;
        t = tt;
    }

    return tmp;
}

string smallestStringWithSwaps2(string s, vector<vector<int>>& pairs) {
    //上述的思路没问题，只是深度遍历太费时了，而且很多重复循环
    //使用并查集，因为上面的深度遍历只是为了得到这个位置能到达的其它位置
    //注意我们我们需要同一个集合中的位置按大小串连起来，类似链表，然后不断更新头节点
    //这里可以有两种方式：
    //一种是根据集合遍历，也就是吧集合中出现的位置和字符都统计出来，然后根据位置排列字符
    //另外一种是根据字符从a开始遍历，统计a出现的位置，然后位置找到集合，因为集合的位置用链表的方式连接
    //所以我们只要不断的使用头节点位置即可，

    vector<int> flags(s.size(),-1);
    for(int i=0;i<pairs.size();++i)
    {
        int t1 = findRoot(flags, pairs[i][0]);
        int t2 = findRoot(flags, pairs[i][1]);
        if(t1 != t2)
        {
            flags[t2] = t1;
        }
        
    }
    // printf("aa:");
    // for(int i=0;i<flags.size();++i)
    // {
    //     printf("%d,",flags[i]);
    // }
    // printf("\n");

    // printf("wy:%d\n",findRoot(flags,3));
    //分集合,集合用链表的方式组织
    vector<int> heads(flags.size(),-1);
    vector<int> links(flags.size(),-1);
    for(int i=links.size()-1;i>=0;--i)
    {
        int r = findRoot(flags,i);
        links[i] = heads[r];
        heads[r] = i;
    }
    
    // for(int i=0;i<links.size();++i)
    // {
    //     printf("%d,",links[i]);
    // }

    vector<vector<int>> poses(26);
    for(int i=0;i<s.size();++i)
    {
        poses[s[i]-'a'].push_back(i);
    }

    string res(s.size(),'0');
    for(int i=0;i<poses.size();++i)
    {
        for(int j=0;j<poses[i].size();++j)
        {
            int p = poses[i][j];
            int r = findRoot(flags,p);
            int head = heads[r];
            res[head] = i+'a';
            heads[r]=links[head];
        }
    }

    return res;
}

//另一种并查集思路，先分集合，然后把集合中的字符进行统计，每次抛出集合最小字符

int main()
{
    string s = "dcab";
    vector<vector<int>> pairs = {{0,3},{1,2}};  //bacd

    s = "dcab";
    pairs = {{0,3},{1,2},{0,2}}; //abcd

    s = "cba";
    pairs = {{0,1},{1,2}}; //abc

    s = "fqtvkfkt";
    pairs={{2,4},{5,7},{1,0},{0,0},{4,7},{0,3},{4,1},{1,3}};//"ffkqttkv"

    printf("%s\n",smallestStringWithSwaps2(s,pairs).c_str());
    return 0;
}