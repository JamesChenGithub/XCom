#include "xcom_var_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    
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
                
                break;
            }
            case xcom_vtype_dict:
            {
                
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
        this->child = false;
    }
#ifdef __cplusplus
}
#endif
