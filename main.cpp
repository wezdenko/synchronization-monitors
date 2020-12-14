#include <thread>
#include <cstdlib>
#include <iostream>
#include "headers/BufferMonitor.hpp"

#define SLEEP_TIME 100000   // 0.1s

BufferMonitor monitor;
int lastOdd = -1;
int lastEven = 0;


void producerEven()
{
    while (true)
    {
        int num = lastEven + 2;
        monitor.putEven(num);
        lastEven = num;
        std::cout << "Put: " << num << std::endl;
        usleep(SLEEP_TIME + rand() % SLEEP_TIME);
    }
}

void producerOdd()
{
    while (true)
    {
        int num = lastOdd + 2;
        monitor.putOdd(num);
        lastOdd = num;
        std::cout << "Put: " << num << std::endl;
        usleep(SLEEP_TIME + rand() % SLEEP_TIME);
    }
}

void consumerEven()
{
    while (true)
    {
        int num = monitor.getEven();
        std::cout << "Get: " << num << std::endl;
        usleep(SLEEP_TIME + rand() % SLEEP_TIME);
    }
}

void consumerOdd()
{
    while (true)
    {
        int num = monitor.getOdd();
        std::cout << "Get: " << num << std::endl;
        usleep(SLEEP_TIME + rand() % SLEEP_TIME);
    }
}

int main(int argc, char const *argv[])
{
    std::thread A1(producerEven);
    std::thread A2(producerOdd);
    std::thread B1(consumerEven);
    std::thread B2(consumerOdd);

    A1.join();
    A2.join();
    B1.join();
    B2.join();
    
    return 0;
}