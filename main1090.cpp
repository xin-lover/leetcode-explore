//1090. 受标签影响的最大值

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
    //考虑贪心算法，先对values排序，每一次都选择最大的，同时统计标签

    vector<int> indices;
    for(int i=0;i<values.size();++i)
    {
        indices.push_back(i);
    }

    sort(indices.begin(),indices.end(),[&values](int a,int b)
    {
        return values[a] > values[b];
    });

    int sum = 0;
    unordered_map<int,int> um;
    int count=0;
    for(int i=0;i<indices.size() && count<num_wanted;++i)
    {
        int lb = labels[indices[i]];
        if(um.find(lb) == um.end() || um[lb]+1 <= use_limit)
        {
            // printf("%d ",indices[i]);
            sum += values[indices[i]];
            ++um[lb];
            ++count;
        }
    }
    // printf("\n");

    return sum;
}

int main()
{
    vector<int> values = {3,2,1};
    vector<int> labels = {1,1,1};

    values = {5,4,3,2,1};
    labels = {1,1,2,2,3};
    int num_wanted = 3;
    int use_limit = 1; //9

    values = {5,4,3,2,1};
    labels = {1,3,3,3,2};
    num_wanted = 3;
    use_limit = 2;  //12

    values = {9,8,8,7,6};
    labels = {0,0,0,1,1}; 
    num_wanted = 3; 
    use_limit = 1;  //16


    printf("%d\n",largestValsFromLabels(values,labels,num_wanted,use_limit));

    return 0;
}