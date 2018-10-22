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
    _core = new xcom_var;
    _isref = false;
}

xcom_data::~xcom_data()
{
    if (_core && !_isref)
    {
        delete _core;
        _core = nullptr;
    }
}
xcom_data::xcom_data(const xcom_data *val)
{
    if (val)
    {
        _core = new xcom_var(val->_core);
        _isref = false;
    }
}
xcom_data::xcom_data(const xcom_data &val)
{
    _core = new xcom_var(val._core);
    _isref = false;
}

//xcom_data::xcom_data(xcom_data &&val)
//{
//    this->_core = std::move(val._core);
//    val._core = nullptr;
//}

void xcom_data::reset_core()
{
    if (_isref)
    {
        _core = nullptr;
    }
    else
    {
        if (_core)
        {
            delete _core;
            _core = nullptr;
        }
    }
    this->_isref = false;
}

xcom_data& xcom_data::operator = (const xcom_data &value)
{
    this->reset_core();
    _core = new xcom_var(value._core);
    _isref = false;
    return *this;
}
//xcom_data& xcom_data::operator = (xcom_data &&value)
//{
//    this->reset_core();
//    this->_core = std::move(value._core);
//    value._core = nullptr;
//    return *this;
//}

#define XCOM_DATA_IMPL(T, VT, VAL) \
xcom_data::xcom_data(T value):xcom_data() { _core->type = xcom_vtype_##VT;  _core->obj->VT##_val = value;  _isref = false; } \
xcom_data::operator T() const {return _core->obj && _core->type == xcom_vtype_##VT ? _core->obj->VT##_val : VAL; } \
T xcom_data::VT##_val() const {return _core->obj ? _core->obj->VT##_val : VAL; } \
xcom_data& xcom_data::operator = (T value) { \
_core->type = xcom_vtype_##VT;\
_core->obj->reset(); \
_core->obj->VT##_val = value;\
 _isref = false; \
return *this;\
}\
bool xcom_data::operator == (const T value) const { \
return _core->type != xcom_vtype_##VT  ?  VAL : _core->obj->VT##_val == value;\
}


xcom_data::xcom_data(bool value):xcom_data() {
    _core->type = xcom_vtype_bool;
    _core->obj->bool_val = value;
     _isref = false;
}
xcom_data::operator bool() const{
    return _core->obj && _core->type == xcom_vtype_bool ? _core->obj->bool_val : false;
}
bool xcom_data::bool_val() const {
    return _core->obj ? _core->obj->bool_val : false;
}
xcom_data& xcom_data::operator = (bool value) {
    _core->type = xcom_vtype_bool;
    _core->obj->reset();
    _core->obj->bool_val = value;
     _isref = false;
    return *this;
}
bool xcom_data::operator == (const bool value) const {
    return _core->type != xcom_vtype_bool  ?  false : _core->obj->bool_val == value;
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

xcom_data::xcom_data(xcom_var *var)
{
    reset_core();
    _core = var;
    _isref = true;
}

xcom_data::xcom_data(const char *value)
{
    *_core = value;
    _isref = false;
}
xcom_data::operator const char *() const
{
    return *_core;
}
const char * xcom_data::string_val() const
{
    return *_core;
}
xcom_data &xcom_data::operator = (const char *value)
{
    *_core = value;
     _isref = false;
    return *this;
}
bool xcom_data::operator == (const char* value) const
{
    return *_core == value;
}


const char *xcom_data::to_json()
{
    if (_core == nullptr)
    {
        return nullptr;
    }
    const char *str = _core->val_str();
    return str;
}
bool xcom_data::empty()
{
    return _core ? _core->empty() : true;
}
uint32_t xcom_data::size()
{
    return _core ? _core->size() : true;
}

xcom_data xcom_data::operator[](const char *key)
{
    xcom_var_ptr var = (*_core)[key];
    return xcom_data(var.get());
}
bool xcom_data::contains(const char *key)
{
    return _core->contains(key);
}
bool xcom_data::erase(const char *key)
{
    return _core->erase(key);
}

void xcom_data::set_buf(const void *buf, uint32_t len)
{
    return _core->set_buffer(buf, len);
}

xcom_data xcom_data::operator[](uint32_t index)
{
    return xcom_data();
}

//}
