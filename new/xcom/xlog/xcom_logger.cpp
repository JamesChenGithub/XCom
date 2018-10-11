//
//  xcom_logger.cpp
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xcom_logger.h"
#include "xcom_logger_pri.h"

#if XCOM_LOG_ENABLE
namespace xcom {
    
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
        XLogPri::sharedInstance().openLog(mode, dir, prefix);
    }
    
    void XLog::appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...)
    {
        va_list valist;
        va_start(valist, format);
        XLogPri::sharedInstance().appendLog(level, file, func, line, format, valist);
        va_end(valist);
    }
    
    
    
    
    
    
    void XLog::closeLog()
    {
        XLogPri::sharedInstance().closeLog();
    }
    
    void XLog::flushLog()
    {
        XLogPri::sharedInstance().flushLog();
    }
    
    
    void XLog::setLogLevel(xcom_log_level level)
    {
        XLogPri::sharedInstance().setLogLevel(level);
    }
    
    xcom_log_level XLog::getLogLevel()
    {
        return XLogPri::sharedInstance().getLogLevel();
    }
    
    void XLog::setLogHook(const xcom_log_hook_callback &hook)
    {
        XLogPri::sharedInstance().setLogHook(hook);
    }
    
    void XLog::setConsoleLogCallback(const xcom_log_hook_callback &callback)
    {
        XLogPri::sharedInstance().setConsoleLogCallback(callback);
    }
    
}
#endif
