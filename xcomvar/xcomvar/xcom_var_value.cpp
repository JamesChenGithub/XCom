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
namespace xcom {
    extern "C" {
#endif
        xcom_var_value::xcom_var_value()
        {
            memset(this, 0, sizeof(xcom_var_value));
            
        }
        xcom_var_value::~xcom_var_value()
        {
            
        }
        
        
#ifdef __cplusplus
    }
}
#endif
