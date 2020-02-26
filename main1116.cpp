//1116. 打印零与奇偶数

#include <cstdio>
#include <functional>
#include <thread>
#include <mutex>

using namespace std;


//思路：还是使用条件变量
class ZeroEvenOdd {
private:
    int n;

    int cur = 0;
    int mark = 0;

    mutex mt;
    condition_variable cv1;
    condition_variable cv2;
    condition_variable cv3;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {

        while(cur<n)
        {
            unique_lock<mutex> lk(mt);
            while(mark != 0)
            {
                cv1.wait(lk);
            }

            if(cur < n)
            {
                printNumber(0);
            }

            if(!(cur & 1))
            {
                mark = 1;
                cv2.notify_one();
            }
            else
            {
                mark = 2;
                cv3.notify_one();
            }

        }
    }

    void even(function<void(int)> printNumber) {
        while(cur < n)
        {
            unique_lock<mutex> lk(mt);
            while(mark != 2)
            {
                cv3.wait(lk);
            }
            if(cur < n)
            {
                printNumber(++cur);
                mark = 0;
                cv1.notify_one();
            }
        }
    }

    void odd(function<void(int)> printNumber) {
        while(cur < n)
        {
            unique_lock<mutex> lk(mt);
            while(mark != 1)
            {
                cv2.wait(lk);
            }
            if(cur < n)
            {
                printNumber(++cur); //这里其实处理不太好，因为++cur后的逻辑移动到了even上去了，也就是变化并没有封装到本线程中，用两个值会比较好
                mark = 0;
                cv1.notify_one();
            }

        }

    }
};

int main()
{
    ZeroEvenOdd zz(2);
    thread th1([&zz](){
        zz.zero([](int a){
            printf("%d",a);
        });
    });

    thread th2([&zz](){
        zz.odd([](int a){
            printf("%d",a);
        });
    });

    thread th3([&zz](){
        zz.even([](int a){
            printf("%d",a);
        });
    });

    th1.join();
    th2.join();
    th3.join();

        // lock_guard<mutex> guard(mt);
        // printf("Get\n");
        // cv1.notify_one();
    return 0;
}