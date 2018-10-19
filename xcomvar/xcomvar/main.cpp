//
//  main.m
//  xcomvar
//
//  Created by AlexiChen on 2018/10/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#import "xcom_data.h"
#include "xcom_var_struct.h"
#include <iostream>


int main(int argc, const char * argv[])
{
//    {
//        std::cout<<sizeof(xcom_var_value) << "    " << sizeof(double) <<  "    "<<  sizeof(uint64_t)<<  "    " << sizeof(std::string) <<  "    " << sizeof(std::shared_ptr<std::string>)<< "    " << sizeof(xcom_var_buf) << std::endl;;
//    }
//    {
//        xcom_var var;
//        var = false;
//    }
//    {
//        xcom_var var(false);
//        var = 8;
//    }
//    
//    {
//        xcom_var var(false);
//        
//        var = "1234";
//        std::cout << var.val_str() << std::endl;
//        var = 2;
//        std::cout << var.val_str() << std::endl;
//        var = 2.5f;
//        std::cout << var.val_str() << std::endl;
//        var = "121212";
//        std::cout << var.val_str() << std::endl;
//        var = 5.0;
//        std::cout << var.val_str() << std::endl;
//        var = 5u;
//        std::cout << var.val_str() << std::endl;
//        var = (uint64_t)5;
//        std::cout << var.val_str() << std::endl;
//        var = true;
//        std::cout << var.val_str() << std::endl;
//        
//        xcom_var a("adasdf");
//        var = a;
//        
//        std::cout << var.val_str() << std::endl;
//        
//        xcom_var ab("adasdfadadsasdf");
//        var = std::move(ab);
//        
//        var = 123u;
//        
//        std::cout << var.val_str() << std::endl;
//    }
    
    {
        xcom_var var;
        var["enable"] = true;
        
        bool enable = var["enable"];
        
        std::cout << (enable ? "true" : "false") <<  var.val_str() << std::endl;
    }
    
    getchar();
    
    return 0;
}
