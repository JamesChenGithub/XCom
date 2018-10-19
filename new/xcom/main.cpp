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

#include "xcom_log.h"

#include "xcom_xlog.h"

//extern void extern_xcom_log(xcom_log_level level, const char *filename , const char *funcname, int line, const char *format, ...)
//{
//    va_list valist;
//    va_start(valist, format);
//    xcom::XLog::sharedInstance().appendLog(level, filename, funcname, line, format, valist);
//    va_end(valist);
//}

using namespace XCom_NameSpace;

int main()
{
    
    XLog::sharedInstance().openLog(xcom_log_mode_async, "/Users/alexichen/UnixSpace/XCom/mmap", "xlog");
    
    
    
//    extern_xcom_log(1, "2", "main", 12, "adsfasdf %d", 1);
   
    return 0;
}
