#include<iostream>
#include <ctime>
#include <cstdlib>
#include<ctime>
#include <unistd.h>

using namespace std;

class timer
{
private:
    unsigned long begTime;
public:
    void start()
    {
        begTime = clock();
    }
    unsigned long elapsedTime()
    {
        return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
    }
    bool isTimeout(unsigned long seconds)
    {
        return seconds >= elapsedTime();
    }
};

void wait()
{
    int to = 24500 + rand() % 39500  + 1;
    for(int i=0; i < 64000; i++)
        for(int j=0; j < to; j++) {}
}

int main()
{
    int frames[] = {1,2};
    int n = 2;
    unsigned long seconds = 5;

    srand(time(NULL));
    timer t;

    cout<<"Sender has to send frames : ";
    for(int i=0; i<n; i++)
        cout<<frames[i]<<" ";
    cout<<endl;

    int count = 0;
    bool delay = false;
    cout<<endl<<"Sender\t\t\t\t\tReceiver\n"<<endl;

    do
    {
        bool timeout = false;
        cout<<"Sending Frame : "<<frames[count];
        cout.flush();
        cout<<"\t\t";
        t.start();

        if(rand()%2)
        {
            wait();
        }

        if(t.elapsedTime() <= seconds)
        {
            cout<<"Received Frame : "<<frames[count]<<" ";
            if(delay)
            {
                cout<<"Duplicate";
                delay = false;
            }
            cout << endl;
            count++;
        }

        else
        {
            cout<<"---"<<endl;
            cout<<"Timeout"<<endl;
            timeout = true;
        }

        t.start();
        if(rand()%2 || !timeout)
        {
            wait();
            if(t.elapsedTime() > seconds )
            {
                cout<<"Delayed Ack" << endl;
                if(count != 0)
                    count--;
                delay = true;
            }

            else if(!timeout)
            {
                cout<< "Acknowledgement : ";
                if(count != n)
                    cout << frames[count] <<endl;
                else
                    cout << 0 << endl;
            }
        }
        cout << endl;
    }
    while(count != n);
    return 0;
}

