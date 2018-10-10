#ifndef XCOM_TICK_H_
#define XCOM_TICK_H_

#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
    
    uint64_t    xcom_get_tick_count();
    int64_t     xcom_get_tick_span(uint64_t old_tick);
    uint64_t    xcom_time_ms();
    uint64_t    xcom_clock_app_monotonic();
    
#ifdef __cplusplus
}
#endif

#endif /* XCOM_TICK_H_ */
