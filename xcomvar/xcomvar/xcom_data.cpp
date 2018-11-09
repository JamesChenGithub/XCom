//
//  xcom_data.cpp
//  xcomvar
//
//  Created by AlexiChen on 2018/10/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "xcom_data.h"
#include "xcom_var_struct.h"
//namespace xcom {

xcom_data::xcom_data():_core(nullptr)
{
    
}

xcom_data::~xcom_data()
{
    if (_core)
    {
        delete _core;
        _core = nullptr;
    }
}
xcom_data::xcom_data(const xcom_data &data):_core(nullptr)
{
    if (data._core)
    {
        _core = new xcom_var(*data._core);
    }
}

xcom_data::xcom_data(xcom_data &&data):_core(nullptr)
{
    if (data._core)
    {
        xcom_var var = *data._core;
        _core = new xcom_var(std::move(var));
        data._core = nullptr;
    }
}
xcom_data::xcom_data(xcom_var *var, bool isvp):_core(nullptr)
{
    if (var != nullptr) {
        xcom_var_ptr ptr(var);
//        xcom_var *ptrget = ptr.get();
//        printf("ptr.get : %p  [ %p]: %s  retaincount = %d\n", ptr.get(), var, ptr->to_var_json(), ptr.use_count());
        _core = new xcom_var(ptr);
        
        xcom_var_ptr nptr = _core->var_val();
//        printf("get var : %p  [ %p]: %s \n", nptr.get(), var, _core->to_var_json());
    }
}


xcom_data& xcom_data::operator = (const xcom_data &data)
{
    if (data._core)
    {
        if (_core)
        {
            *_core = *data._core;
        }
        else
        {
            _core = new xcom_var(*data._core);
        }
    }
    else
    {
        if (_core)
        {
            delete _core;
            _core = nullptr;
        }
    }
    return *this;
    
}
xcom_data& xcom_data::operator = (xcom_data &&data)
{
    if (_core)
    {
        delete _core;
        _core = nullptr;
    }
    _core = data._core;
    data._core = nullptr;
    return *this;
}

#define XCOM_DATA_IMPL(T, VT, VAL) \
xcom_data::xcom_data(T value):_core(nullptr) { _core = new xcom_var(value); } \
xcom_data::operator T() const {return _core ? _core->obj.VT##_val : VAL; } \
T xcom_data::VT##_val() const {return _core ? _core->obj.VT##_val : VAL; } \
xcom_data& xcom_data::operator = (T value) { \
if (_core)  *_core = value;\
else  _core = new xcom_var(value);\
return *this;\
}\
bool xcom_data::operator == (const T value) const { \
return _core && _core->type != xcom_vtype_##VT  ? _core->obj.VT##_val == value : false ;\
}


xcom_data::xcom_data(bool value):_core(nullptr) {
    _core = new xcom_var(value);
}
xcom_data::operator bool() const{
    return _core ? _core->obj.bool_val : false;
}
bool xcom_data::bool_val() const {
    return _core ? _core->obj.bool_val : false;
}
xcom_data& xcom_data::operator = (bool value) {
    if (_core)
    {
        xcom_var_ptr ptr = _core->var_val();
//        printf("ptr = %p  %s\n", ptr.get(), ptr->to_var_json());
        *_core = value;
//        printf("ptr = %p  %s\n", ptr.get(), ptr->to_var_json());
    }
    else
    {
        _core = new xcom_var(value);
    }
    return *this;
}
bool xcom_data::operator == (const bool value) const {
    return _core && _core->type != xcom_vtype_bool  ?  _core->obj.bool_val == value : false;
}


//XCOM_DATA_IMPL(bool, bool, false)
XCOM_DATA_IMPL(int8_t, int8, 0)
XCOM_DATA_IMPL(uint8_t, uint8, 0)
XCOM_DATA_IMPL(int16_t, int16, 0)
XCOM_DATA_IMPL(uint16_t, uint16, 0)
XCOM_DATA_IMPL(int32_t, int32, 0)
XCOM_DATA_IMPL(uint32_t, uint32, 0)
XCOM_DATA_IMPL(int64_t, int64, 0)
XCOM_DATA_IMPL(uint64_t, uint64, 0)
XCOM_DATA_IMPL(float, float, 0.0)
XCOM_DATA_IMPL(double, double, 0.0)
XCOM_DATA_IMPL(void *, ref, NULL)

xcom_data::xcom_data(const char *value):_core(nullptr) {
    _core = new xcom_var(value);
}
xcom_data::operator const char *() const
{
    return _core ? _core->string_val().c_str() : nullptr;
}
const char * xcom_data::string_val() const
{
    return _core ? _core->string_val().c_str() : nullptr;
}
xcom_data &xcom_data::operator = (const char *value)
{
    if (_core)  {
        *_core = value;
    }
    else {
        _core = new xcom_var(value);
    }
    return *this;
}
bool xcom_data::operator == (const char* value) const
{
    return _core && _core->type != xcom_vtype_string ?  *_core == value : false;
}


const char *xcom_data::to_var_json()
{
    if (_core == nullptr)
    {
        return nullptr;
    }
    std::string str = _core->to_var_json();
    return str.c_str();
}
bool xcom_data::empty()
{
    return _core ? _core->empty() : true;
}
uint32_t xcom_data::size()
{
    return _core ? _core->size() : 0;
}


xcom_data xcom_data::operator[](const char *key)
{
    if (!key || !*key)
        return xcom_data();
    
    if (_core == nullptr) {
        _core = new xcom_var();
    }
    xcom_var_ptr var = (*_core)[key];
//    printf("get var : %p : %s \n", var.get(), var->to_var_json());
    return xcom_data(var.get(), true);
}
bool xcom_data::contains(const char *key)
{
    if (!key || !*key)
        return false;
    return _core ? _core->contains(key) : false;
}
bool xcom_data::erase(const char *key)
{
    if (!key || !*key)
        return false;
    return _core ? _core->erase(key) : false;
}

void xcom_data::set_buf(const void *buf, uint32_t len)
{
    if (buf == nullptr || len < 0)
    {
        return;
    }
    
    if (_core == nullptr)
    {
        _core = new xcom_var();
    }
    return _core->set_buffer(buf, len);
}

xcom_data xcom_data::operator[](uint32_t index)
{
    if (_core == nullptr)
    {
        _core = new xcom_var();
    }
    xcom_var_ptr ptr = (*_core)[index];
    return xcom_data(ptr.get());
}

//}
