//
//  xcom_xlog.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef xcom_xlog_h
#define xcom_xlog_h

#include <stdio.h>
#include "xcom_type_def.h"
#include "xcom_log.h"

#if XCOM_LOG_ENABLE

namespace XCom_NameSpace {
    
    class xcom_export XLog
    {
    private:
        XLog();
        ~XLog();
        XLog& operator=(const XLog&) = delete;
        XLog(const XLog&) = delete;
        XLog(const XLog&&) = delete;
        
    public:
        // shared instance
        static XLog& sharedInstance();
        
        // init log setting
        void openLog(xcom_log_mode mode, const char *dir, const char *prefix);
        
        // append log
        void appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...);
        
        void closeLog();
        
        void flushLog();
        
        void setLogLevel(xcom_log_level level);
        
        xcom_log_level getLogLevel();
        
        void setLogHook(const xcom_xlog_hook &hook);

        void setFormatHook(const xcom_xlog_hook &hook);
        
        void setConsoleHook(const xcom_xlog_hook &callback);
        
        void setCryptHook(const xcom_xlog_crypt_hook &callback);
    };
};

#endif


#endif /* xcom_xlog_hpp */
