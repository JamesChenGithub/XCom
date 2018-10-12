//
//  xcom_path.h
//  string_test
//
//  Created by AlexiChen on 2018/5/15.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef XCOM_PATH_H_
#define XCOM_PATH_H_

#include <string>
#include <vector>
#include "xcom_sys_def.h"
#include "xcom_config.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace XCom_NameSpace {
    
    
    
    class xcom_path
    {
    public:
        enum path_type {
            windows_path = 0,
            posix_path = 1,
#if XCOM_OS_WIN
            native_path = windows_path
#else
            native_path = posix_path
#endif
        };
        
        xcom_path();
        
        xcom_path(const xcom_path &path);
        
        xcom_path(xcom_path &&path);
        
        xcom_path(const char *string);
        
        xcom_path(const std::string &string);
        
        ~xcom_path();
        
        size_t length() const;
        
        bool empty() const;
        
        bool is_absolute() const;
        
        xcom_path make_absolute() const;
        
        bool exists() const;
        
        size_t file_size() const;
        
        bool is_directory() const;
        
        bool is_file() const;
        
        std::string extension() const;
        
        std::string filename() const;
        
        xcom_path parent() const;
        
        std::vector<xcom_path> childs() const;
        
        time_t creation_time() const;
        
        time_t last_access_time() const;
        
        time_t last_modified_time() const;
        
        time_t last_status_change_time() const;
        
        std::string str(path_type type = native_path) const;
        
        void set(const std::string &str, path_type type = native_path);
        
        xcom_path operator/(const xcom_path &other) const;
        
        xcom_path &operator=(const xcom_path &path);
        
        xcom_path &operator=(xcom_path &&path);
        
        friend std::ostream &operator<<(std::ostream &os, const xcom_path &path);
        
        bool operator==(const xcom_path &p) const;
        
        bool operator!=(const xcom_path &p) const;
        
        bool remove_file() const;
        
        bool resize_file(size_t target_length) const;
        
        bool create_directory() const;
        
        bool is_wide();
        
#if XCOM_OS_WIN
        xcom_path(const std::wstring &wstring);
        
        xcom_path(const wchar_t *wstring);
        
        std::wstring wstr(path_type type = native_path) const;
        
        void set(const std::wstring &wstring, path_type type = native_path);
        
        xcom_path &operator=(const std::wstring &str);
#endif
        
        static xcom_path getcwd();
        
    protected:
        static std::vector<std::string> tokenize(const std::string &string, const std::string &delim);
        
    protected:
        path_type _type;
        bool _wide;
        bool _absolute;
        std::vector<std::string> _path;
    };
}
#endif //xcom_path_H
