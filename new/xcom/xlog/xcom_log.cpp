//
//  xcom_log.c
//  xcom
//
//  Created by AlexiChen on 2018/10/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#include "xcom_log.h"
#include "xcom_logger.h"

#if XCOM_LOG_ENABLE
#ifdef __cplusplus
extern "C" {
#endif
    void extern_xcom_log(xcom_log_level level, const char *filename , const char *funcname, int line, const char *format, ...)
    {
        va_list valist;
        va_start(valist, format);
        xcom::XLog::sharedInstance().appendLog(level, filename, funcname, line, format, valist);
        va_end(valist);
    }
#ifdef __cplusplus
}
#endif
#endif
