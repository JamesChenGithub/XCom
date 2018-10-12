//
//  xcom_tick_util.cpp
//  xcom
//
//  Created by AlexiChen on 2018/10/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xcom_tick_util.h"
#include <chrono>
#include <unistd.h>
#include <sys/time.h>

#if defined(_WIN32)
#include <ctime>
#include <limits>
#undef max
#else
#include <time.h>
#include <sys/syscall.h>
#if defined(__MACH__)
#include <mach/mach_time.h>
#endif
#endif

extern "C"{
    
    uint64_t xcom_get_tick_count() {
        //    return (uint64_t) std::chrono::steady_clock::now().time_since_epoch().count() / 1000000;
        static unsigned long long s_tick_delta = 0;
        
        unsigned long long tick = 0;
#if defined(_WIN32)
        
        struct timeval currentWin;
        gettimeofday(&currentWin, NULL);
        tick = (unsigned long long)currentWin.tv_sec * 1000 + currentWin.tv_usec / 1000;
#else
#if defined(__MACH__)//for ios and macos
        static mach_timebase_info_data_t info = {0};
        static kern_return_t krv __attribute__((unused)) = mach_timebase_info(&info);
        static double r = 1.0 * info.numer / (info.denom * NSEC_PER_MSEC);
        tick = mach_absolute_time() * r;
#else
        struct timespec curr_time = {0, 0};
        
        syscall(__NR_clock_gettime, CLOCK_MONOTONIC_RAW, &curr_time);
        
        tick = curr_time.tv_sec*1000 + curr_time.tv_nsec/1000/1000;
#endif
#endif
        
        if(s_tick_delta == 0) {
            struct timeval current;
            gettimeofday(&current, NULL);
            s_tick_delta = ((unsigned long long)current.tv_sec*1000 + current.tv_usec/1000) - tick;
        }
        
        tick += s_tick_delta;
        
        return tick;
    }
    
    uint64_t xcom_get_utc_tick(){
        return (uint64_t) std::chrono::system_clock::now().time_since_epoch().count() / 1000;
    }
    
    uint64_t xcom_get_tick_span(uint64_t lastTick){
#if defined(_WIN32)
        struct timeval currentWin;
        gettimeofday(&currentWin, NULL);
        unsigned long long tick = (unsigned long long)currentWin.tv_sec * 1000 + currentWin.tv_usec / 1000;
        
        if (tick >= lastTick)
        {
            return (tick - lastTick);
        }
        else
        {
            return ((std::numeric_limits<unsigned long long>::max() - lastTick) + tick);  // 整型溢出
        }
#else
        return xcom_get_tick_count() - lastTick;
#endif
    }
    
}

