#ifndef XCOM_TYPE_DEF_H
#define XCOM_TYPE_DEF_H

#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#if defined(XC_ENABLE_EXPORT)
    
#if defined(WIN32)
    
#if defined(XC_IMPLEMENTATION)
    #define xcom_export __declspec(dllexport)
#else
    #define xcom_export __declspec(dllimport)
#endif /* defined(XC_IMPLEMENTATION) */
    
#else /* defined(WIN32) */
#if defined(XC_IMPLEMENTATION)
    #if ((defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__))
        #define xcom_export __attribute__((visibility("default")))
    #else
        #define xcom_export
    #endif
#else
    #define xcom_export
#endif /* defined(XC_IMPLEMENTATION) */
#endif
    
#else /* defined(XC_ENABLE_EXPORT) */
#define xcom_export
#endif
    
#ifndef xcom_null
#ifdef __cplusplus
#ifndef nullptr
#define xcom_null        (0)
#else /* nullptr */
#define xcom_null        nullptr
#endif /* nullptr */
#else /* !__cplusplus */
#define xcom_null        ((void*) 0)
#endif /* !__cplusplus */
#endif
    
    
#if defined(__GNUC__)
#define xcom_weak_func     __attribute__((weak))
#elif defined(_MSC_VER) && !defined(_LIB)
#define xcom_weak_func /*__declspec(selectany)*/
#else
#define xcom_weak_func
#endif
    

    
#ifndef xcom_not_used
#ifdef __GNUC__
#define xcom_not_used __attribute__ ((unused))
#else
#define xcom_not_used
#endif
#endif
    


#define xcom_required
    
#define xcom_optional
    
#define xcom_extern extern
    

    
#ifdef __cplusplus
}
#endif


#endif /*XCOM_TYPE_DEF_H*/

