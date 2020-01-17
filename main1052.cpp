//1052. 爱生气的书店老板

#include <cstdio>
#include <vector>

using namespace std;

int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
    //思路：X相当于固定窗口，我们滑动这个窗口即可

    int res = 0;
    for(int i=0;i<customers.size();++i)
    {
        res += grumpy[i]==1 ? 0 : customers[i]; 
    }

    int add = 0;
    for(int i=0;i<X;++i)
    {
        add += (grumpy[i]==0 ? 0 : customers[i]);
    }
    printf("add:%d\n",add);

    int tmp = add;
    for(int i=1;i+X-1<customers.size();++i)
    {
        tmp -= (grumpy[i-1]==0 ? 0 : customers[i-1]);
        tmp += (grumpy[i+X-1] == 0 ? 0 : customers[i+X-1]);
        printf("tmp:%d -=:%d +=:%d\n",tmp,(grumpy[i]==0 ? 0 : customers[i]),(grumpy[i+X-1] == 0 ? 0 : customers[i+X-1]));
        add = max(tmp,add);
    }

    return res+add;
}

int main()
{
    vector<int> customers = {1,0,1,2,1,1,7,5}, grumpy = {0,1,0,1,0,1,0,1};
    int X = 3; //16

    customers = {1};
    grumpy = {0};
    X = 1; //1

    printf("%d\n",maxSatisfied(customers,grumpy,X));
    return 0;
}

