//
//  xcom_tick.cpp
//  xcom
//
//  Created by AlexiChen on 2018/10/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xcom_tick.h"
#include "xcom_tick_util.h"

namespace XCom_NameSpace
{
    xcom_tick_count_diff::xcom_tick_count_diff(int64_t diff) : _tickCountDiff(diff) {
        
    }
    
    xcom_tick_count_diff::operator int64_t() const {
        return _tickCountDiff;
    }
    
    xcom_tick_count_diff &xcom_tick_count_diff::operator+=(int64_t factor) {
        _tickCountDiff += factor;
        return *this;
    }
    
    xcom_tick_count_diff &xcom_tick_count_diff::operator-=(int64_t factor) {
        _tickCountDiff -= factor;
        return *this;
    }
    
    xcom_tick_count_diff &xcom_tick_count_diff::operator*=(int64_t factor) {
        _tickCountDiff *= factor;
        return *this;
    }


    static uint64_t sg_tick_start = ::xcom_get_tick_count();
    static const uint64_t sg_tick_init = 2000000000;
    
    xcom_tick_count::xcom_tick_count(bool now)
    : _tickCount(0) {
        if (now) getTickCount();
    }
    
    xcom_tick_count_diff xcom_tick_count::operator-(const xcom_tick_count &tc) const {
        return xcom_tick_count_diff(_tickCount - tc._tickCount);
    }
    
    xcom_tick_count xcom_tick_count::operator+(const xcom_tick_count_diff &tc_diff) const {
        return xcom_tick_count(*this).operator+=(tc_diff);
    }
    
    xcom_tick_count xcom_tick_count::operator-(const xcom_tick_count_diff &tc_diff) const {
        return xcom_tick_count(*this).operator-=(tc_diff);
    }
    
    xcom_tick_count &xcom_tick_count::operator+=(const xcom_tick_count_diff &tc_diff) {
        _tickCount += (int64_t) tc_diff;
        return *this;
    }
    
    xcom_tick_count &xcom_tick_count::operator-=(const xcom_tick_count_diff &tc_diff) {
        _tickCount -= (int64_t) tc_diff;
        return *this;
    }
    
    uint64_t xcom_tick_count::get() const {
        return _tickCount;
    }
    
    xcom_tick_count &xcom_tick_count::getTickCount() {
        _tickCount = sg_tick_init + ::xcom_get_tick_count() - sg_tick_start;
        return *this;
    }
    
    xcom_tick_count_diff xcom_tick_count::getTickSpan() const {
        return xcom_tick_count(true) - (*this);
    }
    
    bool xcom_tick_count::operator<(const xcom_tick_count &tc) const {
        return _tickCount < tc._tickCount;
    }
    
    bool xcom_tick_count::operator<=(const xcom_tick_count &tc) const {
        return _tickCount <= tc._tickCount;
    }
    
    bool xcom_tick_count::operator==(const xcom_tick_count &tc) const {
        return _tickCount == tc._tickCount;
    }
    
    bool xcom_tick_count::operator!=(const xcom_tick_count &tc) const {
        return _tickCount != tc._tickCount;
    }
    
    bool xcom_tick_count::operator>(const xcom_tick_count &tc) const {
        return _tickCount > tc._tickCount;
    }
    
    bool xcom_tick_count::operator>=(const xcom_tick_count &tc) const {
        return _tickCount >= tc._tickCount;
    }
    
    bool xcom_tick_count::isValid() const{
        return _tickCount != 0;
    }
    
};

