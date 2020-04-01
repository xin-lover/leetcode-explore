//交替打印字符串

#include <cstdio>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

//思路：还是同步问题，因为一个现场只管一种情况，所以在除数递增前要同步，不然输出就乱序了
//使用条件变量
class FizzBuzz {
private:
    int n;

    condition_variable cv1;
    // condition_variable cv2;
    // condition_variable cv3;
    // condition_variable cv4;
    mutex mt;
    int flag = 1;

public:
    int tmp_;

    FizzBuzz(int n) {
        this->n = n;
        tmp_ = 1;
        flag = 3;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        
        while(tmp_ != n)
        {
            unique_lock<mutex> lk(mt);
            while(flag != 1)
            {
                cv1.wait(lk);
            }

            if(tmp_ > n)
            {
                break;
            }

            if(tmp_ % 3 == 0)
            {
                printFizz();
                ++tmp_;
                flag = 3;
            }
            else
            {
                flag = 2;
            }
            cv1.notify_all();   
        }

        flag = 2;
        cv1.notify_all();

    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {

        while(tmp_ != n)
        {
            unique_lock<mutex> lk(mt);
            while(flag != 2)
            {
                cv1.wait(lk);
            }

            if( tmp_ > n)
            {
                break;
            }
            
            if(tmp_ % 5 == 0)
            {
                printBuzz();
                ++tmp_;
                flag = 3;
            }
            else
            {
                flag = 4;
            }
            cv1.notify_all();
        }
        flag=4;
        cv1.notify_all();
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {

        // {
        //     lock_guard<mutex> guard(mt);
        //     flag =3;

        // }
        while(tmp_ != n)
        {
            unique_lock<mutex> lk(mt);
            while(flag != 3)
            {
                cv1.wait(lk);
            }

            if(tmp_> n)
            {
                break;
            }

            if(tmp_ % 3 == 0 && tmp_ % 5 == 0)
            {
                printFizzBuzz();
                ++tmp_;
            }
            else
            {
                flag = 1;
            }
            cv1.notify_all();
        }
        flag = 1;
        cv1.notify_all();

    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(tmp_!=n)
        {
            unique_lock<mutex> lk(mt);
            while(flag != 4)
            {
                cv1.wait(lk);
            }

            printNumber(tmp_);
            flag = 3;
            ++tmp_;
            cv1.notify_all(); 
        }

        cv1.notify_all();

    }
};

std::condition_variable cv;
std::mutex cv_m; // 此互斥用于三个目的：
                 // 1) 同步到 i 的访问
                 // 2) 同步到 std::cerr 的访问
                 // 3) 为条件变量 cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, []{return i == 1;});
    std::cerr << "...finished waiting. i == 1\n";
}
 
void signals()
{
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // {
    //     std::lock_guard<std::mutex> lk(cv_m);
    //     std::cerr << "Notifying...\n";
    // }
    // cv.notify_all();
 
    // std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}

// class FizzBuzz {
// private:
//     int n;
//     int i;
//     std::mutex mtx;
//     std::condition_variable cv;

// public:
//     FizzBuzz(int n) {
//         this->n = n;
//         i = 1;
//     }

//     // printFizz() outputs "fizz".
//     void fizz(std::function<void()> printFizz) {
//         while (i <= n) {
//             std::unique_lock<std::mutex> lock(mtx);
//             cv.wait(lock, [this]() { return (i % 3 == 0 && i % 5 != 0) || (i > n); });
//             if (i <= n) {
//                 printFizz();
//                 ++i;
//             }
//             cv.notify_all();
//         }
//     }

//     // printBuzz() outputs "buzz".
//     void buzz(std::function<void()> printBuzz) {
//         while (i <= n) {
//             std::unique_lock<std::mutex> lock(mtx);
//             cv.wait(lock, [this]() { return (i % 3 != 0 && i % 5 == 0) || (i > n); });
//             if (i <= n) {
//                 printBuzz();
//                 ++i;
//             }
//             cv.notify_all();
//         }
//     }

//     // printFizzBuzz() outputs "fizzbuzz".
//     void fizzbuzz(std::function<void()> printFizzBuzz) {
//         while (i <= n) {
//             std::unique_lock<std::mutex> lock(mtx);
//             cv.wait(lock, [this]() { return (i % 3 == 0 && i % 5 == 0) || (i > n); });
//             if (i <= n) {
//                 printFizzBuzz();
//                 ++i;
//             }
//             cv.notify_all();
//         }
//     }

//     // printNumber(x) outputs "x", where x is an integer.
//     void number(std::function<void(int)> printNumber) {
//         while (i <= n) {
//             std::unique_lock<std::mutex> lock(mtx);
//             cv.wait(lock, [this]() { return (i % 3 != 0 && i % 5 != 0) || (i > n); });
//             if (i <= n) {
//                 printNumber(i);
//                 ++i;
//             }
//             cv.notify_all();
//         }
//     }
// };


int main()
{
    //     std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    // t1.join(); 
    // t2.join(); 
    // t3.join();
    // t4.join();

    // return 0;
    FizzBuzz fb(15);
    thread th1([&fb](){
        fb.fizz([](){
            printf("fizz,");
        });
    });
    thread th2([&fb](){
        fb.buzz([](){
            printf("buzz,");
        });

    });
    thread th3([&fb](){

        fb.fizzbuzz([](){
            printf("fizzbuzz,");
        });
    });
    thread th4([&fb](){

        fb.number([](int a){
            printf("%d,",a);
        });
    });

    th3.join();
    th1.join();
    th2.join();
    th4.join();

    return 0;
}