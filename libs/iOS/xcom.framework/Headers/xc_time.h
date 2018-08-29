#ifndef XC_TIME_H_
#define XC_TIME_H_

#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
    
    uint64_t    xc_get_tick_count();                        // ms
    int64_t     xc_get_tick_span(uint64_t _old_tick);       // ms
    uint64_t    xc_timeMs();
    uint64_t    xc_clock_app_monotonic();                   // ms
    
#ifdef __cplusplus
}
#endif


#endif /* XC_TIME_H_ */
