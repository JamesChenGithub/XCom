//
//  xcom_xlog_core.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_xlog_core_h_
#define xcom_xlog_core_h_

#include "xcom_log.h"

#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <thread>

namespace XCom_NameSpace
{
    const static uint32_t kXCom_XLog_MaxSize = 50 * 1024 * 1024;
    const static size_t kXCom_XLog_BufferSize = 32 * 1024;
    const static int kXCom_XLog_MaxNum = 10;
    
    
    class Logger
    {
    private:
        std::string             m_log_dir;            // 日志全文件名
        std::string             m_log_full_name;      // 日志全文件名
        std::string             m_logbuf;
        uint32_t                m_totalSize;
        std::recursive_mutex    m_log_mutex;
        std::mutex              m_open_mutex;
        xcom_log_level          m_log_level;
        xcom_log_mode           m_log_mode;
        std::atomic_bool        m_print_console;
        std::atomic_bool        m_log_closed;
        
    private:
        // 用于外部导出日志
        xcom_xlog_hook          m_log_hook;
        // 用于格式化日志
        xcom_xlog_hook          m_format_hook;
        // 用于调试时日志
        xcom_xlog_hook          m_console_hook;
        // 用于加密
        xcom_xlog_crypt_hook    m_crypt_hook;
        
    private:
        Logger();
        
        ~Logger();
    private:
        Logger& operator=(const Logger&) = delete;
        Logger(const Logger&) = delete;
        Logger(const Logger&&) = delete;
    public:
        static Logger& sharedInstance();
        
    public:
        // init log setting
        void openLog(xcom_log_mode mode,const char *dir, const char *prefix);
        
        // append log
        void appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...);
        
        void closeLog();
        
        void flushLog();
        
        inline void setLogLevel(xcom_log_level level)
        {
            m_log_level = level;
        }
        
        inline xcom_log_level getLogLevel()
        {
            return m_log_level;
        }
        
        inline void setLogHook(const xcom_xlog_hook &hook)
        {
            m_log_hook = hook;
        }
        
        inline void setFormatHook(const xcom_xlog_hook &hook)
        {
            m_format_hook = hook ? hook : Logger::defaultFormatHook;
        }
        
        inline void setConsoleHook(const xcom_xlog_hook &callback)
        {
             m_console_hook = callback;
        }
        
        inline void setCryptHook(const xcom_xlog_crypt_hook &callback)
        {
            m_crypt_hook = callback;
        }
    
        

        
    private:
        static void defaultFormatHook(const char *time, xcom_log_level level, const char *filename , const char *funcname, int line, int pid, int tid, int mid, const char *format, const char *logcontent);
        
    private:
        void create_log_directory(const char *dir);
        void delete_time_out_mmap();
        void create_mmap_file();
        void flush_mmap_file_atexit();
    };
}

#endif /* HIMLogger_hpp */
