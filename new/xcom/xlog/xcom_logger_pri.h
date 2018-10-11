//
//  xcom_logger_pri.hpp
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef xcom_logger_pri_h
#define xcom_logger_pri_h

#include <stdio.h>
#include "xcom_log.h"
#include "xcom_logger_struct.h"

#if XCOM_LOG_ENABLE
namespace xcom {
    class XLogPri {
    public:
        XLogPri();
        ~XLogPri();
        
        XLogPri& operator=(const XLogPri&) = delete;
        XLogPri(const XLogPri&) = delete;
        XLogPri(const XLogPri&&) = delete;
        static XLogPri& sharedInstance();
        
        void appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, va_list valist);
        void appendLog(xcom_log_info &info, const char *format, va_list valist);
        void openLog(xcom_log_mode mode, const char *dir, const char *prefix);
        void closeLog();
        void flushLog();
        
        
        void setLogHook(const xcom_log_hook_callback &hook);
        void setConsoleLogCallback(const xcom_log_hook_callback &callback);
        xcom_log_hook_callback& getLogHook();
        xcom_log_hook_callback& getConsoleLogCallback();
        
        void setLogLevel(xcom_log_level level);
        xcom_log_level getLogLevel();
        
    private:
        xcom_log_hook_callback    m_log_hook;
        xcom_log_hook_callback    m_console_hook;
        xcom_log_level            m_log_level;
    };
};

#endif
#endif /* xcom_logger_pri_hpp */
