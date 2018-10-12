//
//  xcom_xlog.cpp
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xcom_xlog.h"
#include "xcom_xlog_core.h"

#if XCOM_LOG_ENABLE
namespace XCom_NameSpace {
    
    XLog::XLog()
    {
    }
    
    XLog::~XLog()
    {
    }
    
    
    XLog& XLog::sharedInstance()
    {
        static XLog instance;
        return instance;
    }
    
    void XLog::openLog(xcom_log_mode mode, const char *dir, const char *prefix)
    {
        Logger::sharedInstance().openLog(mode, dir, prefix);
    }
    
    void XLog::appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...)
    {
        va_list valist;
        va_start(valist, format);
        Logger::sharedInstance().appendLog(level, file, func, line, format, valist);
        va_end(valist);
    }
    
    void XLog::closeLog()
    {
        Logger::sharedInstance().closeLog();
    }
    
    void XLog::flushLog()
    {
        Logger::sharedInstance().flushLog();
    }
    
    
    void XLog::setLogLevel(xcom_log_level level)
    {
        Logger::sharedInstance().setLogLevel(level);
    }
    
    xcom_log_level XLog::getLogLevel()
    {
        return Logger::sharedInstance().getLogLevel();
    }
    
    void XLog::setFormatHook(const xcom_xlog_hook &hook)
    {
        Logger::sharedInstance().setFormatHook(hook);
    }
    
    void XLog::setLogHook(const xcom_xlog_hook &hook)
    {
        Logger::sharedInstance().setLogHook(hook);
    }
    
    void XLog::setConsoleHook(const xcom_xlog_hook &callback)
    {
        Logger::sharedInstance().setConsoleHook(callback);
    }
    
    void XLog::setCryptHook(const xcom_xlog_crypt_hook &callback)
    {
        Logger::sharedInstance().setCryptHook(callback);
    }
    
}
#endif
