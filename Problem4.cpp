// compile using g++ as
// $ g++ Problem4.cpp -lpthread -o output
#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

mutex Mutex;
int max_run = 20;
int free_seats = 10;
int custno = 0;
int barberno = 1;
void waitBarber()
{
    while (custno <= 0)
        ;
}
void signalBarber()
{
    custno--;
    if (custno == 0)
        cout << "Barber-> Sleeps\n";
}
void signalCustomer()
{
    custno++;
    if (custno == 1)
        cout << "Barber-> Wakes\n";
}
void barber()
{
    while (max_run > 0)
    {
        waitBarber();
        Mutex.lock();
        free_seats++;
        cout << "Barber-> Cuts Hair\n";
        signalBarber();
        Mutex.unlock();
        max_run--;
    }
}
void customer()
{
    while (max_run > 0)
    {
        Mutex.lock();
        if (free_seats > 0)
        {
            free_seats--;
            cout << "Customer-> Enters with number : " << custno + 1 << "\n";
            signalCustomer();
            Mutex.unlock();
        }
        else
        {
            cout << "The seats are full"
                 << "\n";
            Mutex.unlock();
        }
        max_run--;
    }
}

void run_threads()
{
    thread customer_thread(customer);
    thread barber_thread(barber);
    customer_thread.join();
    barber_thread.join();
}

int main()
{
    cout << "Sleeping Barber problem\n";
    run_threads();
    return 0;
}