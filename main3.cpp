#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// int square(vector<int> states)
// {
//     int start = -1;
//     int mn = INT_MAX;
//     int area = 0;
//     for(int i=0;i<states.size();++i)
//     {
//         if(states[i] > 0)
//         {
//             if(start == -1)
//             {
//                 start = i;
//             }
            
//             if(mn > states[i])
//             {
//                 mn = states[i];
//             }
//         }
//         else
//         {
//             if(start != -1)
//             {
//                 int len = min(i-start,mn);
//                 area = max(area,len*len);

//                 start = -1;
//                 mn = INT_MAX;
//             }
//         }
//     }

//     if(start >= 0)
//     {
//         int sz = states.size();
//         int len = min(sz-start,mn);
//         area = max(area,len*len); 
//     }
    
//     return area;
// }

int square(vector<int> heights)
{
    int n = heights.size();
    int mx = 0;
    for(int i=0;i<n;++i)
    {
        if(heights[i] == 0)
        {
            continue;
        }

        int mn = heights[i];
        for(int j=1;j<heights[i] && i+j < n;++j)
        {
            if(heights[i+j] == 0)
            {
                int len = min(j,mn);
                mx = max(mx,len);
                i=i+j+1;
                break;
            }

            if(heights[i + j] < mn)
            {
                mn = heights[i+j];
                
            }
            int len = min(mn,j+1);
            mx = max(mx,len);

            if(i+j == n-1 && heights[i+j] >= heights[i])
            {
                int len = min(mn,n-i);
                mx = max(mx,len);
            }
        }
    }

    return mx * mx;
}

int main()
{
    vector<int> v = {3,3, 1, 3};
    printf("ddd:%d\n",square(v));
    v = {2,3,3,3};
    printf("ddd:%d\n",square(v));
    vector<vector<int>> m = {
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, },
{2, 0, 2, 2, 0, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, },
{3, 1, 3, 3, 1, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, },
{0, 2, 4, 4, 2, 4, 3, 0, 4, 4, 4, 0, 4, 4, 4, },
{1, 0, 0, 5, 3, 5, 4, 1, 5, 5, 5, 0, 5, 5, 5, },
{2, 1, 1, 6, 4, 6, 5, 2, 6, 6, 6, 1, 6, 6, 6, },
{3, 2, 2, 0, 5, 7, 6, 3, 7, 7, 7, 0, 7, 7, 7, },
{4, 3, 3, 1, 0, 0, 0, 4, 8, 8, 8, 1, 0, 8, 0, },
{5, 0, 4, 2, 0, 0, 0, 5, 9, 9, 9, 0, 1, 0, 1, },
{6, 0, 5, 3, 1, 1, 1, 6, 0, 10, 10, 1, 0, 1, 2, },
{7, 0, 6, 4, 2, 2, 2, 7, 1, 11, 11, 2, 1, 2, 3, },
{8, 1, 7, 0, 3, 3, 3, 8, 2, 12, 12, 3, 2, 3, 4, },
{9, 2, 8, 0, 0, 0, 4, 0, 3, 13, 13, 4, 3, 4, 5, },
{10, 3, 9, 1, 1, 1, 0, 1, 4, 14, 14, 5, 4, 5, 6, },
{11, 4, 10, 2, 2, 2, 1, 0, 5, 15, 15, 6, 5, 0, 7, },
    };

    for(auto a : m)
    {
        printf("%d\n",square(a));
    }
    // system("pause");
    return 0;
}