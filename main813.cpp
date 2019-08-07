//leetcode 813. 最大平均值和的分组

#include <cstdio>
#include <vector>

using namespace std;


double largestSumOfAverages(vector<int>& A, int K) {
    //思路：分为K个连续子数组，暴力做法就把左右分组情况都求一遍，不现实
    //假设A只有3个元素，这只有一种分法，现在添加一个元素，则很明显，需要把它添加到最小值的那个分组
    //其它的同理,但要注意，如果新加入的数比较大，则需要换一下，把最小的组拿出来作为添加的组
    //也就是原来是k个分组，新的数也是一个分组，如果新分组比原来的最小分组大，则交换它们
    //这里有个问题就是{1,2,3} {4} 加入5时应该时{1,2,3,4} {5} 而不是{1,2,3} {4,5}
    //所以我们判断最小分组不是以和为标准，而是平均值
    //这个想法先行了一步，题目的意思是连续数组，也就是A中的元素不能随意分组，必须还是原来的顺序

    if(A.size() < K)
    {
        return 0.0;
    }

    vector<vector<int>> ay;
    vector<double> avgs;
    for(int i=0;i<K;++i)
    {
        ay.push_back({A[i]});
        avgs.push_back(A[i]);
    }

    for(int i=K;i<A.size();++i)
    {
        //找最小值
        int min_index = 0;
        int second_min_index = -1;
        for(int j=1;j<avgs.size();++j)
        {
            if(avgs[j] < avgs[min_index])
            {
                second_min_index = min_index;
                min_index = j;
            }
            else if(second_min_index == -1 || avgs[j] < avgs[second_min_index])
            {
                second_min_index = j;
            }
        }

        if(second_min_index == -1)
        {
            ay[min_index].push_back(A[i]);
            int sz = ay[min_index].size();
            avgs[min_index] = (avgs[min_index] * (sz-1) + A[i]) / sz;
            continue;
        }

        if(A[i] < avgs[second_min_index])
        {
            ay[min_index].push_back(A[i]);
            int sz = ay[min_index].size();
            avgs[min_index] = (avgs[min_index] * (sz-1) + A[i]) / sz;
        }
        else
        {
            vector<int> new_ay = {A[i]};
            double avg = (avgs[min_index] * ay[min_index].size() +avgs[second_min_index] * ay[second_min_index].size()) / (ay[min_index].size() + ay[second_min_index].size());
            swap(ay[min_index],new_ay);
            avgs[min_index] = A[i];

            ay[second_min_index].insert(ay[second_min_index].end(),new_ay.begin(),new_ay.end());
            avgs[second_min_index]=avg;
        }
    }

    double res = 0.0;
    for(int i=0;i<avgs.size();++i)
    {
        res += avgs[i];
    }

    return res;

}

double largestSumOfAverages2(vector<int>& A, int K) {
    //思路：借鉴上一个思路，还是先分为K组，同时记录平均值
    //然后找相邻的平均值和最小的为合并项
    //隐含了贪心算法，不对

    if(A.size() < K)
    {
        return 0.0;
    }

    if(K == 1)
    {
        double sum = 0;
        for(int i=0;i<A.size();++i)
        {
            sum += A[i];
        }

        return sum / A.size();
    }

    vector<int> ay;
    vector<double> avgs;
    double res=0.0;
    for(int i=0;i<K;++i)
    {
        ay.push_back(1);
        avgs.push_back(A[i]);
        res += A[i];
    }

    for(int i=K;i<A.size();++i)
    {
        //找合并项
        int merge_index = 0;
        int tmp = res - avgs[merge_index]*ay[merge_index] - avgs[merge_index+1]*ay[merge_index+1] + (avgs[merge_index]*ay[merge_index] + avgs[merge_index+1] * ay[merge_index+1]) / (ay[merge_index] + ay[merge_index+1]) + A[i];
        for(int j=1;j<avgs.size()-1;++j)
        {
            int cur = res - avgs[j]*ay[j] - avgs[j+1]*ay[j+1] + (avgs[j]*ay[j] + avgs[j+1]*ay[j+1]) / (ay[j] + ay[j+1]) + A[i];
            if(cur > tmp)
            {
                merge_index = j;
                tmp = cur;
            }   
        }

        printf("A[i]:%d min_index:%d\n",A[i],merge_index);
        printf("back:%f\n",avgs.back());
        if(res - avgs.back() * ay.back() + (avgs.back()*ay.back() + A[i]) / (ay.back()+1.0) < tmp)
        {
            double newavg = (avgs[merge_index] * ay[merge_index] + avgs[merge_index+1] * ay[merge_index+1]) / (ay[merge_index] + ay[merge_index+1]);
            printf("newavg:%f\n",newavg);
            avgs[merge_index] = newavg;
            ay[merge_index] = ay[merge_index] + ay[merge_index+1];

            for(int i=merge_index+1;i<avgs.size()-1;++i)
            {
                avgs[i] = avgs[i+1];
                ay[i] = ay[i+1];
            }

            ay.back() = 1;
            avgs.back() = A[i];

            res = tmp;
        }
        else
        {
            printf("get\n");
            res -= avgs.back();
            avgs.back() = (avgs.back() * ay.back() + A[i]) / (ay.back() + 1);
            ay.back()+=1;

            printf("dd:%f\n",avgs.back());
            res += avgs.back();
        }
    }

    return res;
}

double largestSumOfAverages3(vector<int>& A, int K) {
    //动归：dp[i][k]表示前i个数的分为k组的最大平均值
    //则dp[i][k] = max{dp[j][k-1] + A[j+1]+......+A[i]/(i-j)}

    vector<vector<double>> dp(A.size()+1,vector<double>(K+1));
    vector<double> sums(A.size()+1,0);
    for(int i=1;i<=A.size();++i)
    {
        sums[i] = sums[i-1]+A[i-1];
        dp[i][1] = sums[i] / i;
    }

    for(int i=1;i<=A.size();++i)
    {
        for(int k=2;k<=K;++k)
        {
            for(int j=0;j<i;++j)
            {
                dp[i][k] = max(dp[i][k],dp[j][k-1] + (sums[i]-sums[j])/static_cast<double>(i-j));
            }
        }
    }

    return dp[A.size()][K];
}
int main()
{
    vector<int> A = {1,2,3,4,5};
    A = {9,1,2,3,9};
    printf("%f\n",largestSumOfAverages3(A,3));
    A = {1,2};
    // printf("%f\n",largestSumOfAverages2(A,2));
    // A = {1,2,3,4,5,6,7};
    // printf("%f\n",largestSumOfAverages(A,4));
    A = {4,1,7,5,6,2,3};
    printf("%f\n",largestSumOfAverages3(A,4));
    // A = {3324,8299,5545,6172,5817};
    // A = {5722,6172,5817};
    // printf("%f\n",(A[0]+A[1]+A[2])/3.0+(A[3]+A[4]) /2.0);
    // printf("%f\n",largestSumOfAverages3(A,2));

    return 0;
}