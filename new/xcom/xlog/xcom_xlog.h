//
//  xcom_xlog.hpp
//  xcom
//
//  Created by AlexiChen on 2018/10/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#if XCOM_LOG_ENABLE

#ifndef xcom_xlog_hpp
#define xcom_xlog_hpp

#include "xcom_log.h"
#include "xcom_logger_struct.h"
#include "xcom_type_def.h"

#ifdef __cplusplus
extern "C" {
#endif
    
//    typedef void (*xcom_xlog_log_hook_callback)(const xcom_log_info &info, const char* log);
//    
//    xcom_extern void xcom_xlog_log_set_hook_callback(xcom_xlog_log_hook_callback observer);
//    
//    xcom_extern void xcom_xlog_log2(TXELogLevel level, const char *file, int line, const char *func, const char *format, va_list valist);
//    
//    xcom_extern void xcom_xlog_log(TXELogLevel level, const char *file, int line, const char *func, const char *format, ...);
//    
//    xcom_extern void xcom_xlog_log_set_level(TXELogLevel level);
//    
//    xcom_extern void xcom_xlog_log_set_console(bool is_open);
//    
//    xcom_extern void xcom_xlog_log_open(TXELogMode mode, const char *dir, const char *nameprefix);
//    
//    xcom_extern void xcom_xlog_log_flush();
//    
//    xcom_extern void xcom_xlog_log_close();
    
#ifdef __cplusplus
}
#endif

#endif /* xcom_xlog_hpp */
#endif
