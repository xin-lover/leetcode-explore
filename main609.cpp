//leetcode 609. 在系统中查找重复文件


#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<vector<string>> findDuplicate2(vector<string>& paths) {
    
    //这个题目更多考察数据组织的能力
    //这里面有三个信息，目录，文件名，文件内容
    //把内容作为键值应该是最直接的方式，但不合适，因为内容可能很大，所以不使用map，使用两个vector

    unordered_map<string,vector<string>> um;

    for(auto a : paths)
    {
        int start = 0;
        string dir;
        for(int i=1;i<=a.size();++i)
        {
            if(a[i] == ' ' || a[i] == '\0')
            {
                string t = a.substr(start,i-start);
                if(start == 0)
                {
                    dir = t;
                }
                else
                {
                    size_t pos = t.find('(');
                    string ct = t.substr(pos+1,t.size() - pos - 1);
                    if(um.find(ct) != um.end())
                    {
                        um[ct].push_back(dir + "/" + t.substr(0,pos));
                    }
                    else
                    {
                        um[ct]={dir + "/" + t.substr(0,pos)};
                    }
                    
                }
                
                start = i+1;
            }
        }
    }

    vector<vector<string>> res;
    for(auto it : um)
    {
        if(it.second.size() >= 2)
        {
            res.push_back(it.second);
        }
    }
    return res;

}

vector<vector<string>> findDuplicate(vector<string>& paths) {
    
    //这个题目更多考察数据组织的能力
    //这里面有三个信息，目录，文件名，文件内容
    //把内容作为键值应该是最直接的方式，但不合适，因为内容可能很大，所以不使用map，使用两个vector

    vector<string> contents;
    vector<vector<string>> files;

    for(auto a : paths)
    {
        int start = 0;
        string dir;
        for(int i=1;i<=a.size();++i)
        {
            if(a[i] == ' ' || a[i] == '\0')
            {
                string t = a.substr(start,i-start);
                if(start == 0)
                {
                    dir = t;
                }
                else
                {
                    size_t pos = t.find('(');
                    string ct = t.substr(pos+1,t.size() - pos - 1);
                    bool have = false;
                    for(int i=0;i<contents.size();++i)
                    {
                        if(contents[i] == ct)
                        {
                            have = true;
                            files[i].push_back(dir + "/" + t.substr(0,pos));
                            break;
                        }
                    }
                    if(!have)
                    {
                        contents.push_back(ct);
                        files.push_back({dir + "/" + t.substr(0,pos)});
                    }
                }
                
                start = i+1;
            }
        }
    }

    int index=  0;
    while(index < files.size())
    {
        if(files[index].size() < 2)
        {
            files.erase(files.begin() + index);
        }
        else
        {
            ++index;
        }
        
    }

    return files;

}

int main()
{
    vector<string> v = {"root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"};
    auto res = findDuplicate2(v);

    for(auto a : res)
    {
        for(auto b : a)
        {
            printf("%s ",b.c_str());
        }
        printf("\n");
    }

    return 0;
}