//
//  xc_string.h
//  XLive_Demo_Mac
//
//  Created by AlexiChen on 2018/5/14.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xc_string_h
#define xc_string_h
#
#include <iostream>
#include <cstring>
#include <cctype>

namespace xcom
{
    class xc_string
    {
    private:
        char *m_str = nullptr;
        int m_size = 0;

    public:
        xc_string();
        xc_string(const char *str);
        xc_string(const xc_string &xcstr);
        
        ~xc_string();
        
    public:
        int length() const;
        const char *c_str() const;
        
        xc_string& operator = (const xc_string &xcstr);
        xc_string operator + (const xc_string &xcstr);
        xc_string operator + (const char *str);
        xc_string& operator += (const xc_string &xcstr);
        xc_string& operator += (const char *str);
        bool operator==(const xc_string &xcstr);
        bool operator==(const char *str);
        bool operator !=(const xc_string &xcstr);
        bool operator != (const char *str);
        char operator[](int position);
        friend std::ostream& operator << (std::ostream &os, const xc_string& str);
    };
}


#endif /* xc_string_h */
