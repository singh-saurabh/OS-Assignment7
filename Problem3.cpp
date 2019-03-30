#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

mutex m;
int val = 0;
int max_run = 20;
int res = 0;
void waitAgent()
{
    while (val != 0)
        ;
}
void signalAgent(int x)
{
    val = x;
    //cout<<val<<endl;
}
void signalSmoker()
{
    val = 0;
}
void waitSmoker(int x)
{
    while (val != x && max_run > 0)
        ;
    res = x;
}
void agent()
{
    while (max_run > 0)
    {
        waitAgent();
        m.lock();
        int random = rand();
        random = random % 3 + 1;
        if (random == 1)
        {
            cout << "Agent: 1\n";
            signalAgent(1);
        }
        else if (random == 2)
        {
            cout << "Agent: 2\n";
            signalAgent(2);
        }
        else if (random == 3)
        {
            cout << "Agent: 3\n";
            signalAgent(3);
        }
        m.unlock();
        max_run--;
    }
}

void smoker(int s)
{
    while (max_run > 0)
    {
        waitSmoker(s);
        if (max_run <= 0)
            break;
        m.lock();
        cout << "Smoked by Smoker " << s << "\n";
        signalSmoker();
        m.unlock();
        max_run--;
    }
}

int main()
{
    srand(clock());
    cout << "Cigarette Smoker Problem using agent \n";
    thread t1(agent);
    thread t2(smoker, 1);
    thread t3(smoker, 2);
    thread t4(smoker, 3);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}