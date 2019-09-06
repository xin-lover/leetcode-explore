//leetcode 870. 优势洗牌

#include <cstdio>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

vector<int> advantageCount(vector<int>& A, vector<int>& B) {
    //思路：一种是对于B中的数我们都选取刚好能大于它的数
    //这样的化我们对A排列，然后二分查找

    //优化的思路：二分查找比较快，但因为后面查找可用的数时是线性的
    //所以一开始可以对B复制一份，然后排序，这样对于B中的数，我们记录A中刚好大于它的数
    //这一步的复杂度是O(N),所以总的复杂度就是排序的复杂度

    sort(A.begin(),A.end());

    vector<bool> flags(A.size(),false);
    vector<int> res;
    for(int i=0;i<B.size();++i)
    {
        int left=0,right=A.size()-1;
        while(left < right)
        {
            int mid = left+(right - left) / 2;
            if(A[mid] <= B[i])
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
        }

        if(A[right] > B[i])
        {
            while(right < A.size() && flags[right])
            {
                ++right;
            }
        }

        if(right >= A.size() || A[right] <= B[i])
        {
            right = 0;
            while(right<A.size() && flags[right])
            {
                ++right;
            }
        }

        flags[right] = true;
        res.push_back(A[right]);
    }

    return res;
}

//性能一般
vector<int> advantageCount2(vector<int>& A, vector<int>& B) {

    vector<int> Bclone;
    copy(B.begin(),B.end(),back_inserter(Bclone));

    sort(A.begin(),A.end());
    sort(Bclone.begin(),Bclone.end());

    unordered_map<int,queue<int>> um;
    vector<int> remains;

    int k=0;
    for(int j=0;j<A.size();++j)
    {
        if(A[j] > Bclone[k])
        {
            um[Bclone[k]].push(A[j]);
            ++k;
        }
        else
        {
            remains.push_back(A[j]);
        }

    }

    vector<int> res(A.size());
    int j = 0;
    for(int i=0;i<res.size();++i)
    {
        if(um.find(B[i]) != um.end() && !um[B[i]].empty())
        {
            res[i] = um[B[i]].front();
            um[B[i]].pop();
        }
        else
        {
            res[i] = remains[j++];
        }
        
    }

    return res;

}

int main()
{
    vector<int> A = {2,7,11,15};
    vector<int> B = {1,10,4,11};

    // A = {12,24,8,32};
    // B = {13,25,32,11};

    // A = {2,0,4,1,2};
    // B = {1,3,0,0,2};

    vector<int> c = advantageCount2(A,B);
    for(int a : c)
    {
        printf("%d ",a);
    }
    printf("\n");

    return 0;
}