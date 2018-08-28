//
//  xc_string.cpp
//  string_test
//
//  Created by AlexiChen on 2018/5/15.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xc_string.h"


namespace xcom
{
    static const int xc_string_per_size = 64;
    static char *xc_string_alloc(int &size)
    {
        char *ret = (char *)malloc(xc_string_per_size);
        if (ret == nullptr)
        {
            return nullptr;
        }
        memset(ret, 0, xc_string_per_size);
        size = xc_string_per_size;
        return ret;
    }
    
    static char *xc_string_alloc_cpy(const char *str, int &size)
    {
        if (str == nullptr)
        {
            return xc_string_alloc(size);
        }
        else
        {
            int strsize = (str == nullptr ? 0 : (int)strlen(str));
            int alsize = xc_string_per_size;
            if (strsize > xc_string_per_size)
            {
                alsize = (strsize / xc_string_per_size) * 2 * xc_string_per_size;
            }
            
            char *ret = (char *)malloc(alsize);
            memset(ret, 0, alsize);
            strcpy(ret, str);
            size = alsize;
            return ret;
        }
        
    }
    
    static char *xc_string_alloc_cat(char *dest, const char *src, int &size)
    {
        int dlen = (dest == nullptr ? 0 : (int)strlen(dest));
        int slen = (src == nullptr ? 0 : (int)strlen(src));
        
        // realloc
        int strsize = dlen + slen;
        int alsize = xc_string_per_size;
        if (strsize > xc_string_per_size)
        {
            alsize = (strsize / xc_string_per_size) * 2 * xc_string_per_size;
        }
        
        char *ret = (char *)malloc(alsize);
        memset(ret, 0, alsize);
        if (dest)
        {
            strcpy(ret, dest);
        }
        if (src) {
            strcpy(ret+dlen, src);
        }
        
        return ret;
        
    }
    static char *xc_string_cat_alloc_cpy(char *&dest, const char *src, int &size)
    {
        int dlen = (dest == nullptr ? 0 : (int)strlen(dest));
        int reset = size - dlen;
        int slen = (src == nullptr ? 0 : (int)strlen(src));
        
        if (reset > slen)
        {
            // cat direct
            if (src) {
                strcat(dest, src);
            }
            return dest;
        }
        else
        {
            // realloc
            int strsize = slen;
            int alsize = xc_string_per_size;
            if (strsize > xc_string_per_size)
            {
                alsize = (strsize / xc_string_per_size) * 2 * xc_string_per_size;
            }
            
            alsize += size;
            
            char *ret = (char *)malloc(alsize);
            memset(ret, 0, alsize);
            if (dest)
            {
                strcpy(ret, dest);
            }
            if (src) {
                strcpy(ret+dlen, src);
            }
            size = alsize;
            free(dest);
            dest = nullptr;
            dest = ret;
            return ret;
        }
    }
    
    xc_string::xc_string()
    {
        this->m_str = nullptr;
        this->m_size = 0;
    }
    
    xc_string::xc_string(const char *str)
    {
        this->m_str = xc_string_alloc_cpy(str, this->m_size);
    }
    
    xc_string::xc_string(const xc_string &xcstr)
    {
        this->m_str = xc_string_alloc_cpy(xcstr.c_str(), this->m_size);
    }
    
    xc_string::~xc_string()
    {
        printf("(%s) release\n", m_str ? m_str : "");
        if (m_str)
        {
            free(m_str);
            m_str = nullptr;
        }
    }
    
    int xc_string::length() const
    {
        if (m_str)
        {
            return (int)strlen(m_str);
        }
        return 0;
    }
    const char *xc_string::c_str() const
    {
        return m_str;
    }
    
    xc_string& xc_string::operator = (const xc_string &xcstr)
    {
        this->m_str = xc_string_alloc_cpy(xcstr.c_str(), this->m_size);
        return *this;
    }
    
    xc_string xc_string::operator + (const xc_string &xcstr)
    {
        int size = this->m_size;
        char *dest = xc_string_alloc_cat(this->m_str, xcstr.c_str(), size);
        
        xc_string str;
        str.m_str = dest;
        str.m_size = size;
        return str;
    }
    
    xc_string xc_string::operator + (const char *str)
    {
        int size = this->m_size;
        char *dest = xc_string_alloc_cat(this->m_str, str, size);
        
        xc_string xcstr;
        xcstr.m_str = dest;
        xcstr.m_size = size;
        return xcstr;
    }
    
    xc_string& xc_string::operator +=(const xc_string &xcstr)
    {
        xc_string_cat_alloc_cpy(this->m_str, xcstr.c_str(), this->m_size);
        return *this;
    }
    
    xc_string& xc_string::operator += (const char *str)
    {
        xc_string_cat_alloc_cpy(this->m_str, str, this->m_size);
        return *this;
    }
    
    bool xc_string::operator==(const xc_string &xcstr)
    {
        if(strcmp(this->m_str, xcstr.m_str) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool xc_string::operator==(const char *str)
    {
        if(strcmp(this->m_str, str) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool xc_string::operator !=(const xc_string &xcstr)
    {
        if(strcmp(this->m_str, xcstr.m_str) == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    
    bool xc_string::operator != (const char *str)
    {
        if(strcmp(this->m_str, str) == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    
    char xc_string::operator[](int position)
    {
        if (position >=0 && position < this->length()) {
            return *(m_str + position);
        }
        return 0;
    }
    
    std::ostream& operator << (std::ostream &os, const xc_string& str)
    {
        os << (str.m_str == nullptr ? "" : str.m_str);
        return os;
    }
}
