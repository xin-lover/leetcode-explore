//699. 掉落的方块

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> fallingSquares(vector<vector<int>>& positions) {
    //思路：相当于区间，区间求交，但这些区间是由高度的，要根据高度来确定哪个优先求交
    //没什么好思路，先从做简单的开始 

    vector<int> res(positions.size(),0);
    if(positions.empty())
    {
        return res;
    }

    vector<int> heights(positions.size(),0);
    res[0] = positions[0][1];
    heights[0] = res[0];
    int maxheight = res[0];
    for(int i=1;i<positions.size();++i)
    {
        int left = positions[i][0],right = positions[i][0] + positions[i][1];
        int t =positions[i][1];
        for(int j=0;j<i;++j)
        {
            if((left>=positions[j][0] && left < positions[j][0]+positions[j][1]) || (right > positions[j][0] && right<=positions[j][0]+positions[j][1])
                || (positions[j][0] >=left && positions[j][0]+positions[j][1]<right) || (left<positions[j][0]+positions[j][1] && positions[j][0]+positions[j][1]<=right))
            {
                t = max(t,heights[j]+positions[i][1]);
            }
        }

        heights[i] =t;
        maxheight = max(maxheight,t);
        res[i] = maxheight;
    }

    return res;    
}

// 方块（平方根）分解
// 在坐标轴是上执行 update 和 query 操作之前，先将长度为 WW 的坐标轴分为 \sqrt{W} 
// W
// ​	
//   个块。

// 每次方块掉落时，不仅更新方块所在坐标区间每个位置的高度，还更新方块数组 blocks，其中 blocks[i] 表示第 ii 个块，共 B = \lfloor \sqrt{W} \rfloorB=⌊ 
// W
// ​	
//  ⌋ 个位置的高度，即 heights[B*i], heights[B*i + 1], ..., heights[B*i + B-1]。
// class Solution {
//     int[] heights;
//     int[] blocks;
//     int[] blocks_read;
//     int B;

//     public int query(int left, int right) {
//         int ans = 0;
//         while (left % B > 0 && left <= right) {
//             ans = Math.max(ans, heights[left]);
//             ans = Math.max(ans, blocks[left / B]);
//             left++;
//         }
//         while (right % B != B - 1 && left <= right) {
//             ans = Math.max(ans, heights[right]);
//             ans = Math.max(ans, blocks[right / B]);
//             right--;
//         }
//         while (left <= right) {
//             ans = Math.max(ans, blocks[left / B]);
//             ans = Math.max(ans, blocks_read[left / B]);
//             left += B;
//         }
//         return ans;
//     }

//     public void update(int left, int right, int h) {
//         while (left % B > 0 && left <= right) {
//             heights[left] = Math.max(heights[left], h);
//             blocks_read[left / B] = Math.max(blocks_read[left / B], h);
//             left++;
//         }
//         while (right % B != B - 1 && left <= right) {
//             heights[right] = Math.max(heights[right], h);
//             blocks_read[right / B] = Math.max(blocks_read[right / B], h);
//             right--;
//         }
//         while (left <= right) {
//             blocks[left / B] = Math.max(blocks[left / B], h);
//             left += B;
//         }
//     }

//     public List<Integer> fallingSquares(int[][] positions) {
//         //Coordinate Compression
//         //HashMap<Integer, Integer> index = ...;
//         //int t = ...;

//         heights = new int[t];
//         B = (int) Math.sqrt(t);
//         blocks = new int[B+2];
//         blocks_read = new int[B+2];

//         int best = 0;
//         List<Integer> ans = new ArrayList();

//         for (int[] pos: positions) {
//             int L = index.get(pos[0]);
//             int R = index.get(pos[0] + pos[1] - 1);
//             int h = query(L, R) + pos[1];
//             update(L, R, h);
//             best = Math.max(best, h);
//             ans.add(best);
//         }
//         return ans;
//     }
// }

//线段树+懒惰传播
// class Solution {
//     public List<Integer> fallingSquares(int[][] positions) {
//         //Coordinate Compression
//         //HashMap<Integer, Integer> index = ...;

//         SegmentTree tree = new SegmentTree(sortedCoords.size());
//         int best = 0;
//         List<Integer> ans = new ArrayList();

//         for (int[] pos: positions) {
//             int L = index.get(pos[0]);
//             int R = index.get(pos[0] + pos[1] - 1);
//             int h = tree.query(L, R) + pos[1];
//             tree.update(L, R, h);
//             best = Math.max(best, h);
//             ans.add(best);
//         }
//         return ans;
//     }
// }

// class SegmentTree {
//     int N, H;
//     int[] tree, lazy;

//     SegmentTree(int N) {
//         this.N = N;
//         H = 1;
//         while ((1 << H) < N) H++;
//         tree = new int[2 * N];
//         lazy = new int[N];
//     }

//     private void apply(int x, int val) {
//         tree[x] = Math.max(tree[x], val);
//         if (x < N) lazy[x] = Math.max(lazy[x], val);
//     }

//     private void pull(int x) {
//         while (x > 1) {
//             x >>= 1;
//             tree[x] = Math.max(tree[x * 2], tree[x * 2 + 1]);
//             tree[x] = Math.max(tree[x], lazy[x]);
//         }
//     }

