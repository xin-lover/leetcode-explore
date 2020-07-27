//1451. 重新排列句子中的单词

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

string arrangeWords(string text) {
    //思路：首先肯定是分割，然后按长度排序，排序直接用sort
    //注意处理一下首字符，因为单词可能很长，所以我们记录实际单词，而是记录首尾记录

    int n = text.size();
    text[0] -= 'A'-'a';
    vector<vector<int>> words;
    int start = 0;
    for(int i=0;i<text.size();++i)
    {
        if(text[i] == ' ')
        {
            words.push_back({start,i-1});
            start = i+1;
        }
    }

    if(start < text.size())
    {
        words.push_back({start,n-1});
    }

    sort(words.begin(),words.end(),[](vector<int>& a, vector<int>& b){
        if(a[1]-a[0] == b[1]-b[0])
        {
            return a[0] < b[0];
        }
        return a[1]-a[0] < b[1]-b[0];
    });

    string res(n,' ');
    start = 0;
    for(auto a : words)
    {
        for(int i=a[0];i<=a[1];++i)
        {
            res[start++] = text[i];
        }

        ++start;
    }

    res[0] += 'A' - 'a';
    return res;

}

int main()
{
    string text = "Leetcode is cool";   //"Is cool leetcode"
    text = "Keep calm and code on"; //"On and keep calm code"
    text = "To be or not to be";    //"To be or to be not"

    //"Kry hkbwx ubogo xqpqd jlhvvd qcuucx xmwohi qvzegb qsvqskq llwzeug ipwbapd cqwfypww dyphntfz tuqppyipb dkvhhgecd wfwnphmxoa sbdfmnyeim hrsaebveez aszqnvruhr mlghuuwvec xpefyglstj"
    text = "Jlhvvd wfwnphmxoa qcuucx qsvqskq cqwfypww dyphntfz hkbwx xmwohi qvzegb ubogo sbdfmnyeim tuqppyipb llwzeug hrsaebveez aszqnvruhr xqpqd ipwbapd mlghuuwvec xpefyglstj dkvhhgecd kry";
    printf("%s\n",arrangeWords(text).c_str());

    return 0;
}