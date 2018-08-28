#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <functional>
#include <stdio.h>
#include <chrono>

using namespace std;
int main()
{
    bool stoped = false;
    std::mutex m;
    int index = 0;
    std::function<void(std::string)> func = [&](std::string tn){
        std::lock_guard<std::mutex> guard(m);
        index++;
        std::cout << tn << " : " << index << std::endl;
        
    };
    
    std::thread([=]{
        while (!stoped) {
            func("Thread 1");
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }).detach();
    
    std::thread([=]{
        while (!stoped) {
            func("Thread 2");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }).detach();
    
    std::thread([=]{
        while (!stoped) {
            func("Thread 3");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }).detach();
    
    getchar();
    stoped = false;
    return 0;
}
