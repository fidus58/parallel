//
//  main.cpp
//  mutex
//
//  Created by Klaus Ahrens on 10.06.13.
//  Copyright (c) 2013 Klaus Ahrens. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::mutex mut;

std::atomic<int> atomic_count;
int non_atomic_count;

std::atomic_flag lock = ATOMIC_FLAG_INIT;

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    std::thread up   ([](){
                           for (int i=0; i<10'000'000;++i) {
                             //std::lock_guard<std::mutex> lock(mut);
                             //while(lock.test_and_set(std::memory_order_acquire));
                             non_atomic_count++;
                             //lock.clear(std::memory_order_release);
                           }
                     });
    
    std::thread down ([](){
                           for (int i=0; i<10'000'000;++i) {
                             //std::lock_guard<std::mutex> lock(mut);
                             //while(lock.test_and_set(std::memory_order_acquire));
                             non_atomic_count--;
                             //lock.clear(std::memory_order_release);
                           }
                     });
    
    up.join(); down.join();
    end = std::chrono::system_clock::now();
    int elapsed_millis = std::chrono::duration_cast<std::chrono::milliseconds>
    (end-start).count();
    std::cout << "elapsed time: " << elapsed_millis/1000.0 << "s\n";
    std::cout << non_atomic_count <<std::endl;
}

