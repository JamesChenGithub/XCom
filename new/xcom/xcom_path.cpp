//
//  xcom_xlog_core.cpp
//  xcom
//
//  Created by AlexiChen on 2017/10/10.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//
//
//                        _ooOoo_
//                       o8888888o
//                       88" . "88
//                       (| -_- |)
//                       O\  =  /O
//                     ___/`---'\____
//                 .'  \\|      |//  `.
//                 /  \\|||  :  |||//  \
//                /  _||||| -:- |||||-  \
//                |   | \\\  -  /// |   |
//                | \_|  ''\---/''  |   |
//                \  .-\__  `-`  ___/-. /
//              ___`. .'  /--.--\  `. . __
//           ."" '<  `.___\_<|>_/___.'  >'"".
//           | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//           \  \ `-.   \_ __\ /__ _/   .-` /  /
//      ======`-.____`-.___\_____/___.-`____.-'======
//                         `=---='
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                        佛祖保佑
//                        永无BUG



#include "xcom_path.h"
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#if defined(__linux)

# include <linux/limits.h>
#include <cstdio>
#include <stdlib.h>
#include <errno.h>

#endif

#if defined(_WIN32)
#define PATH_SEPARATOR   '\\'
#else
#define PATH_SEPARATOR   '/'
#endif

namespace XCom_NameSpace
{
    char *path_normalize(const char *path) {
        if (!path) return NULL;
        
        char *copy = strdup(path);
        if (NULL == copy) return NULL;
        char *ptr = copy;
        
        for (int i = 0; copy[i]; i++) {
            *ptr++ = path[i];
            if ('/' == path[i]) {
                i++;
                while ('/' == path[i]) i++;
                i--;
            }
        }
        
        *ptr = '\0';
        
        return copy;
    }
    
    /*
     * Recursively `mkdir(path, mode)`
     */
    
    int mkdirp(const char *path, mode_t mode) {
        char *pathname = NULL;
        char *parent = NULL;
        int rc;
        char *p;
        
        if (NULL == path) return -1;
        
        pathname = path_normalize(path);
        if (NULL == pathname) goto fail;
        
        parent = strdup(pathname);
        if (NULL == parent) goto fail;
        
        p = parent + strlen(parent);
        while (PATH_SEPARATOR != *p && p != parent) {
            p--;
        }
        *p = '\0';
        
        // make parent dir
        if (p != parent && 0 != mkdirp(parent, mode)) goto fail;
        free(parent);
        
        // make this one if parent has been made
        rc = mkdir(pathname, mode);
        
        free(pathname);
        
        return 0 == rc || EEXIST == errno
        ? 0
        : -1;
        
    fail:
        free(pathname);
        free(parent);
        return -1;
    }
    
    xcom_path::xcom_path() : _type(native_path), _wide(false), _absolute(false) {
        
    }
    
    xcom_path::xcom_path(const xcom_path &path)
    : _type(path._type), _wide(path._wide), _absolute(path._absolute), _path(path._path) {
        
    }
    
    xcom_path::xcom_path(xcom_path &&path)
    : _type(path._type), _wide(path._wide), _absolute(path._absolute),
    _path(std::move(path._path)) {
        
    }
    
    xcom_path::xcom_path(const char *string) {
        set(string);
    }
    
    xcom_path::xcom_path(const std::string &string) {
        set(string);
    }
    
    xcom_path::~xcom_path() {
        
    }
    
    size_t xcom_path::length() const {
        return _path.size();
    }
    
    bool xcom_path::empty() const {
        return _path.empty();
    }
    
    bool xcom_path::is_absolute() const {
        return _absolute;
    }
    
    xcom_path xcom_path::make_absolute() const {
#if !(defined(_WIN32))
        char temp[PATH_MAX];
        if (realpath(str().c_str(), temp) == NULL)
            return xcom_path();
        //		throw std::runtime_error("Internal error in realpath(): " + std::string(strerror(errno)));
        return xcom_path(temp);
#else
        std::wstring value = wstr(), out(MAX_PATH, '\0');
        DWORD length = GetFullPathNameW(value.c_str(), MAX_PATH, &out[0], NULL);
        if (length == 0)
            return xcom_path();
        //		throw std::runtime_error("Internal error in realpath(): " + std::to_string(GetLastError()));
        return xcom_path(out.substr(0, length));
#endif
    }
    
    bool xcom_path::exists() const {
#if defined(_WIN32)
        return GetFileAttributesW(wstr().c_str()) != INVALID_FILE_ATTRIBUTES;
#else
        struct stat sb;
        return stat(str().c_str(), &sb) == 0;
#endif
    }
    
