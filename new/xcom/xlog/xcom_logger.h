//
//  xcom_logger.hpp
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef xcom_logger_h
#define xcom_logger_h

#include <stdio.h>
#include "xcom_type_def.h"
#include "xcom_log.h"

#if XCOM_LOG_ENABLE

namespace xcom {
    
    class xcom_export XLog {
    public:
        XLog();
        ~XLog();
        XLog& operator=(const XLog&) = delete;
        XLog(const XLog&) = delete;
        XLog(const XLog&&) = delete;
        
        // shared instance
        static XLog& sharedInstance();
       
        // init log setting
        void openLog(xcom_log_mode mode,const char *dir, const char *prefix);
        
        // append log
        void appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...);

        void closeLog();
        
        void flushLog();
        
        void setLogLevel(xcom_log_level level);
        
        xcom_log_level getLogLevel();
        
        void setLogHook(const xcom_log_hook_callback &hook);
        
        void setConsoleLogCallback(const xcom_log_hook_callback &callback);
    };
};

#endif


#endif /* xcom_logger_hpp */
