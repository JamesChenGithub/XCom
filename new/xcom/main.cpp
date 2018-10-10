//
//  main.c
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "xcom.h"

void extern_xcom_log(xcom_log_level level, const char *filename , const char *funcname, int line, const char *format, ...)
{
    static std::recursive_mutex logMutex;
    std::lock_guard<std::recursive_mutex> lock(logMutex);
    std::stringstream ss;
    
    va_list valist;
    va_start(valist, format);
    char strBuf[16 * 1024];
    vsnprintf(strBuf, 16 * 1024, format, valist);
    std::string str = strBuf;
    
    std::string lstr;
    switch (level)
    {
        case xcom_log_level_info:
            lstr = "I";
            break;
        case xcom_log_level_warn:
            lstr = "W";
            break;
        case xcom_log_level_error:
            lstr = "E";
            break;
        case xcom_log_level_debug:
            lstr = "D";
            break;
        case xcom_log_level_verbose:
            lstr = "V";
            break;
            
        default:
            break;
    }
    
    ss << lstr << "|" << std::setw(15) << filename << "|" << std::setw(20) <<funcname << "|" << std::setw(5) << line <<"|" << str << std::endl ;
    
    std::cout << ss.str() << std::endl;
    
    va_end(valist);
}

int main()
{
    xcom_log_debug("this is a test");
    xcom_log("this is a test");
    xcom_log("this is a test");
    xcom_log("this is a test");
    xcom_log("a");
    return 0;
}
