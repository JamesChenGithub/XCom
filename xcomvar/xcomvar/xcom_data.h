//
//  xcom_data.hpp
//  xcomvar
//
//  Created by AlexiChen on 2018/10/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_data_hpp
#define xcom_data_hpp

#include <string>
#include <map>
#include <vector>
#include <sstream>


//namespace xcom {

    struct xcom_var;
    class xcom_data
    {
    public:
        // basic declare
        xcom_data();
        ~xcom_data();
        
        xcom_data(const xcom_data &data);
        xcom_data(xcom_data &&data);
        
        xcom_data &operator = (const xcom_data &data);
        xcom_data &operator = (xcom_data &&data);
        
    public:
        // basic type delc
        #define XCOM_DATA_DELC(T, VT, VAL) \
        xcom_data(T value);\
        operator T() const;  \
        T VT##_val() const;  \
        xcom_data &operator = (T value); \
        bool operator == (const T value) const; \

        XCOM_DATA_DELC(bool, bool, false)
        XCOM_DATA_DELC(int8_t, int8, 0)
        XCOM_DATA_DELC(uint8_t, uint8, 0)
        XCOM_DATA_DELC(int16_t, int16, 0)
        XCOM_DATA_DELC(uint16_t, uint16, 0)
        XCOM_DATA_DELC(int32_t, int32, 0)
        XCOM_DATA_DELC(uint32_t, uint32, 0)
        XCOM_DATA_DELC(int64_t, int64, 0)
        XCOM_DATA_DELC(uint64_t, uint64, 0)
        XCOM_DATA_DELC(float, float, 0.0)
        XCOM_DATA_DELC(double, double, 0.0)
        XCOM_DATA_DELC(void *, ref, NULL)
        
    public:
        // string delc
        xcom_data(const char *data);
        operator const char *() const;
        const char * string_val() const;
        xcom_data &operator = (const char *data);
        bool operator == (const char* data) const;
        
    public:
        // dict delc
        xcom_data operator[](const char *key);
        bool contains(const char *key);
        bool erase(const char *key);
        
    public:
        // array
        xcom_data operator[](uint32_t index);
    public:
        // buf
        void set_buf(const void *buf, uint32_t len);
        
    public:
        // tool
        const char *to_json();
        
        // just array or dict vaild, return empty;
        // other return false
        bool empty();
        
        // just array or dict vaild, return size;
        // other return 1
        uint32_t size();
        
    private:
        xcom_var *_core;
        xcom_data(const xcom_var *var, bool isvp);
    };
    
//}

#endif /* xcom_data_hpp */
