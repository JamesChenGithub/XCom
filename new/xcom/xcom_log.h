#ifndef XCOM_LOG_H_
#define XCOM_LOG_H_

#include "xcom_sys_def.h"
#include "xcom_type_def.h"
#include "xcom_config.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    
    enum xcom_log_mode{
        xcom_log_mode_async = 0,
        xcom_log_mode_sync,
    };
    
    enum xcom_log_level
    {
        xcom_log_level_verbose,  // 所有信息
        xcom_log_level_debug,    // 调试日志
        xcom_log_level_info,     // 信息日志
        xcom_log_level_warning,  // 警告日志
        xcom_log_level_error,    // 错误日志
        xcom_log_level_fatal,    // 错误日志
        xcom_log_level_none,     // 关掉日志
    };
    
    typedef void (*xcom_xlog_crypt_hook)(const void* _data, size_t _inputlen, void* _output, size_t& _len);
    typedef void (*xcom_xlog_hook)(const char *time, xcom_log_level level, const char *filename , const char *funcname, int line, int pid, int tid, int mid, const char *format, const char *logcontent);
    
#if XCOM_LOG_ENABLE
    
    xcom_extern void extern_xcom_log_append(xcom_log_level level, const char *filename , const char *funcname, int line, const char *format, ...);
    
#if XCOM_OS_WIN
    #define __FILENAME__ (strrchr(__FILE__, '\\') + 1)
#else
    #define __FILENAME__ (strrchr(__FILE__, '/') + 1)
#endif
    
#define xcom_log_error(fmt, ...)    extern_xcom_log_append(xcom_log_level_error, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define xcom_log_warn(fmt, ...)     extern_xcom_log_append(xcom_log_level_warn, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define xcom_log_info(fmt, ...)     extern_xcom_log_append(xcom_log_level_info, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define xcom_log_debug(fmt, ...)    extern_xcom_log_append(xcom_log_level_debug, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define xcom_log_verbose(fmt, ...)  extern_xcom_log_append(xcom_log_level_verbose, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define xcom_log          xcom_log_debug
    
#else
    
#define xcom_log_error(fmt, ...)
#define xcom_log_warn(fmt, ...)
#define xcom_log_info(fmt, ...)
#define xcom_log_debug(fmt, ...)
#define xcom_log_verbose(fmt, ...)
#define xcom_log(fmt, ...)
    
    
#endif
    
#ifdef __cplusplus
}
#endif
#endif /* XCOM_LOG_H_ */
