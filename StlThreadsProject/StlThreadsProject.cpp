#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

int amount{};

mutex m;

void inc(int count)
{
    for (int i = 0; i < count; i++)
    {
        lock_guard<mutex> lock(m);
        cout << this_thread::get_id() << " " << ++amount << "\n";
    }
        
}

void func()
{
    for (int i = 0; i < 100; i++)
    {
        cout << this_thread::get_id() << " " << i << "\n";
        this_thread::sleep_for(100ms);
    }
}

void sum100(promise<int> prom_pes)
{
    cout << "current thread id = " << this_thread::get_id() << "\n";

    int sum{};
    for (int i = 1; i <= 1000; i++)
        sum += i;

    this_thread::sleep_for(100ms);
    prom_pes.set_value(sum);
}

int main()
{
    //thread th1(inc);
    //thread th2(inc);
    ////cout << "main thread\n";
    //
    ///*for (int i = 0; i < 50; i++)
    //{
    //    cout << this_thread::get_id() << " " << i << "\n";
    //    this_thread::sleep_for(100ms);
    //}*/

    //th1.join();
    //th2.join();

    /*jthread th1(inc, 100);
    jthread th2(inc, 200);

    cout << "amount = " << amount << "\n";*/

    cout << "main thread id = " << this_thread::get_id() << "\n";

    /*future<int> result = async(sum100);

    jthread th2(inc, 200);

    result.wait();
    cout << "result = " << result.get() << "\n";*/

    promise<int> promise_result;
    future<int> future_result = promise_result.get_future();

    jthread th2(inc, 200);

    jthread th3(sum100, move(promise_result));
    future_result.wait();
    cout << "result = " << future_result.get() << "\n";
    
}
