#include <iostream>
#include <thread>
#include <mutex>

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

    jthread th1(inc, 100);
    jthread th2(inc, 200);

    cout << "amount = " << amount << "\n";
}
