#ifndef XCOM_TICK_UTIL_H_
#define XCOM_TICK_UTIL_H_

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    uint64_t xcom_get_tick_count();  // ms
    
    uint64_t xcom_get_utc_tick();
    
    uint64_t xcom_get_tick_span(uint64_t lastTick);
    
#ifdef __cplusplus
}
#endif

#endif /* XCOM_TICK_H_ */
