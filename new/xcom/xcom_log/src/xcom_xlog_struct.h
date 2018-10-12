//
//  xcom_xlog_struct.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef xcom_xlog_struct_h
#define xcom_xlog_struct_h


#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <stdint.h>
#include <string>
#include "xcom_log.h"

#if XCOM_LOG_ENABLE

struct xcom_log_info {
public:
    xcom_log_level      level;
    std::string         tag;
    std::string         file_name;
    std::string         func_name;
    int                 line;
    
    struct timeval      timeval;
    int64_t             pid;
    int64_t             tid;
    int64_t             maintid;
    
    std::string         log_content;
    
public:
    std::string to_string() const
    {
        return "";
    }
};


//extern intmax_t xcom_xlog_pid();
//
//extern intmax_t xcom_xlog_tid();
//
//extern intmax_t xcom_xlog_main_tid();

#endif

#endif /* xcom_xlog_struct_h */
