//630. 课程表 III

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

//回溯超时，很明显
void backtrace(vector<vector<int>>& courses,int index,int nextStart,int curCount,int& maxCount)
{
    if(index >= courses.size())
    {
        return;
    }

    if(nextStart + courses[index][0] <= courses[index][1])
    {
        maxCount = max(maxCount,curCount+1);
        backtrace(courses,index+1, nextStart+courses[index][0],curCount+1,maxCount);
    }

    backtrace(courses,index+1, nextStart,curCount,maxCount);
}

int scheduleCourse(vector<vector<int>>& courses) {
    //思路：类似工程安排问题，主要就是有个课程关闭会导致某些课程修不到的
    //贪心策略，优先选择可以早结束的课程，因为这样我们就可以有更多的选择
    //但这里的问题是可能最开始选择的路线不一定是最优的，所以可以允许回退
    //最多修n个，所以可以记录修k个时的最优选择，这样对新的课程看是否可以添加到可能的路线中，从而形成最优解
    //这样不是最优的，也就是需要优化路线

    if(courses.empty())
    {
        return 0;
    }

    sort(courses.begin(),courses.end(),[](vector<int>& a, vector<int>& b)
    {
        return a[1] < b[1];
    });

    for(int i=0;i<courses.size();++i)
    {
        printf("%d %d\n",courses[i][0],courses[i][1]);
    }

    int lastCourse=-1;
    int res = 0;
    int lastEnd = 0;
    for(int i=0;i<courses.size();++i)
    {
        printf("%d %d %d\n",lastEnd,courses[i][0],courses[i][1]);
        if(lastEnd + courses[i][0] <= courses[i][1])
        {
            ++res;
            printf("i:%d\n",i);
            lastEnd += courses[i][0];
            lastCourse = i;
        }
        else if(lastCourse >=0 && lastEnd - courses[lastCourse][0] + courses[i][0] < lastEnd)
        {
            lastEnd = lastEnd - courses[lastCourse][0] + courses[i][0];
            lastCourse = i;
        }
    }

    return res;
}   

int scheduleCourse2(vector<vector<int>>& courses) {
    //思路：用动归，排序之后，课程只有两种选择，所以用两个数组
    //一个表示修当前课程时的最大值，一个是不修当前课程的最大值

    if(courses.empty())
    {
        return 0;
    }

    sort(courses.begin(),courses.end(),[](vector<int>& a, vector<int>& b)
    {
        return a[1] < b[1];
    });
    

      priority_queue<int> pq;
    int lastEnd = 0;
    for(int i=0;i<courses.size();++i)
    {
        if(lastEnd + courses[i][0] <= courses[i][1])
        {
            pq.push(courses[i][0]);
            lastEnd += courses[i][0];
        }
        else
        {
            if(!pq.empty())
            {
                int mx = pq.top();
                if(courses[i][0] < mx)
                {
                    pq.pop();
                    pq.push(courses[i][0]);
                    lastEnd -= (mx - courses[i][0]);
                }
            }

        }
        
    }
    
    return pq.size();
}

int main()
{
    vector<vector<int>> courses = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}}; //3
    // courses = {{1,2},{2,3}}; //2
    // courses = {{5,5},{4,6},{2,6}}; //2
    courses = {{7,17},{3,12},{10,20},{9,10},{5,20},{10,19},{4,18}};//4
    courses = {{100,2},{32,50}};
    printf("%d\n",scheduleCourse2(courses));
    return 0;
}