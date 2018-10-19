//
//  xcom_var_value.cpp
//  xcomvar
//
//  Created by AlexiChen on 2018/10/19.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xcom_var_value.h"
#include "xcom_var_struct.h"

#ifdef __cplusplus
extern "C" {
#endif
    xcom_var_value::xcom_var_value()
    {
        //memset(this, 0, sizeof(xcom_var_value));
    }
    xcom_var_value::~xcom_var_value()
    {
        
    }
    void xcom_var_value::reset()
    {
        //        memset(this, 0, sizeof(xcom_var_value));
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
    
    bool xcom_var_value::contains(const char *key)
    {
        return dict_val->find(key) != dict_val->end();
    }
    xcom_var_ptr xcom_var_value::get(const char *key)
    {
        auto it = dict_val->find(key);
        if (it == dict_val->end())
        {
            return nullptr;
        }
        printf("xcom_var_value get ptr = %p  str : %s\n", it->second, it->second->val_str());
        return it->second;
    }
    void xcom_var_value::put(const char *key, xcom_var value)
    {
        xcom_var_ptr var_ptr = new xcom_var(std::move(value));
        printf("put ptr = %p  str : %s\n", var_ptr, var_ptr->val_str());
        dict_val->insert(std::make_pair(key, var_ptr));
    }
#ifdef __cplusplus
}
#endif
