//
//  xcom_xlog.cpp
//  xcom
//
//  Created by AlexiChen on 2018/10/11.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#if XCOM_LOG_ENABLE

#include "xcom_xlog.h"


xcom_xlog_log_hook_callback g_logObserver = 0;

void xcom_xlog_log_set_hook_callback(xcom_xlog_log_hook_callback observer) {
    g_logObserver = observer;
}

#ifdef __cplusplus
extern "C" {
#endif
//    void xcom_xlog_log2(xcom_log_level level, const char *file, int line, const char *func, const char *format, va_list valist){
//       
//        if (!txf_logger_is_enabled_for((TXELoggerLevel) level))
//            return;
//        char strBuf[16 * 1024];
//        vsprintf(strBuf, format, valist);
//        
//        
//        TXSLogInfo info = {(TXELoggerLevel) level, "", file, func, line, {0, 0}, -1, -1, -1};
//        info.pid = txf_logger_pid();
//        info.tid = txf_logger_tid();
//        info.maintid = txf_logger_main_tid();
//        gettimeofday(&info.timeval, NULL);
//        
//        if (g_logObserver) {
//            g_logObserver(info, strBuf);
//            return;
//        }
//        
//        txf_logger_write(&info, strBuf);
//    }
//    
//    void txf_log(TXELogLevel level, const char *file, int line, const char *func, const char *format, ...){
//        if (!txf_logger_is_enabled_for((TXELoggerLevel) level)) return;
//        char strBuf[16 * 1024];
//        va_list pArgs;
//        va_start(pArgs, format);
//        vsprintf(strBuf, format, pArgs);
//        va_end(pArgs);
//        
//        
//        TXSLogInfo info = {(TXELoggerLevel) level, "", file, func, line, {0, 0}, -1, -1, -1};
//        info.pid = txf_logger_pid();
//        info.tid = txf_logger_tid();
//        info.maintid = txf_logger_main_tid();
//        gettimeofday(&info.timeval, NULL);
//        
//        if (g_logObserver) {
//            g_logObserver(info, strBuf);
//            return;
//        }
//        
//        txf_logger_write(&info, strBuf);
//    }
//    
//    void txf_log_set_level(TXELogLevel level) {
//        txf_logger_set_level((TXELoggerLevel) level);
//    }
//    
//    void txf_log_set_console(bool is_open) {
//        txf_appender_set_console_log(is_open);
//    }
//    
//    void txf_log_open(TXELogMode mode, const char *dir, const char *nameprefix) {
//        txf_appender_open((enum TXEAppenderMode) mode, dir, nameprefix);
//    }
//    
//    void txf_log_flush(){
//        txf_appender_flush_sync();
//    }
//    
//    void txf_log_close() {
//        txf_appender_close();
//    }
#ifdef __cplusplus
}
#endif
#endif
