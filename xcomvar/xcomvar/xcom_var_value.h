//
//  xcom_var_value.hpp
//  xcomvar
//
//  Created by AlexiChen on 2018/10/19.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_var_value_hpp
#define xcom_var_value_hpp
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "xcom_var_type.h"
#ifdef __cplusplus
extern "C" {
#endif

//======================================
struct xcom_var;
typedef std::shared_ptr<xcom_var> xcom_var_ptr;
typedef std::map<std::string, xcom_var_ptr> xcom_var_dict;
typedef std::vector<xcom_var_ptr> xcom_var_vec;

typedef union xcom_var_value
{
    bool            bool_val;
    int8_t          int8_val;
    uint8_t         uint8_val;
    int16_t         int16_val;
    uint16_t        uint16_val;
    int32_t         int32_val;
    uint32_t        uint32_val;
    int64_t         int64_val;
    uint64_t        uint64_val;
    float           float_val;
    double          double_val;
    std::string     string_val;
    xcom_var_buf    buf_val;
    void            *ptr_val;
    void            *ref_val;
    xcom_var_dict   *dict_val;
    xcom_var_vec    *array_val;
    xcom_var_ptr    var_val;
    
public:
    xcom_var_value();
    ~xcom_var_value();
    void reset();
    
public:
    inline xcom_var_value &operator = (const xcom_var_value &value)
    {
        memcpy(this, &value, sizeof(value));
        return *this;
    }
public:
    
    // dict action
    bool contains(const char *key);
    xcom_var_ptr get(const char *key);
    void put(const char *key, xcom_var value);
}xcom_var_value;
    
#ifdef __cplusplus
}
#endif

#endif /* xcom_var_value_hpp */
