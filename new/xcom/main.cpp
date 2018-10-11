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

//extern void extern_xcom_log(xcom_log_level level, const char *filename , const char *funcname, int line, const char *format, ...)
//{
//    va_list valist;
//    va_start(valist, format);
//    xcom::XLog::sharedInstance().appendLog(level, filename, funcname, line, format, valist);
//    va_end(valist);
//}

int main()
{
    xcom_log("aaaa");
//    extern_xcom_log(1, "2", "main", 12, "adsfasdf %d", 1);
   
    return 0;
}
