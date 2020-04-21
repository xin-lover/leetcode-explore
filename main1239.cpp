//1239. 串联字符串的最大长度

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

void backtrace(vector<string>& arr,int index,vector<bool>& flags,int& res,int& maxRes)
{
    if(index >= arr.size())
    {
        return;
    }

    if(res + arr[index].size()>26)
    {
        return;
    }

    bool overlap = false;
    vector<bool> tmp(26,false);
    for(int i=0;i<arr[index].size();++i)
    {
        if(tmp[arr[index][i]-'a'])
        {
            overlap = true;
            break;
        }
        tmp[arr[index][i]-'a']=true;
        if(flags[arr[index][i]-'a'])
        {
            overlap = true;
            break;
        }
    }

    if(!overlap)
    {
        res += arr[index].size();
        maxRes = max(res,maxRes);
        for(int i=0;i<arr[index].size();++i)
        {
            flags[arr[index][i]-'a'] = true;
        }
        for(int j=index+1;j<arr.size();++j)
        {
            backtrace(arr,j,flags,res,maxRes);
        }
        res -= arr[index].size();
        for(int i=0;i<arr[index].size();++i)
        {
            flags[arr[index][i]-'a'] = false;
        }

    }
}

int maxLength(vector<string>& arr) {
    //思路：不能有重复字符，意味着最长26
    //arr的长度有16，回溯法性能低，可以试试
    //一个优化是使用位来代替数组

    int res = 0;
    int maxRes = 0;
    vector<bool> flags(26,false);
    for(int i=0;i<arr.size();++i)
    {
        backtrace(arr,i,flags,res,maxRes);
    }

    return maxRes;
}

int StrLenCmp(const void *a, const void *b)
{
    return strlen(*(char **)b) - strlen(*(char **)a);
}

int HasMoreSameChar(char *arr)
{
    int sameCharRec[26] = {0};

    while (*arr != '\0') {
        if (sameCharRec[*arr - 'a'] == 0) {
            sameCharRec[*arr - 'a']++;
        } else {
            return 1;
        }
        arr++;
    }

    return 0;
}

int maxLength2(char **arr, int arrSize)
{
    int monoMaxLen = 0;
    char *startChar = (char *)malloc(sizeof(char) * 27); // 26个字母 + 1空位
    memset(startChar, '\0', sizeof(char) * 27);

    // 利用快排把长度较长的字符串排在前面
    qsort(arr, arrSize, sizeof(char *), StrLenCmp);

    // 两重遍历逐个比较，满足单词内不重复字母且与已组合的单词串字母不重复这两个条件时，合并新单词至已组合单词串中
    for (int i = 0; i < arrSize; i++) {
        // 如果目标字段就有重复的字母，直接pass掉
        if (HasMoreSameChar(arr[i]) == 1) {
            continue;
        }
        // startChar 是每一个i遍历的组合单词串
        strncpy(startChar, arr[i], strlen(arr[i]) + 1);

        for (int j = 0; j < arrSize; j++) {
            // strcspn是找startChar中第一个有arr[j]种字符的位置，如果不存在重复字母，这个位置应该在startChar尾巴上，即strlen(startChar)
            if (i != j && HasMoreSameChar(arr[j]) == 0 && strlen(startChar) == strcspn(startChar, arr[j])) {
                // 满足要求，则组合成一个更长的新串
                startChar = strcat(startChar, arr[j]);
            }
        }
        // 找最大
        monoMaxLen = strlen(startChar) > monoMaxLen ? strlen(startChar) : monoMaxLen;
        memset(startChar, '\0', sizeof(char) * 27);
    }
    return monoMaxLen;
}

int main()
{
    vector<string> arr = {"un","iq","ue"};//4
    // arr = {"cha","r","act","ers"};//6;
    // arr = {"abcdefghijklmnopqrstuvwxyz"};//26
    arr = {"yy"};
    arr = {"a", "abc", "d", "de", "def"};//6
    arr = {"abc","ce","bf"};

    char* aar2[3]={"abc","ce","bf"};
    printf("%d\n",maxLength2(&aar2[0],3));
    return 0;
}