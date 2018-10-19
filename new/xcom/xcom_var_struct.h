#ifndef XCOM_VAR_STRUCT_H
#define XCOM_VAR_STRUCT_H

#include <string>
#include <map>
#include <vector>
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif
    //======================================
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
        xcom_vtype_bytes     = 'm',
//        xcom_vtype_ptr       = '*',
        xcom_vtype_ref       = '&',
        xcom_vtype_array     = '[',
        xcom_vtype_dict      = '{',
//        xcom_vtype_var       = 'v',
        
        
    } xcom_var_type;
    
    const char *xcom_var_type_string(xcom_var_type type);
    //======================================
    
    typedef struct xcom_var_buf{
        void        *buf;
        uint32_t    len;
        
    public:
        xcom_var_buf();
        xcom_var_buf(void *buf, uint32_t len);
        ~xcom_var_buf();
        
    }xcom_var_buf;
    
    //======================================
    struct xcom_var;
    typedef std::map<std::string, std::shared_ptr<xcom_var>> xcom_var_dic;
    typedef std::vector<std::shared_ptr<xcom_var>> xcom_var_vec;
    
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
        xcom_var_dic    *dic_val;
        xcom_var_vec    *array_val;
        xcom_var        *var_val;
        
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
    }xcom_var_value;
    
    
    typedef struct xcom_var
    {
    public:
        xcom_var_value  *obj = nullptr;
    private:
        xcom_var_type   type = xcom_vtype_null;
        int             retaincount = 0;
    public:
        ~xcom_var();
        xcom_var();
    public:
        
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
        
        xcom_var(const xcom_var &val) : xcom_var() { this->type = val.type;  *(this->obj) = *(val.obj);}
        xcom_var(xcom_var &&val) : xcom_var() { this->type = val.type;  this->obj = std::move(val.obj); val.type = xcom_vtype_null; val.obj = nullptr;}
    
        //inline xcom_var var_val() const {return this->obj && this->type == xcom_vtype_var ? this->obj->var_val : xcom_var(); }
        
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
            return this->type != xcom_vtype_string  ?  false : this->obj->string_val == std::string(cstr);
        }
        bool operator == (const std::string str) const {
            return this->type != xcom_vtype_string  ?  false : this->obj->string_val == str;
        }
        
//        xcom_var(void *buf, uint32_t len):xcom_var() { this->type = xcom_vtype_bytes; this->obj->buf_val = xcom_var_buf(buf, len); };
//        xcom_var(void *ref):xcom_var() { this->type = xcom_vtype_bytes; this->obj->ref_val = ref; };
        
    public:
        
        const char *to_type_json()
        {
            return "";
        }
        
        const char *to_json()
        {
            return "";
        }
        
        const char *val_str() const
        {
            
            std::string typestr = xcom_var_type_string(this->type);
            std::string valstr = "" ;
            switch(type)
            {
                // case xcom_vtype_ptr:
                case xcom_vtype_null: { valstr = "null"; break; };
                case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; break; };
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
                case xcom_vtype_string: { valstr = this->string_val(); break;};
                case xcom_vtype_bytes: {  break;};
                case xcom_vtype_array: {  break;};
                case xcom_vtype_dict: {  break;};
//                case xcom_vtype_var: { valstr = this->obj->var_val->val_str(); break;};
                case xcom_vtype_ref: { valstr = std::to_string(this->int8_val()); break;};
            }
            
            std::string str = "{" + typestr + ":" + valstr + "}";
            return str.c_str();
        }
        

    }xcom_var, xcom_var_t;
    
#ifdef __cplusplus
}
#endif



#endif
