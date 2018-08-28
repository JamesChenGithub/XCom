#ifndef XCOM_BASE_XCVAR_H
#define XCOM_BASE_XCVAR_H

#include "xctypedef.h"
#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum {
        xcvar_null = 0,
        xcvar_bool = 'b',
        xcvar_uint8 = 'y',
        xcvar_int16 = 'n',
        xcvar_uint16 = 'q',
        xcvar_int32 = 'i',
        xcvar_uint32 = 'u',
        xcvar_int64 = 'x',
        xcvar_uint64 = 't',
        xcvar_float = 'f',
        xcvar_double = 'd',
        xcvar_string = 'c',
        xcvar_bytes = 'm',
        xcvar_ptr = '*',
        xcvar_array = '[',
        xcvar_dict = '{',
        xcvar_variant = 'v'
    } xcvar_type;
    
    union xcvar_value
    {
        bool b;
    }xcvar_value;
    
    struct xcvar
    {
        std::string key;
        xcvar_type type;
        
        
    }xcvar;
    
#ifdef __cplusplus
}
#endif
#endif
