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
        xcom_var_value  *obj = nullptr;
        xcom_var_type   type = xcom_vtype_null;
    private:
        int             retaincount = 0;
        bool            child;
    public:
        ~xcom_var();
        xcom_var();
    public:
        /* basic types */
        #define XCOM_VAR_FUNC(T, VT, VAL) \
        inline xcom_var(T value):xcom_var() { this->type = xcom_vtype_##VT;  this->obj->VT##_val = value; } \
        inline operator T() {return this->obj && this->type == xcom_vtype_##VT ? this->obj->VT##_val : VAL; } \
        inline T VT##_val() const {return this->obj ? this->obj->VT##_val : VAL; } \
        inline xcom_var &operator = (T value) { \
            this->type = xcom_vtype_##VT;\
            this->obj->reset(); \
            this->obj->VT##_val = value;\
            return *this;\
        }\
        inline bool operator == (const T value) const { \
            return this->type != xcom_vtype_##VT  ?  VAL : this->obj->VT##_val == value;\
        }
        
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
        
        xcom_var(const xcom_var *val) : xcom_var() { if(val) { this->type = val->type; *(this->obj) = *(val->obj); } }
        xcom_var(const xcom_var &val) : xcom_var() { this->type = val.type;  *(this->obj) = *(val.obj);}
        xcom_var(xcom_var &&val) : xcom_var() { this->type = val.type;  this->obj = std::move(val.obj); val.type = xcom_vtype_null; val.obj = nullptr;}
        
        inline xcom_var &operator = (const xcom_var &value) {
            this->type = this->type = value.type;
            this->obj->reset();
            *(this->obj) = *(value.obj);
            return *this;
        }
        inline xcom_var &operator = (xcom_var &&value) {
            this->type = value.type;
            this->obj->reset();
            this->obj = std::move(value.obj);
            value.type = xcom_vtype_null;
            value.obj = nullptr;
            return *this;
        }
        
    
        inline xcom_var(const std::string &str):xcom_var() { this->type = xcom_vtype_string; this->obj->string_val = str; };
        inline xcom_var(const char *cstr):xcom_var() { this->type = xcom_vtype_string; this->obj->string_val = cstr; };
        
        inline operator const char *() const {return this->obj && this->type == xcom_vtype_string ? this->obj->string_val.c_str() : ""; }
        inline operator std::string() const {return this->obj && this->type == xcom_vtype_string ? this->obj->string_val.c_str() : std::string(""); }
        
        inline const char *cstr_val() const  {return this->obj && this->type == xcom_vtype_string ? this->obj->string_val.c_str() : ""; }
        inline std::string string_val() const {return this->obj && this->type == xcom_vtype_string ? this->obj->string_val : std::string(""); }
        
        inline xcom_var &operator= (const char *cstr) {this->type = xcom_vtype_string; this->obj->reset(); this->obj->string_val = cstr; return *this; }
        inline xcom_var &operator= (const std::string &str) {this->type = xcom_vtype_string; this->obj->reset(); this->obj->string_val = str; return *this; }
        
        bool operator == (const char *cstr) const {
            return this->type != xcom_vtype_string && cstr ?  false : this->obj->string_val == std::string(cstr);
        }
        bool operator == (const std::string str) const {
            return this->type != xcom_vtype_string  ?  false : this->obj->string_val == str;
        }
        
    public:
        /* dict */
        xcom_var* operator[](const char *key) {
            if (!key || !*key)
                return nullptr;
            
            if (this->type != xcom_vtype_dict)
                init_vdict();
            
            if (!this->contains(key))
                put(key, xcom_var(0));
            
            xcom_var_ptr ptr = get(key);
            printf("xcom_var_ptr get ptr = %p  str : %s\n", ptr, ptr->val_str());
            return ptr;
        }
        bool contains(const char *key)
        {
            if (this->type != xcom_vtype_dict) return false;
            return this->obj->contains(key);
        }

    private:
        void init_vdict()
        {
            if (this->type != xcom_vtype_dict)
            {
                this->type = xcom_vtype_dict;
                delete this->obj;
                this->obj = nullptr;
                this->obj = new xcom_var_value;
                this->obj->dict_val = new xcom_var_dict;
            }
        }
        
        /* 'key-value' dictionary methods */
        void put(const char *key, xcom_var data) {
            init_vdict();
            this->obj->put(key, data);
        }
        
        xcom_var_ptr get(const char *key) {
            auto ptr = this->obj->get(key);
            printf("get ptr = %p\n", ptr);
            return ptr;
        }
    public:
        /* array */
    public:
        /* buffer */
    public:
        
        const char *to_type_json()
        {
            return "";
        }
        
        const char *to_json()
        {
            if (this->is_number() )
            {
                return this->val_str();
            }
            else
            {
                
            }
            return "";
        }
        
        const char *val_str() const
        {
            
            std::string typestr = xcom_var_type_string(this->type);
            std::string valstr = "" ;
            switch(this->type)
            {
                case xcom_vtype_null: { valstr = "null"; break; };
                case xcom_vtype_bool: { valstr = this->bool_val() ? 1 : 0; break; };
                case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); break;};
                case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); break;};
                case xcom_vtype_int16: { valstr = std::to_string(this->int8_val()); break;};
                case xcom_vtype_uint16: { valstr = std::to_string(this->int16_val()); break;};
                case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); break;};
                case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); break;};
                case xcom_vtype_int64: { valstr = std::to_string(this->uint64_val()); break;};
                case xcom_vtype_uint64: { valstr = std::to_string(this->int64_val()); break;};
                case xcom_vtype_float: { valstr = std::to_string(this->float_val()); break;};
                case xcom_vtype_double: { valstr = std::to_string(this->double_val()); break;};
                case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; break;};
                case xcom_vtype_bytes: {  break;};
                case xcom_vtype_array: {  break;};
                case xcom_vtype_dict: {  break;};
                case xcom_vtype_var: { valstr = this->obj->var_val->val_str(); break;};
                case xcom_vtype_ref: { valstr = std::to_string(this->int8_val()); break;};
            }
            
            std::string str = "{ \"" + typestr + "\" : " + valstr + " }";
            return str.c_str();
        }
        
    public:
        inline bool is_number() const { return this->type <= xcom_vtype_string; }
        inline bool is_array() const { return this->type == xcom_vtype_array; }
        inline bool is_dict() const { return this->type == xcom_vtype_dict;}
        

    }xcom_var, xcom_var_t;
    
#ifdef __cplusplus
}
#endif



#endif
