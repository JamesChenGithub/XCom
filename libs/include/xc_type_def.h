#ifndef XCOM_BASE_XCTYPEDEF_H
#define XCOM_BASE_XCTYPEDEF_H

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
#define xc_export __declspec(dllexport)
#else
#define xc_export __declspec(dllimport)
#endif /* defined(XC_IMPLEMENTATION) */
    
#else /* defined(WIN32) */
#if defined(XC_IMPLEMENTATION)
#if ((defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__))
#define xc_export __attribute__((visibility("default")))
#else
#define xc_export
#endif
#else
#define xc_export
#endif /* defined(XC_IMPLEMENTATION) */
#endif
    
#else /* defined(XC_ENABLE_EXPORT) */
#define xc_export
#endif
    
#ifndef xc_null
#ifdef __cplusplus
#ifndef nullptr
#define xc_null        (0)
#else /* nullptr */
#define xc_null        nullptr
#endif /* nullptr */
#else /* !__cplusplus */
#define xc_null        ((void*) 0)
#endif /* !__cplusplus */
#endif
    
#ifdef __cplusplus
}
#endif

#endif

