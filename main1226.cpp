//1226. 哲学家进餐

#include <cstdio>
#include <functional>
#include <thread>
#include <vector>

using namespace std;

class DiningPhilosophers {
public:
    condition_variable cv_;
    mutex mt_;

    vector<bool> flags_;
    const int count_ = 5;
    
    DiningPhilosophers() {
        flags_.resize(count_,true);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        //思路：需要考虑的是如何调用？根据题意，哲学家不是在吃就是在想着吃，翻译到程序也就是wantsToEat一直在调用
        //而DiningPhilosophers这个类应该是只有一个对象，那么其实我们的任务就是避免死锁了
        //每个人吃一次，需要5个步骤，而编号是0～5，每次都要拿到左右两个叉子才能吃面
        //因为很容易陷入没人拿一个叉子的情况，所以需要要定下规则，要不同时拿起两个叉子，不要不拿，否则不好管理；
        //

        int left = philosopher;
        int right = (philosopher + 1) % count_;

        unique_lock<mutex> lk(mt_);
        while(!flags_[left] || !flags_[right])
        {
            cv_.wait(lk);
        }

        flags_[left] = false;
        flags_[right] = true;
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        flags_[left]= true;
        flags_[right] = true;

        cv_.notify_all();

    }
};


// class Semaphore {
// public:
//   Semaphore(int count = 0) : count_(count) {
//   }
    
//   void Set(int count){
//       count_ = count;
//   }
    
//   void Signal() {
//     std::unique_lock<std::mutex> lock(mutex_);
//     ++count_;
//     cv_.notify_one();
//   }

//   void Wait() {
//     std::unique_lock<std::mutex> lock(mutex_);
//     while(count_ <= 0){
//         cv_.wait(lock);
//     }
//     --count_;
//   }

// private:
//   std::mutex mutex_;
//   std::condition_variable cv_;
//   int count_;
// };

// class DiningPhilosophers {
// public:
//     DiningPhilosophers() {
//         guid.Set(4);
//     }
    
//     void wantsToEat(int philosopher,
//                     function<void()> pickLeftFork,
//                     function<void()> pickRightFork,
//                     function<void()> eat,
//                     function<void()> putLeftFork,
//                     function<void()> putRightFork) {
//         int l = philosopher;
//         int r = (philosopher+1)%5;
//         guid.Wait();        
        
//         lock[l].lock();
//         lock[r].lock();
//         pickLeftFork();
//         pickRightFork();
//         eat();
//         putRightFork();
//         putLeftFork();
//         lock[r].unlock();
//         lock[l].unlock();
        
//         guid.Signal();
//     }
// private:
//     std::mutex lock[5];
//     Semaphore guid;
// };

int main()
{
    DiningPhilosophers dp;
    for(int i=0;i<5;++i)
    {
        thread th([i,&dp](){
            dp.wantsToEat(i,[]()
            {
                printf("pick left\n");
            },
            []()
            {
                printf("pick right\n");
            },
            []()
            {
                printf("eat\n");
            },
            []()
            {
                printf("put left\n");
            },
            []()
            {
                printf("put right\n");
            });
        });

        th.join();
    }

    return 0;
}