    size_t xcom_path::file_size() const {
#if defined(_WIN32)
        struct _stati64 sb;
        if (_wstati64(wstr().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::file_size(): cannot stat file \"" + str() + "\"!");
#else
        struct stat sb;
        if (stat(str().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::file_size(): cannot stat file \"" + str() + "\"!");
#endif
        return (size_t) sb.st_size;
    }
    
    bool xcom_path::is_directory() const {
#if defined(_WIN32)
        DWORD attr = GetFileAttributesW(wstr().c_str());
        return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
        struct stat sb;
        if (stat(str().c_str(), &sb))
            return false;
        return S_ISDIR(sb.st_mode);
#endif
    }
    
    bool xcom_path::is_file() const {
#if defined(_WIN32)
        DWORD attr = GetFileAttributesW(wstr().c_str());
        return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) == 0;
#else
        struct stat sb;
        if (stat(str().c_str(), &sb))
            return false;
        return S_ISREG(sb.st_mode);
#endif
    }
    
    std::string xcom_path::extension() const {
        const std::string &name = filename();
        size_t pos = name.find_last_of(".");
        if (pos == std::string::npos)
            return "";
        return name.substr(pos + 1);
    }
    
    std::string xcom_path::filename() const {
        if (empty())
            return "";
        const std::string &last = _path[_path.size() - 1];
        return last;
    }
    
    xcom_path xcom_path::parent() const {
        xcom_path result;
        result._absolute = _absolute;
        
        if (_path.empty()) {
            if (!_absolute)
                result._path.push_back("..");
        } else {
            size_t until = _path.size() - 1;
            for (size_t i = 0; i < until; ++i)
                result._path.push_back(_path[i]);
        }
        return result;
    }
    
    std::vector<xcom_path> xcom_path::childs() const{
        std::vector<xcom_path> list;
#if defined(_WIN32)
        WIN32_FIND_DATAA fileData;
        HANDLE handle = FindFirstFileA((str() + "\\*").c_str(), &fileData);
        while(handle != INVALID_HANDLE_VALUE){
            if(strcmp(fileData.cFileName, ".") != 0 && strcmp(fileData.cFileName, "..") != 0){
                list.push_back((*this) / fileData.cFileName);
            }
            if(!FindNextFileA(handle, &fileData)){
                break;
            }
        }
        FindClose(handle);
#else
        DIR *dir = opendir(str().c_str());
        while(dir != NULL){
            dirent *file = readdir(dir);
            if(file){
                if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0){
                    list.push_back((*this) / file->d_name);
                }
            }
            else{
                break;
            }
        }
        closedir(dir);
#endif
        return list;
    }
    
    time_t xcom_path::creation_time() const {
        return last_status_change_time();
    }
    
