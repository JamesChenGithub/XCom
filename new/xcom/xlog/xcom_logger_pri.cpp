//
//  xcom_logger_pri.cpp
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#include "xcom_logger_pri.h"

#if XCOM_LOG_ENABLE
namespace xcom
{
    void xcom_console_hook(xcom_log_info &info, const char *log)
    {
        
        xcom_log_hook_callback callback = XLogPri::sharedInstance().getConsoleLogCallback();
        if (callback) {
            std::string str = info.to_string();
            callback(str.c_str());
        }
        
    }
    
    void xcom_log_hook(xcom_log_info &info, const char* log)
    {
        xcom_log_hook_callback callback = XLogPri::sharedInstance().getLogHook();
        if (callback) {
            std::string str = info.to_string();
            callback(str.c_str());
        }
    }
    
    XLogPri::XLogPri()
    {
        m_log_level = xcom_log_level_debug;
    }
    
    XLogPri::~XLogPri()
    {
    }
    
    XLogPri& XLogPri::sharedInstance()
    {
        static XLogPri instance;
        return instance;
    }
    
    void XLogPri::appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, va_list valist)
    {
//        txf_log2((TXELogLevel)level, file, line, func, format, valist);
    }
    
    void XLogPri::appendLog(xcom_log_info &info, const char *format, va_list valist)
    {
//        txf_log2((TXELogLevel)info.level, info.fileName.c_str(), info.line, info.funcName.c_str(), format.c_str(), valist);
    }
    
    
    void XLogPri::setLogHook(const xcom_log_hook_callback &hook)
    {
//        if(hook){
//            txf_log_set_hooker(txf_log_hook);
//        }
//        else{
//            txf_log_set_hooker(NULL);
//        }
        m_log_hook = hook;
    }
    
    void XLogPri::setConsoleLogCallback(const xcom_log_hook_callback &callback)
    {
//        if(callback == NULL){
//            txf_log_set_console(false);
//        }
//        else{
//            txf_log_set_console(true);
//        }
        m_console_hook = callback;
    }
    
    
    xcom_log_hook_callback& XLogPri::getLogHook()
    {
        return m_log_hook;
    }
    xcom_log_hook_callback& XLogPri::getConsoleLogCallback()
    {
        return m_console_hook;
    }
    
    
//    void XLogPri::SetTidDelegate(const IDDelegate &delegate)
//    {
//        tidDelegate_ = delegate;
//    }
//
//    void XLogPri::SetMainTidDelegate(const IDDelegate &delegate)
//    {
//        mainTidDelegate_ = delegate;
//    }
//
//    IDDelegate& XLogPri::GetTidDelegate()
//    {
//        return tidDelegate_;
//    }
//
//    IDDelegate& XLogPri::GetMainTidDelegate()
//    {
//        return mainTidDelegate_;
//    }
    
    void XLogPri::openLog(xcom_log_mode mode,const char *dir, const char *prefix)
    {
//        txf_log_set_level((TXELogLevel)logLevel_);
//        txf_log_open((TXELogMode)mode, dir.c_str(), prefix.c_str());
    }
    
    void XLogPri::closeLog()
    {
//        txf_log_close();
    }
    
    void XLogPri::flushLog()
    {
//        txf_log_flush();
    }
    
    
    void XLogPri::setLogLevel(xcom_log_level level)
    {
//        txf_log_set_level((TXELogLevel)level);
//        logLevel_ = level;
    }
    
    xcom_log_level XLogPri::getLogLevel()
    {
        return m_log_level;
    }
    
    
//    extern "C"
//    {
//        intmax_t txf_logger_pid()
//        {
//            static intmax_t pid = getpid();
//            return pid;
//        }
//
//        intmax_t txf_logger_tid()
//        {
//            return (intmax_t)(XLogPri::GetInstance().GetTidDelegate() == NULL ? -1 : XLogPri::GetInstance().GetTidDelegate()());
//        }
//
//        intmax_t txf_logger_main_tid()
//        {
//            return (intmax_t)(XLogPri::GetInstance().GetMainTidDelegate() == NULL ? -1 : XLogPri::GetInstance().GetMainTidDelegate()());
//        }
//    }
    
}
#endif
