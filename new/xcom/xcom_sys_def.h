#ifndef XCOM_SYS_DEF_H
#define XCOM_SYS_DEF_H

#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#if defined(__ANDROID__) || defined (ANDROID)
#define XCOM_OS_ANDROID 1
#define XCOM_OVERRIDE
#elif (defined(_WIN32) || defined(_WIN64))
    
#if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0501)
    // here we only support Windows XP and above
#define XCOM__WIN32_WINNT 0x0501
#endif
    
#define XCOM_OS_WIN 1
#define XCOM_OVERRIDE override
    
#ifdef _MSC_VER
#pragma warning(disable:4355) // we don't need such warning C4355: 'this' : used in base member initializer list
#if _MSC_VER >= 1300 // MS VC++ 7.0 _MSC_VER = 1300
#define    __attribute__(...)
#else
#define    __attribute__(a)
#endif
#endif
    
#define _WINSOCKAPI_
#ifndef WINBASE_DECLARE_GET_MODULE_HANDLE_EX
#define WINBASE_DECLARE_GET_MODULE_HANDLE_EX
#endif
    
#include <windows.h>
#undef _WINSOCKAPI_
    
#if defined(WINAPI_FAMILY_PARTITION)
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#define XCOM_OS_WIN_DESKTOP 1
#else
#define XCOM_OS_WIN8    1
#define XCOM_OS_WIN_APP     1
#endif
#else
#define XCOM_OS_WIN_DESKTOP     1
#endif
    
    
#elif defined(__APPLE__) || defined(__MACH__)
    
#include <TargetConditionals.h>
#define OVERRIDE override
    
#if TARGET_OS_IPHONE
#define XCOM_OS_IOS 1
    
#if TARGET_IPHONE_SIMULATOR
#define XCOM_OS_IOS_SIMULATOR 1
#endif
    
#elif TARGET_OS_MAC
#define XCOM_OS_MAC 1
#else
#error Unsupported platform
#endif
    
#elif defined(__linux__) || defined(__CYGWIN__)
#define XCOM_OS_LINUX 1
    
#elif (!defined(XCOM_OS_MAC) && !defined(XCOM_OS_IOS) && !defined(XCOM_OS_ANDROID) && !defined(XCOM_OS_WIN) && !defined(XCOM_OS_LINUX))
#error current system is not supported
#endif
    
#ifdef __cplusplus
}
#endif

#endif /*XCOM_SYS_DEF_H*/