    time_t xcom_path::last_access_time() const {
#if defined(_WIN32)
        struct _stati64 sb;
        if (_wstati64(wstr().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::last_access_time(): cannot stat file \"" + str() + "\"!");
#else
        struct stat sb;
        if (stat(str().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::last_access_time(): cannot stat file \"" + str() + "\"!");
#endif
        return sb.st_atime;
    }
    
    time_t xcom_path::last_modified_time() const {
#if defined(_WIN32)
        struct _stati64 sb;
        if (_wstati64(wstr().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::last_modified_time(): cannot stat file \"" + str() + "\"!");
#else
        struct stat sb;
        if (stat(str().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::last_modified_time(): cannot stat file \"" + str() + "\"!");
#endif
        return sb.st_mtime;
    }
    
    time_t xcom_path::last_status_change_time() const {
#if defined(_WIN32)
        struct _stati64 sb;
        if (_wstati64(wstr().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::last_status_change_time(): cannot stat file \"" + str() + "\"!");
#else
        struct stat sb;
        if (stat(str().c_str(), &sb) != 0)
            return 0;
        //		throw std::runtime_error("xcom_path::last_status_change_time(): cannot stat file \"" + str() + "\"!");
#endif
        return sb.st_ctime;
    }
    
    std::string xcom_path::str(xcom_path::path_type type) const {
        std::ostringstream oss;
        if (_type == posix_path && _absolute)
            oss << "/";
        else if (_type == windows_path && _absolute) {
            if (_path.size() == 0 || _path[0].find(':') == -1) {
                oss << "\\\\";
            }
        }
        for (size_t i = 0; i < _path.size(); ++i) {
            oss << _path[i];
            if (i + 1 < _path.size()) {
                if (type == posix_path)
                    oss << '/';
                else
                    oss << '\\';
            }
        }
        return oss.str();
    }
    
    void xcom_path::set(const std::string &str, xcom_path::path_type type) {
        _type = type;
        if (type == windows_path) {
            _path = tokenize(str, "/\\");
#if defined(_WIN32)
            _absolute = str.size() >= 2 && ((isalpha(str[0]) && str[1] == ':') || (str[0] == '\\' && str[1] == '\\'));
#else
            _absolute = str.size() >= 2 && std::isalpha(str[0]) && str[1] == ':';
#endif
        } else {
            _path = tokenize(str, "/");
            _absolute = !str.empty() && str[0] == '/';
        }
        _wide = false;
    }
    
    xcom_path xcom_path::operator/(const xcom_path &other) const {
        //	if (other._absolute)
        //		throw std::runtime_error("xcom_path::operator/(): expected a relative path!");
        //	if (_type != other._type)
        //		throw std::runtime_error("xcom_path::operator/(): expected a path of the same type!");
        xcom_path result(*this);
        for (size_t i = 0; i < other._path.size(); ++i)
            result._path.push_back(other._path[i]);
        return result;
    }
    
    xcom_path &xcom_path::operator=(const xcom_path &path) {
        _type = path._type;
        _path = path._path;
        _absolute = path._absolute;
        return *this;
    }
    
    xcom_path &xcom_path::operator=(xcom_path &&path) {
        if (this != &path) {
            _type = path._type;
            _path = std::move(path._path);
            _absolute = path._absolute;
        }
        return *this;
    }
    
    std::ostream &operator<<(std::ostream &os, const xcom_path &path) {
        os << path.str();
        return os;
    }
    
    bool xcom_path::operator==(const xcom_path &p) const {
        return p._path == _path;
    }
    
    bool xcom_path::operator!=(const xcom_path &p) const {
        return p._path != _path;
    }
    
    bool xcom_path::remove_file() const {
#if defined(_WIN32)
        return DeleteFileW(wstr().c_str()) != 0;
#else
        return std::remove(str().c_str()) == 0;
#endif
    }
    
    bool xcom_path::resize_file(size_t target_length) const {
#if defined(_WIN32)
        HANDLE handle = CreateFileW(wstr().c_str(), GENERIC_WRITE, 0, nullptr, 0, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle == INVALID_HANDLE_VALUE)
            return false;
        LARGE_INTEGER size;
        size.QuadPart = (LONGLONG) target_length;
        if (SetFilePointerEx(handle, size, NULL, FILE_BEGIN) == 0) {
            CloseHandle(handle);
            return false;
        }
        if (SetEndOfFile(handle) == 0) {
            CloseHandle(handle);
            return false;
        }
        CloseHandle(handle);
        return true;
#else
        return ::truncate(str().c_str(), (off_t) target_length) == 0;
#endif
    }
    
    bool xcom_path::create_directory() const {
        return mkdirp(str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) == 0;
    }
    
    xcom_path xcom_path::getcwd() {
#if !(defined(_WIN32))
        char temp[PATH_MAX];
        if (::getcwd(temp, PATH_MAX) == NULL)
            return xcom_path();
        //		throw std::runtime_error("Internal error in getcwd(): " + std::string(strerror(errno)));
        return xcom_path(temp);
#else
        std::wstring temp(MAX_PATH, '\0');
        if (!_wgetcwd(const_cast<wchar_t*>(temp.c_str()), MAX_PATH))
            return xcom_path();
        //		throw std::runtime_error("Internal error in getcwd(): " + std::to_string(GetLastError()));
        return xcom_path(temp.c_str());
#endif
    }
    
    std::vector<std::string> xcom_path::tokenize(const std::string &string, const std::string &delim) {
        std::string::size_type lastPos = 0, pos = string.find_first_of(delim, lastPos);
        std::vector<std::string> tokens;
        
        while (lastPos != std::string::npos) {
            if (pos != lastPos )
            {
                if (pos != std::string::npos)
                {
                    tokens.push_back(string.substr(lastPos, pos - lastPos));
                }
                else
                {
                    tokens.push_back(string.substr(lastPos));
                }
                
            }
            lastPos = pos;
            if (lastPos == std::string::npos || lastPos + 1 == string.length())
                break;
            pos = string.find_first_of(delim, ++lastPos);
        }
        
        return tokens;
    }
    
    bool xcom_path::is_wide() {
        return _wide;
    }
    
#if defined(_WIN32)
    xcom_path::xcom_path(const wchar_t *wstring) {
        set(wstring);
    }
    
    xcom_path::xcom_path(const std::wstring &wstring) {
        set(wstring);
    }
    
    std::wstring xcom_path::wstr(path_type type) const {
        std::string temp = str(type);
        int size = MultiByteToWideChar(CP_UTF8, 0, &temp[0], (int) temp.size(), NULL, 0);
        std::wstring result(size, 0);
        MultiByteToWideChar(CP_UTF8, 0, &temp[0], (int) temp.size(), &result[0], size);
        return result;
    }
    
    
    void xcom_path::set(const std::wstring &wstring, path_type type) {
        std::string string;
        if (!wstring.empty()) {
            int size = WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int) wstring.size(),
                                           NULL, 0, NULL, NULL);
            string.resize(size, 0);
            WideCharToMultiByte(CP_UTF8, 0, &wstring[0], (int) wstring.size(),
                                &string[0], size, NULL, NULL);
        }
        set(string, type);
        _wide = true;
    }
    
    xcom_path &xcom_path::operator=(const std::wstring &str) {
        set(str);
        return *this;
    }
#endif
}
