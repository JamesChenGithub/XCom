//
//  xcom_logger_struct.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_logger_struct_h
#define xcom_logger_struct_h


#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <stdint.h>
#include <string>
#include "xcom_log.h"


struct xcom_log_info {
public:
    xcom_log_level      level;
    std::string         tag;
    std::string         fileName;
    std::string         funcName;
    int                 line;
    
    struct timeval  timeval;
    int64_t         pid;
    int64_t         tid;
    int64_t         maintid;
    
public:
    std::string to_string()
    {
        return "";
    }
};

#endif /* xcom_logger_struct_h */