//     private void push(int x) {
//         for (int h = H; h > 0; h--) {
//             int y = x >> h;
//             if (lazy[y] > 0) {
//                 apply(y * 2, lazy[y]);
//                 apply(y * 2 + 1, lazy[y]);
//                 lazy[y] = 0;
//             }
//         }
//     }

//     public void update(int L, int R, int h) {
//         L += N; R += N;
//         int L0 = L, R0 = R, ans = 0;
//         while (L <= R) {
//             if ((L & 1) == 1) apply(L++, h);
//             if ((R & 1) == 0) apply(R--, h);
//             L >>= 1; R >>= 1;
//         }
//         pull(L0); pull(R0);
//     }

//     public int query(int L, int R) {
//         L += N; R += N;
//         int ans = 0;
//         push(L); push(R);
//         while (L <= R) {
//             if ((L & 1) == 1) ans = Math.max(ans, tree[L++]);
//             if ((R & 1) == 0) ans = Math.max(ans, tree[R--]);
//             L >>= 1; R >>= 1;
//         }
//         return ans;
//     }
// }

// class Solution {
//     public static class SegmentTree {
//         private final int[][] positions;
//         private HashMap<Integer, Integer> truthToVirtual;//对应下标
//         private int MAXN;
//         private int[] change;
//         private int[] max;
//         private int N;//坐标总数

//         public SegmentTree(int[][] positions) {
//             this.positions = positions;
//             TreeSet<Integer> treeSet = new TreeSet<>();
//             for (int[] square : positions) {
//                 treeSet.add(square[0]);//左边界
//                 treeSet.add(square[0] + square[1] - 1);//右边界
//             }
//             //编号
//             N = 0;
//             truthToVirtual = new HashMap<>();
//             while (!treeSet.isEmpty()) {
//                 truthToVirtual.put(treeSet.pollFirst(), N++);
//             }
//             /*for(Map.Entry<Integer,Integer> i:truthToVirtual.entrySet()){
//                 System.out.println("truthIdx:"+i.getKey()+",virtualIdx"+i.getValue());
//             }*/
//             //初始化各表
//             MAXN = N << 2;
//             max = new int[MAXN];
//             change = new int[MAXN];
//         }

//         private List<Integer> fallingAll() {
//             List<Integer> ans = new ArrayList<>();
//             int l,r;
//             int max = 0;
//             for (int[] square : positions) {
//                 l = truthToVirtual.get(square[0]);
//                 r = truthToVirtual.get(square[0] + square[1] - 1);
//                 int height = query(l, r, 0, N - 1, 1)+square[1];
//                 ans.add(max = Math.max(height ,max));
//                 update(l,r,height,0,N-1,1);
//             }
//             return ans;
//         }


//         //从L...R区间下发任务
//         private void pushDown(int rt) {
//             int leftChild = rt << 1;
//             if (change[rt]!=0) {//下发更新任务
//                 change[leftChild] = change[rt];
//                 change[leftChild | 1] = change[rt];
//                 max[leftChild] = change[rt];
//                 max[leftChild | 1] = change[rt];
//                 change[rt] = 0;
//             }
//         }

//         private void pushUp(int rt, int lc, int rc) {
//             //当前区间最高高度肯定是两个子区间中更高那个
//             max[rt] = Math.max(max[lc], max[rc]);
//         }
//         private int query(int l,int r,int L,int R,int rt){
//             if (l <= L && r >= R) {
//                 return max[rt];
//             }
//             //懒不住，任务下发
//             int mid = L + ((R - L) >> 1);
//             pushDown(rt);
//             int ans = 0;
//             if (l <= mid) {
//                 ans = Math.max(query(l, r, L, mid, rt << 1),ans);
//             }
//             if (r > mid) {
//                 ans = Math.max(query(l, r,  mid + 1, R, rt << 1 | 1),ans);
//             }
//             pushUp(rt, rt << 1, rt << 1 | 1);
//             return ans;
//         }
//         private void update(int l,int r,int c,int L,int R,int rt){
//             if (l <= L && r >= R) {
//                 change[rt] = c;//懒住
//                 max[rt] = c;
//                 return;
//             }
//             //懒不住，任务下发
//             int mid = L + ((R - L) >> 1);
//             pushDown(rt);
//             if (l <= mid) {
//                 update(l, r, c, L, mid, rt << 1);
//             }
//             if (r > mid) {
//                 update(l, r, c, mid + 1, R, rt << 1 | 1);
//             }
//             pushUp(rt, rt << 1, rt << 1 | 1);
//         }
//     }
//     public List<Integer> fallingSquares(int[][] positions) {
//         return new SegmentTree(positions).fallingAll();
//     }
// }

int main()
{
    vector<vector<int>> positions = {{1, 2}, {2, 3}, {6, 1}}; //[2, 5, 5]
    positions = {{100, 100}, {200, 100}}; //[100, 100]
    positions = {{1,2},{1,3}};//[2,5]
    positions = {{6,1},{9,2},{2,4}}; //[1,2,4]
    positions = {{9,1},{6,5},{6,7}}; //[1,6,13]
    auto res = fallingSquares(positions); 

    for(auto a : res)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}