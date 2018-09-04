//
//  trequest.h
//  curl_networking
//
//  Created by jasenhuang on 15/7/29.
//  Copyright (c) 2015年 tencent. All rights reserved.
//

#ifndef __curl_networking__trequest__
#define __curl_networking__trequest__

#include <iostream>
#include <vector>
#include "tbasictypes.h"

#ifdef USE_NAMESPACE
namespace Network {
#endif

class ConnectionOperation;

class Request {
public:
    
    Request();
    virtual ~Request();
    
    size_t Read(char* buf, size_t size);
    
    void SetURL(const std::string& url){url_ = url;}
    std::string GetURL(){return url_;}
    
    void SetConnectTimeout(long timeout){connect_timeout_ms_ = timeout;}
    long GetConnectTimeout(){return connect_timeout_ms_;}
    
    void SetReadTimeout(long timeout){read_timeout_ms_ = timeout;}
    long GetReadTimeout(){return read_timeout_ms_;}
    
    void SetCustomReqeuest(const std::string& custom){custom_request_ = custom;}
    std::string GetCustomReqeuest(){return custom_request_;}
    
    void SetFilePath(const std::string& path){file_path_ = path;};
    std::string GetFilePath(){return file_path_;}
    
    void SetHeader(const std::string& key, const std::string& value);
    std::string GetHeader(const std::string& key);
    
    void SetMethod(const std::string& method);
    std::string GetMethod();
protected:
    friend class ConnectionOperation;
    
    std::vector<std::pair<std::string , std::string> > headers_;
    
    std::string     method_;
    std::string     url_;
    std::string     custom_request_;
    long            connect_timeout_ms_;
    long            read_timeout_ms_;
    
    std::string     file_path_;
    std::string     buf_;
    size_t          pos_;
    size_t          total_;
    
private:
    FILE*           fd_;
};

#ifdef USE_NAMESPACE
};
#endif

#endif /* defined(__curl_networking__trequest__) */
