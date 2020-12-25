//488. 祖玛游戏

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

// int backtrace2(const string& board,unordered_map<char,int>& hand)
// {
//     if(board.empty())
//     {
//         return 0;
//     }
//     int i=0;
//     int ans=6;
//     while(i < board.size())
//     {
//         int j=i+1;
//         while(j < board.size() and board[i] == board[j])
//         {
//             ++j;
//         }

//         int balls = 3 - (j-i);
//         if(hand[board[i]] >= balls)
//         {
//             balls = max(0,balls);
//             hand[board[i]] -= balls;
//             ans = min(ans,balls + backtrace2(board.substr(0,i) + board.substr(j,board.length()-j),hand));
//             hand[board[i]] += balls;
//         }

//         i = j;
//     }   

//     return ans;
// }

// //这种方式通不过“board: RRWWRRBBRR, hand: WB: ”，正确流程“RRWWRRBBRR->RRWWRRBBR(W)R->RRWWRRBB(B)R(W)R->RRWWRRR(W)R->RRWW(W)R->RRR->""
// //除非，流程修改为RRRR可以不消除，这个虽然可以得到正确结果，但与游戏的本意不符
// void backtrace(vector<pair<char,int>>& states,vector<bool>& flags, unordered_map<char,int>& hand, int index,int curRes,int& res)
// {
//     if(index >= states.size())
//     {
//         bool able = true;
//         unordered_map<char,int> tmpHand = hand;
//         for(int i=0;i<flags.size();++i)
//         {
//             if(flags[i])
//             {
//                 if(tmpHand[states[i].first] >= 3-states[i].second)
//                 {
//                     curRes += 3 - states[i].second;
//                     tmpHand[states[i].first] -= 3- states[i].second;
//                 }
//                 else
//                 {
//                     able = false;
//                     break;
//                 }
                
//             }
//         }
//         if(able)
//         {
//             printf("curRes:%d\n",curRes);
//             res = min(res,curRes);
//         }
//         return;
//     }
//     printf("--------- %d %c %d %d\n",index,states[index].first,states[index].second,curRes);

//     int tmp = states[index].second;
//     vector<int> ids;
//     for(int i=index-1;i>=0;--i)
//     {
//                 printf("wy:%d %s\n",i,flags[i] ? "true" : "false");
//         if(flags[i])
//         {
//             if(states[i].first != states[index].first)
//             {
//                 break;
//             }

//             tmp += states[i].second;
//             printf("i:%d\n",i);
//             ids.push_back(i);
//             if(tmp >= 3)
//             {
//                 for(auto j : ids)
//                 {
//                     flags[j] = false;
//                 }
//                 flags[index] = false;
//                 printf("get\n");
//                 backtrace(states,flags,hand,index+1,curRes,res);
//                 for(auto j : ids)
//                 {
//                     flags[j] = true;
//                 }
//                 flags[index] = true;
//                 break;
//             }
//         }
//     }

//     char ball = states[index].first;
//     if(tmp < 3 && tmp + hand[ball] >= 3)
//     {
//         for(auto j : ids)
//         {
//             flags[j] = false;
//         }
//         flags[index] = false;
//         hand[ball] -= 3-tmp;
//         printf(">=3 %c %d\n",states[index].first,states[index].second);
//         backtrace(states,flags,hand,index+1,curRes+3-tmp,res);
//         for(auto j : ids)
//         {
//             flags[j] = true;
//         }
//         flags[index] = true;
//         hand[ball] += 3-tmp;
//     }
//     else
//     {
//         printf("no index:%d %c %d\n",index,states[index].first,states[index].second);
//         backtrace(states,flags,hand,index+1,curRes,res);
//     }
// }

// string boom(string s, int i) {
//     if (s.empty()) return "";
//     int left = i, right = i;
//     while (left > 0 && s[left - 1] == s[left]) --left;
//     while (right < s.size() - 1 && s[right + 1] == s[right]) ++right;
//     if (right - left + 1 >= 3) {
//         s = s.substr(0, left) + s.substr(right + 1);
//         return boom(s, max(left - 1, 0));
//     }
//     return s;
// }
// void backtrace3(string board, map<char, int>& hand, int ball, int remain, int& min_ball) {
//     if (board.empty()) {
//         min_ball = min(min_ball, ball);
//         return;
//     }
//     if (ball >= min_ball || remain == 0 || min_ball == 0) return;
//     string s;
//     int left = -1;
//     for (int i = 0; i < board.size(); ++i) {
//         if (i == board.size() - 1 || board[i] != board[i + 1]) {
//             int lack = 3 - (i - left);
//             if (hand[board[i]] >= lack) {
//                 hand[board[i]] -= lack;
//                 s = board;
//                 s.insert(i, lack, board[i]);
//                 s = boom(s, i);
//                 backtrace3(s, hand, ball + lack, remain - lack, min_ball);
//                 hand[board[i]] += lack;
//             }
//             left = i;
//         }
//     }
// }

