// compile using g++ as
// $ g++ Problem5.cpp -lpthread -o output
#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

int run_for = 20;
int n = 5;
int st[5] = {};
mutex Mutex;
void waitPhilosopher(int x)
{
    while (st[(x + 1) % 5] == 1 || st[(x) % 5] == 1)
        ;
}
void signalEat(int x)
{
    st[(x + 1) % 5] = 1;
    st[x] = 1;
}
void signalRelease(int x)
{
    st[(x + 1) % 5] = 0;
    st[x] = 0;
}
void philosopher(int x)
{
    while (run_for > 0)
    {
        Mutex.lock();
        cout << "Philosopher " << x + 1 << " wishes to eat\n";
        Mutex.unlock();
        waitPhilosopher(x);
        Mutex.lock();
        signalEat(x);
        cout << "Philosopher " << x + 1 << " is eating \n";
        Mutex.unlock();
        Mutex.lock();
        signalRelease(x);
        cout << "Philosopher " << x + 1 << " has now eaten and is thinking\n";
        Mutex.unlock();
        run_for--;
    }
}
void run_threads()
{
    thread t1(philosopher, 0);
    thread t2(philosopher, 1);
    thread t3(philosopher, 2);
    thread t4(philosopher, 3);
    thread t5(philosopher, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

int main()
{
    cout << "Dining Philosopher using Semaphores \n";
    run_threads();
    return 0;
}