#ifndef XCOM_VAR_STRUCT_H
#define XCOM_VAR_STRUCT_H

#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "xcom_var_type.h"
#include "xcom_var_value.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    union xcom_var_value;
    typedef struct xcom_var
    {
    public:
        xcom_var_value  obj;
        xcom_var_type   type = xcom_vtype_null;

    public:
        ~xcom_var();
        xcom_var();
    public:
        /* basic types */
        #define XCOM_VAR_FUNC(T, VT, VAL) \
        inline xcom_var(T value):xcom_var() { this->type = xcom_vtype_##VT;  this->obj.VT##_val = value; } \
        inline operator T() {return this->obj.VT##_val; } \
        inline T VT##_val() const {return this->obj.VT##_val; } \
        xcom_var &operator = (T value) { \
            this->reset();\
            if (this->type == xcom_vtype_vptr) {\
                xcom_var_ptr ptr = this->var_val();\
                *ptr = value;\
            } else {\
                this->type = xcom_vtype_##VT;\
                this->obj.VT##_val = value;\
            }\
            return *this;\
        }\
        inline bool operator == (const T value) const { \
            return this->type != xcom_vtype_##VT  ?  false : this->obj.VT##_val == value;\
        }
        
//        inline xcom_var(bool value):xcom_var() {
//            this->type = xcom_vtype_bool;
//            this->obj.bool_val = value;
//        }
//        inline operator bool() {
//            return this->obj.bool_val;
//        }
//        inline bool bool_val() const {
//            return this->obj.bool_val;
//        }
//        inline xcom_var &operator = (bool value) {
//            this->reset();
//            if (this->type == xcom_vtype_vptr)
//            {
//                xcom_var_ptr ptr = this->var_val();
//                printf("ptr = %p  %s\n", ptr.get(), ptr->to_json());
//                *ptr = value;
//                printf("ptr = %p  %s\n", ptr.get(), ptr->to_json());
//            }
//            else
//            {
//                this->type = xcom_vtype_bool;
//                this->obj.bool_val = value;
//            }
//            return *this;
//        }
//
//        inline bool operator == (const bool value) const {
//            return this->type != xcom_vtype_bool  ?  false : this->obj.bool_val == value;
//        }
        
        
        XCOM_VAR_FUNC(bool, bool, false)
        XCOM_VAR_FUNC(int8_t, int8, 0)
        XCOM_VAR_FUNC(uint8_t, uint8, 0)
        XCOM_VAR_FUNC(int16_t, int16, 0)
        XCOM_VAR_FUNC(uint16_t, uint16, 0)
        XCOM_VAR_FUNC(int32_t, int32, 0)
        XCOM_VAR_FUNC(uint32_t, uint32, 0)
        XCOM_VAR_FUNC(int64_t, int64, 0)
        XCOM_VAR_FUNC(uint64_t, uint64, 0)
        XCOM_VAR_FUNC(float, float, 0.0)
        XCOM_VAR_FUNC(double, double, 0.0)
        XCOM_VAR_FUNC(void *, ref, NULL)
        
        
        
        // string
        xcom_var(const std::string &str);
        xcom_var(const char *cstr);
        
        operator const char *() const;
        operator std::string() const;
        
        const char *cstr_val() const;
        std::string string_val() const;
        
        xcom_var &operator= (const char *cstr);
        xcom_var &operator= (const std::string &str);
        
        bool operator == (const char *cstr) const;
        bool operator == (const std::string str) const;
        
        // copy and =
        xcom_var(const xcom_var &val) : xcom_var() {
            this->reset(val);
        }
        xcom_var(xcom_var *val) : xcom_var() {
            if (val)
            {
                this->reset(*val);
            }
        }
        
        xcom_var(xcom_var &&val) : xcom_var() {
            this->reset(std::move(val));
        }
        
        inline xcom_var &operator = (const xcom_var &value) {
            this->reset(value);
            return *this;
        }
        inline xcom_var &operator = (xcom_var &&value) {
            this->reset(std::move(value));
            return *this;
        }
        
        
        inline xcom_var(xcom_var_ptr value):xcom_var() {
            this->type = xcom_vtype_vptr;
            this->obj.var_val = value;
//            printf("var ptr construct:%s  %s\n", this->to_json(), this->var_val()->to_json());
        }
        inline operator xcom_var_ptr() {
            if (this->type == xcom_vtype_vptr) {
                return this->obj.var_val;
            }
            return nullptr;
        }
        inline xcom_var_ptr var_val() const {
            if (this->type == xcom_vtype_vptr) {
                return this->obj.var_val;
            }
            return nullptr;
        }
        inline xcom_var &operator = (xcom_var_ptr value) {
            this->type = xcom_vtype_vptr;
            this->reset();
            this->obj.var_val = value;
            return *(this->obj.var_val.get());
        }
        inline bool operator == (const xcom_var_ptr value) const {
            return this->type != xcom_vtype_vptr  ?  false : this->obj.var_val == value;
        }
    
        
        
    private:
        void reset();
        void reset(const xcom_var &var);
        void reset(xcom_var &&var);
        
    
    public:
        /* array */
        xcom_var_ptr operator[](uint32_t index);
        
        /* 'index' based array methods */
        void append(xcom_var data);
    private:

        /* 'index' based array methods */
        xcom_var_ptr at(uint32_t index);
        
        void init_varray();
    public:
        /* dict */
        xcom_var_ptr operator[](const char *key);
        bool contains(const char *key);
        
        bool erase(const char *key);
    private:
        void init_vdict();
        
        /* 'key-value' dictionary methods */
        void put(const char *key, xcom_var &&data);
        
        xcom_var_ptr get(const char *key);
   
    public:
        /* buffer */
        void set_buffer(const void *data, uint32_t len);
    public:
        
        std::string to_json() const;
        
    public:
        inline bool is_number() const { return this->type <= xcom_vtype_string; }
        inline bool is_array() const { return this->type == xcom_vtype_array; }
        inline bool is_dict() const { return this->type == xcom_vtype_dict;}
        
        // just array or dict vaild, return empty;
        // other return false
        bool empty();
        
        // just array or dict vaild, return size;
        // other return 1
        uint32_t size();
        

    }xcom_var, xcom_var_t;
    
#ifdef __cplusplus
}
#endif



#endif
