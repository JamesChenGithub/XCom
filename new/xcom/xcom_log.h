#ifndef XCOM_LOG_H_
#define XCOM_LOG_H_

#include "xcom_sys_def.h"
#include "xcom_config.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    enum xcom_log_level
    {
        xcom_log_level_none,     // 关掉日志
        xcom_log_level_error,    // 错误日志
        xcom_log_level_warn,     // 警告日志
        xcom_log_level_info,     // 信息日志
        xcom_log_level_debug,    // 调试日志
        xcom_log_level_verbose,  // 所有信息
    };
    
#if XCOM_LOG_DISABLE
    
#define xcom_log_error(fmt, ...)
#define xcom_log_warn(fmt, ...)
#define xcom_log_info(fmt, ...)
#define xcom_log_debug(fmt, ...)
#define xcom_log_verbose(fmt, ...)
#define xcom_log(fmt, ...)
    
#else
    
    extern void extern_xcom_log(xcom_log_level level, const char *filename , const char *funcname, int line, const char *tag, const char *format, ...);
    
#if XCOM_OS_WIN
#define __FILENAME__ (strrchr(__FILE__, '\\') + 1)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') + 1)
#endif
    
#define xcom_log_error(fmt, ...)    extern_xcom_log(xcom_log_level_error, __FILENAME__, __FUNCTION__, __LINE__, tag, fmt, ##__VA_ARGS__)
#define xcom_log_warn(fmt, ...)     extern_xcom_log(xcom_log_level_warn, __FILENAME__, __FUNCTION__, __LINE__, tag, fmt, ##__VA_ARGS__)
#define xcom_log_info(fmt, ...)     extern_xcom_log(xcom_log_level_info, __FILENAME__, __FUNCTION__, __LINE__, tag, fmt, ##__VA_ARGS__)
#define xcom_log_debug(fmt, ...)    extern_xcom_log(xcom_log_level_debug, __FILENAME__, __FUNCTION__, __LINE__, tag, fmt, ##__VA_ARGS__)
#define xcom_log_verbose(fmt, ...)  extern_xcom_log(xcom_log_level_verbose, __FILENAME__, __FUNCTION__, __LINE__, tag, fmt, ##__VA_ARGS__)
#define xcom_log(fmt, ...)          xcom_log_debug(fmt, ...)
    
#endif
    
#ifdef __cplusplus
}
#endif
#endif /* XCOM_LOG_H_ */
