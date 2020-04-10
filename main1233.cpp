//1233. 删除子文件夹

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<string> removeSubfolders(vector<string>& folder) {
    //思路：这个可以理解前缀，也就是如果一个字符串是另一个字符串的前缀
    //那么删除另一个字符串,如果使用字符串contains的功能，那么问题可以变简单一些
    //不过要注意，/a/b,/a/b/c,/a这种情况，也就是需要对已存在的前缀作删除处理
    //也就是说对于新的字符串，它可能是子文件夹，也可能是前缀
    //一个简单的做法是对folder排序，幸运的是‘/’的ascii码比‘a'小，子文件夹刚好连起来

    sort(folder.begin(),folder.end());

    vector<string> res;
    res.push_back(folder[0]);
    int cur = 0;
    for(int i=1;i<folder.size();++i)
    {
        int j=0;
        for(;j<folder[cur].size();++j)
        {
            if(folder[cur][j] != folder[i][j])
            {
                break;
            }
        }

        if(j != folder[cur].size() || (folder[i].size() > j && folder[i][j] != '/'))
        {
            res.push_back(folder[i]);
            cur= i;   
        }
    }

    return res;
}

int main()
{
    vector<string> folder = {"/a","/a/b","/c/d","/c/d/e","/c/f"};   //["/a","/c/d","/c/f"]
    folder = {"/a","/a/b/c","/a/b/d"};//["/a"]
    // folder = {"/a/b/c","/a/b/d","/a/b/ca"};//["/a/b/c","/a/b/ca","/a/b/d"]

    vector<string> res = removeSubfolders(folder);
    for(auto a : res)
    {
        printf("%s ,",a.c_str());
    }
    printf("\n");

    return 0;
}