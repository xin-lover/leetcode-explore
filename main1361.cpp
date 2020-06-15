//1361. 验证二叉树

#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;

bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
    //思路：不用真的去构建，只需要总结几个规律即可
    //1.除根节点外每个节点只有一个入度
    //2.根节点只有一个
    //找到根节点后，遍历一次即可

    vector<int> in_degrees(n,0);
    for(int i=0;i<n;++i)
    {
        if(leftChild[i] > -1)
        {
            in_degrees[leftChild[i]]++;
        }
        
        if(rightChild[i] > -1)
        {
            in_degrees[rightChild[i]]++;
        }
    }

    int in_0_index = -1;
    for(int i=0;i<in_degrees.size();++i)
    {
        if(in_degrees[i] == 0)
        {
            if(in_0_index == -1)
            {
                in_0_index = i;
            }
            else
            {
                return false;
            }
        }
        else if(in_degrees[i] > 1)
        {
            return false;
        }
    }

    if(in_0_index == -1)
    {
        return false;
    }

    //遍历
    queue<int> qu;
    qu.push(in_0_index);
    set<int> visited;
    while(!qu.empty())
    {
        int p = qu.front();
        qu.pop();

        if(p == -1 || visited.find(p) != visited.end())
        {
            continue;
        }

        visited.insert(p);
        qu.push(leftChild[p]);
        qu.push(rightChild[p]);
    }

    return visited.size() == n;
}

bool validateBinaryTreeNodes2(int n, vector<int>& leftChild, vector<int>& rightChild) {
    //思路：其它规律：
    //1.如果只有一棵树，那么所有点的祖先是同一个
    //2.每个节点只有一个父节点，也就是入度为1

    vector<int> parents(n,-1);
    for(int i=0;i<n;++i)
    {
        if(leftChild[i] != -1)
        {
            if(parents[leftChild[i]] != -1)
            {
                return false;
            }
            parents[leftChild[i]] = i;
        }

        if(rightChild[i] != -1)
        {
            if(parents[rightChild[i]] != -1)
            {
                return false;
            }
            parents[rightChild[i]] = i;
        }

    }

    int root = -1;
    for(int i=0;i<n;++i)
    {
        int tmp = i;
        int loop = 0;
        while(parents[tmp] != -1)
        {
            ++loop;
            if(loop >= n)
            {
                return false;
            }
            tmp = parents[tmp];
        }

        if(root == -1)
        {
            root = tmp;
        }
        else if(tmp != root)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n = 4;
    vector<int> leftChild = {1,-1,3,-1}, rightChild = {2,-1,-1,-1}; //true
    n = 4, leftChild = {1,-1,3,-1}, rightChild = {2,3,-1,-1}; //false;
    // n = 2, leftChild = {1,0}, rightChild = {-1,-1}; //false;
    n = 4, leftChild = {1,2,0,-1},rightChild={-1,-1,-1,-1}; //false
    printf(validateBinaryTreeNodes2(n,leftChild,rightChild) ? "true\n" : "false\n");
    return 0;
}