#include "xcom_var_struct.h"

#ifdef __cplusplus
extern "C" {
#endif
    const char *xcom_var_type_string(xcom_var_type type)
    {
        switch(type)
        { 
            // case xcom_vtype_ptr:
            case xcom_vtype_ref:  return "ref";
            case xcom_vtype_array: return "array";
            case xcom_vtype_dict: return "dic";
            case xcom_vtype_null: return "null";
            case xcom_vtype_bool: return "bool";
            case xcom_vtype_int8: return "int8";
            case xcom_vtype_uint8: return "uint8";
            case xcom_vtype_int16: return "int16";
            case xcom_vtype_uint16: return "uint16";
            case xcom_vtype_int32: return "int32";
            case xcom_vtype_uint32: return "uint32";
            case xcom_vtype_int64: return "int64";
            case xcom_vtype_uint64: return "uint64";
            case xcom_vtype_float: return "float";
            case xcom_vtype_double: return "double";
            case xcom_vtype_string: return "string";
            case xcom_vtype_bytes: return "byte";
//            case xcom_vtype_variant: return "var";
        }
        return "";
    }
    
    //======================================
    
    xcom_var_buf::xcom_var_buf() {
        this->buf = nullptr;
        this->buf = 0;
    }
    
    xcom_var_buf::xcom_var_buf(void *buf, uint32_t len) {
        this->buf = nullptr;
        this->buf = 0;
        
        if(buf && len > 0)
        {
            void *abuf = malloc(len);
            if (abuf)
            {
                memcpy(this->buf, buf, len);
                this->buf = abuf;
                this->len = len;
            }
        }
    }
    
    xcom_var_buf::~xcom_var_buf()
    {
        if (this->buf)
        {
            free(buf);
            this->buf = nullptr;
            this->len = 0;
        }
    }
    
    //==============================
    xcom_var_value::xcom_var_value()
    {
        memset(this, 0, sizeof(xcom_var_value));
    }
    xcom_var_value::~xcom_var_value()
    {
        
    }
    void xcom_var_value::reset()
    {
        //memset(this, 0, sizeof(xcom_var_value));
//        this->bool_val  = false;
//        this->int8_val = 0;
//        this->uint8_val = 0;
//        this->int16_val = 0;
//        this->uint16_val = 0;
//        this->int32_val = 0;
//        this->uint32_val = 0;
//        this->int64_val = 0;
//        this->uint64_val = 0;
//        this->float_val = 0;
//        this->double_val = 0;
//        this->string_val = "";
//        this->buf_val = {nullptr, 0};
//        this->ptr_val = nullptr;
//        this->ref_val = nullptr;
//        this->dic_val = nullptr;
//        this->array_val = nullptr;
//        this->var_val = nullptr;
    }
    
    
    //==============================
    xcom_var::~xcom_var()
    {
        printf("[%p] dealloc : %s\n", this, this->val_str());
        switch(this->type)
        {
                
                //                case xcom_vtype_ptr:
                //                {
                //                    if( this->obj->ptr_val)
                //                    {
                //                        delete this->obj->ptr_val;
                //                        this->obj->ptr_val = nullptr;
                //                    }
                //                    break;
                //                }
            case xcom_vtype_ref:
            {
                this->obj->ref_val = nullptr;
                break;
            }
            case xcom_vtype_array:
            {
                if(this->obj->array_val)
                {
                    
                }
                break;
            }
            case xcom_vtype_dict:
            {
                if(this->obj->dic_val)
                {
                    
                }
                break;
            }
                break;
            case xcom_vtype_null:
            case xcom_vtype_bool:
            case xcom_vtype_int8:
            case xcom_vtype_uint8:
            case xcom_vtype_int16:
            case xcom_vtype_uint16:
            case xcom_vtype_int32:
            case xcom_vtype_uint32:
            case xcom_vtype_int64:
            case xcom_vtype_uint64:
            case xcom_vtype_float:
            case xcom_vtype_double:
            case xcom_vtype_string:
            case xcom_vtype_bytes:
//            case xcom_vtype_variant:
            default:
            {
                this->retaincount--;
                if (this->retaincount <= 0)
                {
                    if (obj)
                    {
                        delete obj;
                        obj = nullptr;
                    }
                    
                }
                
                
                break;
            }
                
        }
        
    }
    
    xcom_var::xcom_var()
    {
        this->obj = new xcom_var_value;
        this->type = xcom_vtype_null;
        this->retaincount = 1;
    }
#ifdef __cplusplus
}
#endif
