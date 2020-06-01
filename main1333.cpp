//1333. 餐厅过滤器

#include <cstdio>
#include <vector>

using namespace std;

vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {
    //思路：用最直观的思路吧

    vector<vector<int>> tmp;
    for(auto a : restaurants)
    {
        if(veganFriendly && !a[2])
        {
            continue;
        }

        if(a[3] > maxPrice || a[4] > maxDistance)
        {
            continue;
        }

        tmp.push_back({a[0],a[1]});
    }

    sort(tmp.begin(),tmp.end(),[](vector<int>& a,vector<int>& b)
    {
        if(a[1] == b[1])
        {
            return a[0] > b[0];
        }

        return a[1] > b[1];
    });

    vector<int> res;
    for(auto a : tmp)
    {
        res.push_back(a[0]);
    }

    return res;
}

int main()
{
    vector<vector<int>> restaurants = {{1,4,1,40,10},{2,8,0,50,5},{3,8,1,30,4},{4,10,0,10,3},{5,1,1,15,1}};
    int veganFriendly = 1, maxPrice = 50, maxDistance = 10; //3,1,5

    restaurants = {{1,4,1,40,10},{2,8,0,50,5},{3,8,1,30,4},{4,10,0,10,3},{5,1,1,15,1}};
    veganFriendly = 0, maxPrice = 50, maxDistance = 10;//[4,3,2,1,5]

    auto res = filterRestaurants(restaurants,veganFriendly,maxPrice,maxDistance);

    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}