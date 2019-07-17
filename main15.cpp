#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {1,3,7,2,8};
    sort(v.rbegin(),v.rend());

    for(auto a : v)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}