//
//  xcom_var_type.h
//  xcomvar
//
//  Created by AlexiChen on 2018/10/19.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_type_h
#define xcom_var_type_h

#include <string>
#include <map>
#include <vector>
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    xcom_vtype_null      = 0,
    xcom_vtype_bool      = 'b',
    xcom_vtype_int8      = 'Y',
    xcom_vtype_uint8     = 'y',
    xcom_vtype_int16     = 'n',
    xcom_vtype_uint16    = 'N',
    xcom_vtype_int32     = 'i',
    xcom_vtype_uint32    = 'I',
    xcom_vtype_int64     = 'x',
    xcom_vtype_uint64    = 'X',
    xcom_vtype_float     = 'f',
    xcom_vtype_double    = 'D',
    xcom_vtype_string    = 'c',
    xcom_vtype_ref       = '&',
    //        xcom_vtype_ptr       = '*',
    xcom_vtype_bytes     = 'm',
    xcom_vtype_array     = '[',
    xcom_vtype_dict      = '{',
    xcom_vtype_vptr      = 'v',
} xcom_var_type;

const char *xcom_var_type_string(xcom_var_type type);
    
    
    typedef struct xcom_var_buf{
        void        *buf;
        uint32_t    len;
        
    public:
        xcom_var_buf();
        xcom_var_buf(const void *buf, uint32_t len);
        ~xcom_var_buf();
        const char *to_json() const
        {
            char buf[128];
            sprintf(buf, "{\"buf\" : \"%p\", \"len\" : \"%u\"}", buf, len);
            std::string json = buf;
            return json.c_str();
        }
        
    }xcom_var_buf;
    
#ifdef __cplusplus
}
#endif

#endif /* xcom_var_type_h */
