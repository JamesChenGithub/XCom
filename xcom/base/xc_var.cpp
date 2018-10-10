#include "xc_var.h"
#include <string>

typedef struct xcvar_buf_s{
    void        *buf;
    uint32_t    len;
}xcvar_buf_t;

typedef union xcvar_base_val_u
{
    bool            b;
    int8_t          i8;
    uint8_t         u8;
    int16_t         i16;
    uint16_t        u16;
    int32_t         i32;
    uint32_t        u32;
    int64_t         i64;
    uint64_t        u64;
    float           f;
    double          d;
    std::string     str;
    xcvar_buf_t     buf;
    void            *ptr;
}xcvar_base_val;



typedef union xcvar_obj_u
{
    xcvar_base_val base;
    xcvar_base_val array;
    xcvar_base_val dic;
}xcvar_obj;

typedef struct xcvar_val_t
{
    xcvar_type  type;
    xcvar_obj   obj;
}xcvar_val_s;


typedef struct xc_var_t
{
    std::string     key;
    xcvar_val_s     value;
}xc_var_s;




