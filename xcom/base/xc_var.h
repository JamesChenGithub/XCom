#ifndef XCOM_BASE_XCVAR_H
#define XCOM_BASE_XCVAR_H

#include "xc_type_def.h"
#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum xcvar_type{
        xcvar_null      = 0,
        xcvar_bool      = 'b',
        xcvar_int8      = 'Y',
        xcvar_uint8     = 'y',
        xcvar_int16     = 'n',
        xcvar_uint16    = 'N',
        xcvar_int32     = 'i',
        xcvar_uint32    = 'I',
        xcvar_int64     = 'x',
        xcvar_uint64    = 'X',
        xcvar_float     = 'f',
        xcvar_double    = 'D',
        xcvar_string    = 'c',
        xcvar_bytes     = 'm',
        xcvar_ptr       = '*',
        xcvar_array     = '[',
        xcvar_dict      = '{',
        xcvar_variant   = 'v'
    } xcvar_type;

    
#ifdef __cplusplus
}
#endif
#endif
