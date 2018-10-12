//
//  xcom_xlog_core.cpp
//  xcom
//
//  Created by AlexiChen on 2017/10/10.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//
//
//                        _ooOoo_
//                       o8888888o
//                       88" . "88
//                       (| -_- |)
//                       O\  =  /O
//                     ___/`---'\____
//                 .'  \\|      |//  `.
//                 /  \\|||  :  |||//  \
//                /  _||||| -:- |||||-  \
//                |   | \\\  -  /// |   |
//                | \_|  ''\---/''  |   |
//                \  .-\__  `-`  ___/-. /
//              ___`. .'  /--.--\  `. . __
//           ."" '<  `.___\_<|>_/___.'  >'"".
//           | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//           \  \ `-.   \_ __\ /__ _/   .-` /  /
//      ======`-.____`-.___\_____/___.-`____.-'======
//                         `=---='
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                        佛祖保佑
//                        永无BUG


#include "xcom_xlog_core.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "xcom_path.h"
#include "xcom_tick.h"


namespace XCom_NameSpace {
    
#define append_log(fmt, ...) Logger::appendLog(m_log_level, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
    
    //==================================================
    
    static void __log2file(const void *data, size_t len) {
//        if (NULL == data || 0 == len || txv_logdir.empty()) {
//            return;
//        }
//
//        TXCScopedLock lock_file(txv_mutex_log_file);
//
//        if (txv_cache_logdir.empty()) {
//            if (__openlogfile(txv_logdir)) {
//                __writefile(data, len, txv_logfile);
//                if (kAppednerAsync == txv_mode) {
//                    __closelogfile();
//                }
//            }
//            return;
//        }
//
//        struct timeval tv;
//        gettimeofday(&tv, NULL);
//        char logcachefilepath[1024] = {0};
//
//        __make_logfilename(tv, txv_cache_logdir, txv_logfileprefix.c_str(), LOG_EXT, logcachefilepath, 1024);
//
//        TXCPath path(logcachefilepath);
//        if (path.exists() && __openlogfile(txv_cache_logdir)) {
//            __writefile(data, len, txv_logfile);
//            if (kAppednerAsync == txv_mode) {
//                __closelogfile();
//            }
//
//
//            char logfilepath[1024] = {0};
//            __make_logfilename(tv, txv_logdir, txv_logfileprefix.c_str(), LOG_EXT, logfilepath, 1024);
//            if (__append_file(logcachefilepath, logfilepath)) {
//                if (kAppednerSync == txv_mode) {
//                    __closelogfile();
//                }
//                remove(logcachefilepath);
//            }
//        } else {
//            bool write_sucess = false;
//            bool open_success = __openlogfile(txv_logdir);
//            if (open_success) {
//                write_sucess = __writefile(data, len, txv_logfile);
//                if (kAppednerAsync == txv_mode) {
//                    __closelogfile();
//                }
//            }
//
//            if (!write_sucess) {
//                if (open_success && kAppednerSync == txv_mode) {
//                    __closelogfile();
//                }
//
//                if (__openlogfile(txv_cache_logdir)) {
//                    __writefile(data, len, txv_logfile);
//                    if (kAppednerAsync == txv_mode) {
//                        __closelogfile();
//                    }
//                }
//            }
//        }
        
    }
    
    static void __writetips2file(const char *tips_format, ...) {
        
//        if (NULL == tips_format) {
//            return;
//        }
//
//        char tips_info[4096] = {0};
//        va_list ap;
//        va_start(ap, tips_format);
//        vsnprintf(tips_info, sizeof(tips_info), tips_format, ap);
//        va_end(ap);
//
//        char tmp[8 * 1024] = {0};
//        size_t len = sizeof(tmp);
//
//        // TODO:
//        //TXCLogBuffer::Write(tips_info, strnlen(tips_info, sizeof(tips_info)), tmp, len);
//
//        __log2file(tmp, len);
    }
    
    static void __writetips2console(const char *tips_format, ...) {
        
//        if (NULL == tips_format) {
//            return;
//        }
//
//        TXSLogInfo info;
//        memset(&info, 0, sizeof(TXSLogInfo));
//
//        char tips_info[4096] = {0};
//        va_list ap;
//        va_start(ap, tips_format);
//        vsnprintf(tips_info, sizeof(tips_info), tips_format, ap);
//        va_end(ap);
//        gettimeofday(&info.timeval, NULL);
//        txf_console_log(&info, tips_info);
    }
    
    static void __del_timeout_file(const std::string &log_path) {
//        time_t now_time = time(NULL);
//        
//        TXCPath path(log_path);
//        
//        if (path.exists() && path.is_directory()) {
//            std::vector<TXCPath> files = path.childs();
//            for(int i = 0; i < files.size(); ++i){
//                time_t fileModifyTime = files[i].last_modified_time();
//                
//                if (now_time > fileModifyTime && now_time - fileModifyTime > kMaxLogAliveTime) {
//                    if (files[i].is_file()) {
//                        files[i].remove_file();
//                    } else if (files[i].is_directory()) {
//                        __del_files(files[i].str());
//                    }
//                }
//            }
//        }
    }
    
    //==================================================
    
    Logger::Logger()
    {
        m_totalSize = 0;
        m_log_level = xcom_log_level_debug;
        m_log_mode = xcom_log_mode_async;
        m_print_console = true;
        m_log_closed = false;
    }
    
    Logger::~Logger()
    {
        this->flushLog();
        this->closeLog();
    }
    
    Logger& Logger::sharedInstance()
    {
        static Logger instance;
        return instance;
    }
    
    void Logger::openLog(xcom_log_mode mode, const char *dir, const char *nameprefix)
    {
        m_log_mode = mode;
        
        assert(dir);
        assert(nameprefix);
        
        if (m_log_closed) {
            __writetips2file("xlog has already been opened. dir:%s nameprefix:%s", dir, nameprefix);
            return;
        }
        std::lock_guard<std::mutex> lock(m_open_mutex);
        
        // 1. 创建目录
        //mkdir(dir, S_IRWXU|S_IRWXG|S_IRWXO);
        xcom_path path(dir);
        if (!path.create_directory()) {
            __writetips2console("create directory error:%d %s, path:%s", errno, strerror(errno), dir);
        }
        
        // 2. 删除过期时间的文件
        this->delete_time_out_mmap();
      
        // 3. 获取mmap文件, 将上一次未保存的mmap文件写文件
        this->create_mmap_file();
        
        // 4. 异常退出时，写文件
        this->flush_mmap_file_atexit();
        
    }
    
    void Logger::appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...)
    {
//        va_list valist;
//        va_start(valist, format);
//        Logger::sharedInstance().appendLog(level, file, func, line, format, valist);
//        va_end(valist);
    }
    
    void Logger::closeLog()
    {
        
    }
    
    void Logger::flushLog()
    {
       
    }
    
    void Logger::defaultFormatHook(const char *time, xcom_log_level level, const char *filename , const char *funcname, int line, int pid, int tid, int mid, const char *format, const char *logcontent)
    {
        
    }
    
    
    void Logger::create_log_directory(const char *dir)
    {
        
    }
    void Logger::delete_time_out_mmap()
    {
        
    }
    void Logger::create_mmap_file()
    {
        
    }
    void Logger::flush_mmap_file_atexit()
    {
        
    }
}
