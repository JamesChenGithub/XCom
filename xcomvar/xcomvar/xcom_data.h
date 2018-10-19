//
//  xcom_data.hpp
//  xcomvar
//
//  Created by AlexiChen on 2018/10/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xcom_data_hpp
#define xcom_data_hpp

#include <stdio.h>

namespace xcom {
    
    typedef struct xcom_var  xcom_var_t;
    class xcast_data
    {
    private:
        
    public:
        xcom_var_t *_value;
        bool _child;
    };
    
}

#endif /* xcom_data_hpp */
