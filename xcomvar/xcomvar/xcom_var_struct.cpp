#include "xcom_var_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    
    //==============================
    static int xcom_var_new_count = 0;
    xcom_var::~xcom_var()
    {
        printf("var_struct dealloc [%d]: [%p]  : [obj = %p]\n", --xcom_var_new_count, this, this->obj);
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
                if (this->obj->dict_val)
                {
//                    auto it = this->obj->array_val->begin();
//                    auto end = this->obj->array_val->end();
//                    while(it != end){
//                        it->reset();
//                        it++;
//                    }
                    this->obj->array_val->clear();
                    delete this->obj->array_val;
                    this->obj->array_val = nullptr;
                }
                
                break;
            }
            case xcom_vtype_dict:
            {
                if (this->obj->dict_val)
                {
//                    auto it = this->obj->dict_val->begin();
//                    auto end = this->obj->dict_val->end();
//                    while(it != end){
//                        it->second.reset();
//                        it++;
//                    }
                    this->obj->dict_val->clear();
                    delete this->obj->dict_val;
                    this->obj->dict_val = nullptr;
                }
                break;
            }
            case xcom_vtype_bytes:
            {
                 if (this->obj->buf_val)
                 {
                     delete this->obj->buf_val;
                     this->obj->buf_val = nullptr;
                 }
                break;
            }
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
        this->retaincount = 0;
        this->child = false;
        printf("var_struct new [%d]: [%p] \n", ++xcom_var_new_count, this);
    }
#ifdef __cplusplus
}
#endif
