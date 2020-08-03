//1471. 数组中的 k 个最强值

#include <cstdio>
#include <vector>

using namespace std;

vector<int> getStrongest(vector<int>& arr, int k) {
    //简单的思路就是排序两次

    //其它思路：使用优先队列存储k个值，快速找到可以不用全排序

    int n = arr.size();
    sort(arr.begin(),arr.end());

    int mid = arr[(n-1)/2];
    sort(arr.begin(),arr.end(),[mid](int a,int b){
        if(abs(a-mid) == abs(b-mid))
        {
            return a > b;
        }

        return abs(a-mid) > abs(b-mid);
    });

    return vector<int>(arr.begin(),arr.begin()+k);
}


//双指针法
vector<int> getStrongest2(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
    int m = arr[(arr.size() - 1) / 2];
    int l = 0, r = arr.size() - 1;
    vector<int> ans;
    while (ans.size() < k) {
        if (abs(arr[l] - m) <= abs(arr[r] - m))
            ans.emplace_back(arr[r--]);
        else
            ans.emplace_back(arr[l++]);
    }
    return ans;
}

int main()
{
    vector<int> arr = {1,2,3,4,5};
    int k = 2;  //[5,1]

    arr = {1,1,3,5,5}, k = 2;   //[5,5]

    for(auto a : getStrongest(arr,k))
    {
        printf("%d ",a);
    }

    printf("\n");

    return 0;
}