//leetcode 881. 救生艇

#include <cstdio>
#include <vector>

using namespace std;

int numRescueBoats(vector<int>& people, int limit) {
    //思路：最多两个人，所以我们先排序，最重的肯定和最轻的组合一起，如果不符合要求，则继续下一个

    //主要是排序费时,优化排序
    sort(people.rbegin(),people.rend());

    int left = 0,right=people.size()-1;

    int res = 0;
    while(left<right)
    {
        if(people[left]+people[right] > limit)
        {
            ++left;
        }
        else
        {
            ++left;
            --right;
        }
        ++res;
    }

    if(left == right)
    {
        ++res;
    }

    return res;
}
int numRescueBoats2(vector<int>& people, int limit) 
{
    int lenth = people.size(), num = 0;
    if (lenth == 0)
        return 0;
    vector<int> arr(limit+1);
    for (int i = 0; i < lenth; i++) {
        //people[i]是体重，对应arr数组的下标
        arr[people[i]]++;//统计人数
    }

    int k = 0;
    //排序
    for (int i = 0; i <= limit; i++) {
        while (arr[i] != 0) {
            //i为体重
            people[k] = i; //重新为people数组排序
            arr[i]--;
            k++;
        }
    }
    for(auto a : people)
    {
        printf("%d ",a);
    }
    printf("\n");

    int cur = 0;
    for (int i = lenth - 1; i >= cur; i--) {
        if (limit - people[i] >= people[cur]) {
            cur++;
        }
        num++;
    }

    return num;
}

int main()
{
    vector<int> v = {1,2};
    printf("%d\n",numRescueBoats2(v,3));
    v = {3,2,2,1};
    printf("%d\n",numRescueBoats2(v,3));
    v = {3,5,3,4};
    printf("%d\n",numRescueBoats2(v,5));
    return 0;
}