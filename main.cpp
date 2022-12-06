/*Assignment 6: Producer-consumer
Edited by Zubaydah Koelemeij
06/12/2022*/

#include <queue>
#include <thread>
#include <iostream>
#include <mutex>

int counter = 0;
bool done = false;

std::mutex mutex;

std::queue<int> goods;

void producer()
{
    const std::lock_guard<std::mutex> lock(mutex);

    std::cout << "Starting producer..." << std::endl;

    for (int i = 0; i < 500; ++i)
    {
        goods.push(i);
        counter++;
    }

    done = true;

    std::cout << "Finished producer..." << std::endl;
}

void consumer()
{
    const std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Starting consumer..." << std::endl;

    while (!goods.empty())
    {
        goods.pop();
        counter--;
    }

    std::cout << "Finished consumer..." << std::endl;
}

int main()
{
    counter = 0;
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    std::cout << "Net: " << counter << " " << goods.size() << std::endl;
}
