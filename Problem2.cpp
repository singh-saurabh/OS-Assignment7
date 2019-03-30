// compile using g++ as
// $ g++ Problem2.cpp -lpthread -o output

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
int write_read = 1;
int readerno = 0;
int max_run = 10;
int mut = 1;

void wait(string s)
{
    while (write_read == 0)
        ;
    write_read--;
}

void signal(string s)
{
    write_read++;
}
void writer()
{
    while (max_run > 0)
    {
        wait("empty");
        cout << "Writing\n";
        max_run--;
        signal("full");
    }
}

void reader()
{
    while (max_run > 0)
    {
        m.lock();
        readerno++;
        if (readerno == 1)
            wait("wrt");
        m.unlock();
        cout << "Reading\n";
        m.lock();
        readerno--;
        if (readerno == 0)
            signal("full");
        m.unlock();
        max_run--;
    }
}

int main()
{
    cout << "Starve free reader writer solution \n";
    thread writer_thread(writer);
    thread reader_thread(reader);
    writer_thread.join();
    reader_thread.join();
    return 0;
}