string boom(string s, int i) {
    if (s.empty()) return "";
    int left = i-1, right = i+1;
    while (left >= 0 && s[left] == s[i]) --left;
    while (right < s.size() && s[right] == s[i]) ++right;
    if (right - left - 1 >= 3) {
        s = s.substr(0, left+1) + s.substr(right);
        return boom(s, max(left, 0));
    }
    return s;
}

void dfs(const string& board, unordered_map<char, int>& hand,int usedCount,int& res){
    
    if(board.empty())
    {
        res = min(usedCount,res);
        return;
    }

    //计算接下来至少要的字符数量
    map<char, int> pBcount;
    for (const auto& pc : board) pBcount[pc]++;
    int nextAtLeastCount = 0;

    for (auto& p : pBcount) {
        if (p.second < 3) {
            nextAtLeastCount += 3 - p.second;
        }
        if ((3 - p.second) > hand[p.first]) //mhand的某个字符数量不够, 剪枝
            return;
    }
    if ((nextAtLeastCount + usedCount) >= res) {  //不可能再回溯出更小的消除路径了, 剪枝, 这是个关键剪枝: 如果已经得到了某个解, 当前再搜索下去不可能比它更小则停止此路线搜索!, 此处可以在相当浅的递归中return
        return;
    }

    //尝试每一个位置。。。。
    // int ret = INT_MAX;
    for(int i=0; i<board.size();++i){
        for(auto& it : hand)
        {
            if(it.second <= 0)
            {
                continue;
            }
            string newBoard = board;
            newBoard.insert(newBoard.begin()+i,it.first);
            newBoard = boom(newBoard,i);
            --it.second;
            dfs(newBoard,hand,usedCount+1,res);
            ++it.second;
        }
    }
}

int findMinStep(string board, string hand) {
    //思路：唯一方复杂性在于销掉一串连续的球后，前后的球又会连接到一起，这个时候可能会再次触发消除
    //所以问题就来了，如何判定某一串球是否该消除？
    //假设RaxxxRb，0<a<=b<3，其中xxx中没有R，假设消除xxx需要m个球，那么对于RaxxxRb,需要m+(a+b>=3 ?0 : 3-a-b)
    //我们记录同颜色球串上一次出现的位置，中间是没有这种颜色的球的
    //没有什么好的方案，先暴力解决,回溯

    // vector<pair<char,int>> states;
    // int start = 0;
    // for(int i=1;i<board.size();++i)
    // {
    //     if(board[i] != board[start])
    //     {
    //         states.push_back({board[start],i-start});
    //         start = i;
    //     }
    // }

    // states.push_back({board[start],(int)board.length()-start});

    // vector<bool> flags(states.size(),true);

    unordered_map<char,int> um;
    for(int i=0;i<hand.size();++i)
    {
        um[hand[i]]++;
    }

    // // //
    // // int res = INT_MAX;
    // // // for(int i=0;i<states.size();++i)
    // // {
    // //     backtrace(states,flags,um,0,0,res);
    // // }

    // // return res == INT_MAX ? -1 : res;

    // int res = backtrace2(board,um);
    // return res > 5 ? -1 :res;

    int res=INT_MAX;
    dfs(board,um,0,res);
    return res == INT_MAX ? -1 : res;

}



int main()
{
    string board = "WRRBBW", hand = "RB"; //-1
    // board = "WWRRBBWW", hand = "WRBRW"; //2
    // board = "G", hand = "GGGGG";    //2
    board = "RBYYBBRRB", hand = "YRBGB";    //3
    // board = "RRWWRRW", hand="RR";   //2
    // board = "W",hand = "W"; //-1
    // board = "WWGWGW", hand="GWBWR"; //3
    // board="WWBBWBBWW", hand="BB"; //-1
    // board = "RRWWRRBBRR", hand="WB"; //2
    printf("%d\n",findMinStep(board,hand)); 

    return 0;
}