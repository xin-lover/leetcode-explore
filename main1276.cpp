//1276. 不浪费原料的汉堡制作方案

#include <cstdio>
#include <vector>

using namespace std;

vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
    //思路：4+1，2+1，如果要最后甚于为0，那么tomato的数量必须大于cheese的数量
    //而这个又有点像鸡兔同笼问题，可以假设先制作小皇堡，即2+1，然后看剩余的tomato数量
    //来确定巨无霸的数量4+1

    int m = tomatoSlices;
    int n = cheeseSlices;
    if(m & 1)
    {
        return {};
    }
    if(m < n * 2 || m > n * 4)
    {
        return {};
    }

    int p = m - n * 2;
    int q = p / 2;

    return {q,n-q};
}

int main()
{
    int tomatoSlices = 16,cheeseSlices = 7;//1,6
    tomatoSlices = 17,cheeseSlices = 4; //[]
    tomatoSlices = 0, cheeseSlices = 0; //[0,0]
    // tomatoSlices = 2, cheeseSlices = 1; //[0,1]
    tomatoSlices= 2385088,cheeseSlices = 164763;//[]
    vector<int> res = numOfBurgers(tomatoSlices,cheeseSlices);
    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}