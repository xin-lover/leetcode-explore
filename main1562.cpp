//1562. 查找大小为 M 的最新分组

#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int findLatestStep(vector<int>& arr, int m) {
    //思路：使用map记录一个连续1的分组情况，形式是{start,next}
    //start是分组的第一个1开始的位置，next是本分组下一个1预期的位置
    //当一个分组的next和某个分组的start重合，则可以合并
    
    int res = -1;
    int count = 0;
    unordered_map<int,int> um_12; //记录{next_left,next_right}
    unordered_map<int,int> um_21;  //记录{next_right,next_left}
    for(int i=0;i<arr.size();++i)
    {
        int cur = arr[i];
        if(um_12.find(cur) != um_12.end())
        {
            if(um_12[cur] - cur - 1 == m)
            {
                --count;
            }
            //合并
            if(um_21.find(cur) != um_21.end())
            {
                if(cur - um_21[cur]-1 == m)
                {
                    --count;
                }
                int start = um_21[cur];
                int end = um_12[cur];

                um_12[start] = end;
                um_21[end] = start;

                um_12.erase(cur);
                um_21.erase(cur);

                if(end - start - 1 == m)
                {
                    ++count;
                }
            }
            else
            {
                int end = um_12[cur];
                um_12[cur-1] = end;
                um_21[end] = cur-1;

                um_12.erase(cur);

                if(end - cur == m)
                {
                    ++count;
                }
            }
        }
        else if(um_21.find(cur) != um_21.end())
        {
            if(cur - um_21[cur] - 1 == m)
            {
                --count;
            }
            //合并
            if(um_12.find(cur) != um_12.end())
            {
                if(um_12[cur] - cur - 1 == m)
                {
                    --count;
                }
                int start = um_21[cur];
                int end = um_12[cur];

                um_12[start] = end;
                um_21[end] = start;

                um_12.erase(cur);
                um_21.erase(cur);
                
                if(end - start - 1 == m)
                {
                    ++count;
                }
            }
            else
            {
                int start = um_21[cur];

                um_21[cur+1] = start;
                um_12[start] = cur+1;

                um_21.erase(cur);

                if(cur - start == m)
                {
                    ++count;
                }
            }
        }
        else
        {
            um_12[cur-1] = cur+1;
            um_21[cur+1] = cur-1;

            if(m == 1)
            {
                ++count;
            }
        }
        
        if(count > 0)
        {
            res = i+1;
        }
    }

    return res;
}

int findLatestStep(vector<int>& arr, int m) {

int main()
{
    vector<int> arr = {3,5,1,2,4};
    int m = 1; //4

    arr = {3,1,5,4,2}, m = 2;   //-1

    arr = {2,1}, m = 2; //2

    printf("%d\n",findLatestStep(arr,m));

    return 0;
}

