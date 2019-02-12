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

using namespace xcom;
int main(int argc, const char * argv[])
{
    {
        xcom_data var;
        
        xcom_data content;
        {
            content["sage"]=18;
            content["age"]=18;
        }
        
        var.append(content);
        std::cout << "var :" << var.to_var_json() << std::endl << std::endl;
        return 0;
        
        content["sage"]=28;
        content["age"]=28;
        var.append(content);
        
        content["sage"]=38;
        content["age"]=38;
        var.append(content);
        
        content["sage"]=48;
        content["age"]=48;
        var.append(content);
        
        
        std::cout << "var :" << var.to_var_json() << std::endl << std::endl;
        std::cout << "var :" << var.to_json() << std::endl << std::endl;
        
    }
    getchar();
    return 0;
    
    {
        xcom_data var;
        var["enable"] = true;
        xcom_data content;
        {
            content["sage"]=18;
            content["age"]=28;
        }
        
        var["content"] = content;
        var["content2"] = content;
        var["content3"] = content;
        
        content.erase("sage");
        var["haha"] = content;
        
        std::cout << "var :" << var.to_var_json() << std::endl << std::endl;
        std::cout << "var :" << var.to_json() << std::endl << std::endl;
        
    }
    
    getchar();
    return 0;
    
    
    {
        std::cout<<sizeof(xcom_var_value) << "    " << sizeof(double) <<  "    "<<  sizeof(uint64_t)<<  "    " << sizeof(std::string) <<  "    " << sizeof(std::shared_ptr<std::string>)<< "    " << sizeof(xcom_var_buf) << std::endl;;
    }
    {
        xcom_var var;
        var = false;
    }
    {
        xcom_var var(false);
        var = 8;
    }
    
    {
        xcom_var var(false);
        
        var = "1234";
        std::cout << var.to_json() << std::endl;
        var = 2;
        std::cout << var.to_var_json() << std::endl;
        var = 2.5f;
        std::cout << var.to_var_json() << std::endl;
        var = "121212";
        std::cout << var.to_var_json() << std::endl;
        var = 5.0;
        std::cout << var.to_var_json() << std::endl;
        var = 5u;
        std::cout << var.to_var_json() << std::endl;
        var = (uint64_t)5;
        std::cout << var.to_var_json() << std::endl;
        var = true;
        std::cout << var.to_var_json() << std::endl;
        
        xcom_var a("adasdf");
        var = a;
        
        std::cout << var.to_json() << std::endl;
        
        xcom_var ab("adasdfadadsasdf");
        var = std::move(ab);
        std::cout << var.to_json() << std::endl;
        var = 123u;
        
        std::cout << var.to_json() << std::endl;
    }
    
    {
        xcom_data var;        
        var["enable"] = true;
        std::string str = var.to_var_json();
        var["age"] = 100;
        std::cout << "var :" <<  str << std::endl;
        str = var.to_json();
        std::cout << "var :" <<  str << std::endl;
        
        xcom_data content;
        {
            content["age"]=18;
            content["size"]=28;
            content["house"]=38;
            content["house"]=48;
            content["desc"]="qweqwerqwerqwer";
            
            std::cout << "content : " << content.to_json() << std::endl;
        }
        
        var["content"] = content;
        var["content2"] = content;
        
        std::cout << "var :" << var.to_var_json() << std::endl;
        std::cout << "var :" << var.to_json() << std::endl;
    
    }
    
    {
        xcom_data var;
        var["enable"] = true;
        std::string str = var.to_var_json();
        var["age"] = 100;
        std::cout << "var :" <<  str << std::endl;
        str = var.to_json();
        std::cout << "var :" <<  str << std::endl;
        
        xcom_data content;
        {
            content["age"]=18;
            content["size"]=28;
            content["house"]=38;
            content["house"]=48;
            
            std::cout << "content : " << content.to_json() << std::endl;
        }
        
        var["content"] = content;
        var["content2"] = content;
        var["content3"] = content;
        
        std::cout << "var :" << var.to_var_json() << std::endl;
        std::cout << "var :" << var.to_json() << std::endl;
        
    }
    
    getchar();
    
    return 0;
}
