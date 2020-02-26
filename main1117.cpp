//1117. H2O 生成
#include <cstdio>
#include <functional>
#include <thread>

using namespace std;

//思路：还是一样的使用条件变量，信号量可能更契合
class H2O {
public:
    H2O() {
        mark = 0;   
    }

    void hydrogen(function<void()> releaseHydrogen) {
        
        unique_lock<mutex> lk(mt);
        while(mark == 2)
        {
            cv1.wait(lk);
        }

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        ++mark;
        if(mark == 1)
        {
            cv1.notify_one();
        }
        else 
        {
            cv2.notify_one();
        }

    }

    void oxygen(function<void()> releaseOxygen) {
        
        unique_lock<mutex> lk(mt); 
        while(mark != 2)
        {
            cv2.wait(lk);
        }
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        mark = 0;
        cv1.notify_one();
    }

private:
    condition_variable cv1;
    condition_variable cv2;
    mutex mt;
    int mark;
};

int main()
{
    H2O h2o;
    string input = "HHHHOO";
    for(int i=0;i<input.size();++i)
    {
        if(input[i]=='H')
        {
            thread th([&h2o](){
                h2o.hydrogen([](){
                    printf("H");
                });
            });
            th.detach();
        }
        else
        {
            thread th([&h2o](){
                h2o.oxygen([](){
                    printf("O");
                });
            });
            th.detach();
        }
    }

    return 0;
}