// compile using g++ as
// $ g++ Problem1.cpp -lpthread -o output

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
int BUFFER = 200;
int number = 0;
int maximum = 20;
int turn = 0;
int mut = 1;

void wait(string s)
{
    if (s == "empty")
    {
        while (number == BUFFER)
            ;
        mut--;
    }
    else
    {
        while (number == 0)
            ;
        mut--;
    }
}
void signal(string s)
{
    if (s == "empty")
    {
        mut++;
    }
    else
    {
        mut++;
    }
}
void producer()
{
    while (maximum > 0)
    {
        wait("empty");
        m.lock();
        number += 1;
        cout << "Produced-> " << number << "\n";
        maximum -= 1;
        m.unlock();
        signal("full");
    }
}
void consumer()
{
    while (maximum > 0)
    {
        wait("full");
        m.lock();
        cout << "Consumed<- " << number << "\n";
        number -= 1;
        maximum -= 1;
        m.unlock();
        signal("empty");
    }
}
void run_threads()
{
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
}
int main()
{
    cout << "Producer Consumer using semaphores \n";
    run_threads();
    return 0;
}