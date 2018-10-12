//
//  xcom_tick.hpp
//  xcom
//
//  Created by AlexiChen on 2018/10/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_tick_hpp
#define xcom_tick_hpp

#include <stdint.h>
#include "xcom_config.h"

namespace XCom_NameSpace
{
    class xcom_tick_count_diff
    {
    public:
        xcom_tick_count_diff(int64_t diff);
        
        operator int64_t() const;
        
        xcom_tick_count_diff &operator+=(int64_t factor);
        
        xcom_tick_count_diff &operator-=(int64_t factor);
        
        xcom_tick_count_diff &operator*=(int64_t factor);
        
    public:
        // xcom_tick_count_diff(const xcom_tick_count_diff&);
        // xcom_tick_count_diff& operator=(const xcom_tick_count_diff&);
        
    private:
        int64_t _tickCountDiff;
    };
    
    class xcom_tick_count {
    public:
        xcom_tick_count(bool now = false);
        
        xcom_tick_count_diff operator-(const xcom_tick_count &tc) const;
        
        xcom_tick_count operator+(const xcom_tick_count_diff &tc_diff) const;
        
        xcom_tick_count operator-(const xcom_tick_count_diff &tc_diff) const;
        
        xcom_tick_count &operator+=(const xcom_tick_count_diff &tc_diff);
        
        xcom_tick_count &operator-=(const xcom_tick_count_diff &tc_diff);
        
        uint64_t get() const;
        
        xcom_tick_count &getTickCount();
        
        xcom_tick_count_diff getTickSpan() const;
        
        bool operator<(const xcom_tick_count &tc) const;
        
        bool operator<=(const xcom_tick_count &tc) const;
        
        bool operator==(const xcom_tick_count &tc) const;
        
        bool operator!=(const xcom_tick_count &tc) const;
        
        bool operator>(const xcom_tick_count &tc) const;
        
        bool operator>=(const xcom_tick_count &tc) const;
        
        bool isValid() const;
        
    public:
        // xcom_tick_count(const xcom_tick_count&);
        // xcom_tick_count& operator=(const xcom_tick_count&);
        
    private:
        uint64_t _tickCount;
    };
};
#endif /* xcom_tick_hpp */
