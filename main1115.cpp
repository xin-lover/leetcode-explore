//1115. 交替打印FooBar

#include <cstdio>
#include <functional>
#include <mutex>
#include <thread>

using namespace std;

class FooBar {
private:
    int n;
    condition_variable cv1;
    condition_variable cv2;
    mutex mt1;
    mutex mt2;

    int mark;

public:
    FooBar(int n) {
        this->n = n;

        mark = 0;
        thread th1([this](){
            foo([]()
            {
                printf("foo");
            });
        });

        thread th2([this](){
            bar([]()
            {
                printf("bar");
            });
        });

        // cv1.notify_one();
        th1.join();
        th2.join();
    }

    void foo(function<void()> printFoo) {

        for (int i = 0; i < n; i++) {
            
            unique_lock<mutex> lk(mt1);
            while(!mark)
            {
                cv1.wait(lk);
            }
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            mark = 0;
            cv2.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        {
            lock_guard<mutex> guard(mt1);
            mark = 1;
            cv1.notify_one();
        }
        for (int i = 0; i < n; i++) {
            
            unique_lock<mutex> lk(mt1);
            while(mark)
            {
                cv2.wait(lk);
            }
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            cv1.notify_one();
            mark = 1;
        }
    }

    
};

int main()
{
    FooBar fb(3);

    return 0;
}