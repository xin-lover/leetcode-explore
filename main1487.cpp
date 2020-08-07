//1487. 保证文件名唯一

#include <cstdio>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> getFolderNames(vector<string>& names) {
    //思路：重点是如何确定名字已存在，简单的思路就是用map或set

    vector<string> res(names.size());
    set<string> st;
    for(int i=0;i<names.size();++i)
    {
        string tmp = names[i];
        if(st.find(names[i]) != st.end())
        {
            int j = 1;
            //这个string连接效率不高，可优化
            while(st.find(tmp = (names[i] + "(" + to_string(j) + ")")) != st.end())
            {
                ++j;
            }
        }

        st.insert(tmp);
        res[i] = tmp;
    }

    return res;
}

vector<string> getFolderNames2(vector<string>& names) {
    //思路：重点是如何确定名字已存在，简单的思路就是用map或set
    //字符串连接比较耗性能，所以优化点在于避免字符串的频繁连接

    vector<string> res(names.size());
    set<pair<string,int>> st;
    for(int i=0;i<names.size();++i)
    {
        int j = 0;
        while(st.find({names[i],j}) != st.end())
        {
            ++j;
        }

        st.insert({names[i],j});
        if(j == 0)
        {
            res[i] = names[i];
            if(names[i].back() == ')')
            {
                auto left = names[i].find_last_of('(');
                bool isNum = true;
                if(left != string::npos)
                {
                    for(int k=left+1;k+2<names[i].size();++k)
                    {
                        if(names[i][k] < '0' || names[i][k] > '9')
                        {
                            isNum = false;
                            break;
                        }
                    }
                    if(isNum)
                    {
                        int p = stoi(names[i].substr(left+1,names[i].size()-left-2));
                        if(p > 0)
                        {
                            st.insert({names[i].substr(0,left),p});
                        }
                        
                    }
                    
                }

            }
        }
        else
        {
            res[i] = names[i] + "(" + to_string(j) + ")";
            st.insert({res[i],0});
        }
    }

    return res;
}

vector<string> getFolderNames3(vector<string>& names) {
    //思路：上述方法写的太复杂，我们再进一步，给每个前缀和一个这个前缀的数量
    //那么遇到这个前缀之后，直接就能确定给那个数字

    //这里比上面好的一个点就是哈希表，哈希表还是比set效率高

    unordered_map<string,int> um;
    vector<string> res(names.size());
    for(int i=0;i<names.size();++i)
    {
        if(um.find(names[i]) == um.end())
        {
            um[names[i]] = 1;
            res[i] = names[i];
        }
        else
        {
            do
            {
                res[i] = names[i] + "(" + to_string(um[names[i]]) + ")";
                ++um[names[i]];
            } while (um.find(res[i]) != um.end());
            
            um[res[i]] = 1;
        }
    }

    return res;
}

int main()
{
    vector<string> names = {"pes","fifa","gta","pes(2019)"};
    names = {"gta","gta(1)","gta","avalon"};    //["gta","gta(1)","gta(2)","avalon"]
    names = {"onepiece","onepiece(1)","onepiece(2)","onepiece(3)","onepiece"};//["onepiece","onepiece(1)","onepiece(2)","onepiece(3)","onepiece(4)"]
    // names = {"wano","wano","wano","wano"};  //["wano","wano(1)","wano(2)","wano(3)"]
    // names = {"kaido","kaido(1)","kaido(2)","kaido(1)"};  //["kaido","kaido(1)","kaido(2)","kaido(1)(1)"]
    names = {"kingston(0)","kingston","kingston"};  //["kingston(0)","kingston","kingston(1)"]
    for(auto a : getFolderNames3(names))
    {
        printf("%s ",a.c_str());
    }
    printf("\n");

    return 0;
}