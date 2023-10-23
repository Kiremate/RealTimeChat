#include <iostream>
#include <chrono>
#include "ThreadPool.h"  

int main() {
    ThreadPool pool(4);

    bool running = true;
    int i = 0;

    std::thread inputThread([&running] {
        char ch;
        std::cout << "Press 'F' to stop..." << std::endl;
        do {
            std::cin >> ch;
        } while (ch != 'F' && ch != 'f');
        running = false;
        });

    while (running) {
        pool.enqueueJob([i] {
            std::cout << "Printing: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  
            });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++i;
    }

    inputThread.join();

    return 0;
}
