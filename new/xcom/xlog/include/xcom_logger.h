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

namespace xcom {
    
    class xcom_export XLog {
    public:
        XLog();
        ~XLog();
        XLog& operator=(const XLog&) = delete;
        XLog(const XLog&) = delete;
        XLog(const XLog&&) = delete;
        
        /**
         *  获取单例
         *  @return XLog 实例
         */
        static XLog& sharedInstance();
        /**
         *  创建日志
         *  @param mode 模式
         *  @param dir 目录
         *  @param prefix 日志名前缀
         */
        void openLog(xcom_log_mode mode,const char *dir, const char *prefix);
        /**
         *  添加日志
         *  @param level 级别
         *  @param file 文件名
         *  @param func 函数名
         *  @param line 行好
         *  @param format 格式
         */
        void appendLog(xcom_log_level level, const char *file, const char *func, int line, const char *format, ...);

        void closeLog();
        
        void flushLog();
        
        void setLogLevel(xcom_log_level level);
        
        xcom_log_level getLogLevel();
        
        void setLogHook(const xcom_log_hook_callback &hook);
        
        void setConsoleLogCallback(const xcom_log_hook_callback &callback);
    };
};

#endif /* xcom_logger_hpp */
