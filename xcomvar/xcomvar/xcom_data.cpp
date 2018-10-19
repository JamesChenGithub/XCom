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
}

xcom_data::~xcom_data()
{
    if (_core)
    {
        delete _core;
        _core = nullptr;
    }
}
xcom_data::xcom_data(const xcom_data *val)
{
    if (val)
    {
        this->_core = new xcom_var(val->_core);
    }
}
xcom_data::xcom_data(const xcom_data &val)
{
    this->_core = new xcom_var(val._core);
}

xcom_data::xcom_data(xcom_data &&val)
{
    this->_core = std::move(val._core);
    val._core = nullptr;
}

void xcom_data::reset_core()
{
    if (_core)
    {
        delete _core;
        _core = nullptr;
    }
}

xcom_data& xcom_data::operator = (const xcom_data &value)
{
    this->reset_core();
    this->_core = new xcom_var(value._core);
    return *this;
}
xcom_data& xcom_data::operator = (xcom_data &&value)
{
    this->reset_core();
    this->_core = std::move(value._core);
    value._core = nullptr;
    return *this;
}

#define XCOM_DATA_IMPL(T, VT, VAL) \
    xcom_data::xcom_data(T value):xcom_data() { _core->type = xcom_vtype_##VT;  _core->obj->VT##_val = value; } \
    xcom_data::operator T() const {return _core->obj && _core->type == xcom_vtype_##VT ? _core->obj->VT##_val : VAL; } \
    T xcom_data::VT##_val() const {return _core->obj ? _core->obj->VT##_val : VAL; } \
    xcom_data& xcom_data::operator = (T value) { \
        _core->type = xcom_vtype_##VT;\
        _core->obj->reset(); \
        _core->obj->VT##_val = value;\
        return *this;\
    }\
    bool xcom_data::operator == (const T value) const { \
       return _core->type != xcom_vtype_##VT  ?  VAL : _core->obj->VT##_val == value;\
    }

XCOM_DATA_IMPL(bool, bool, false)
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

xcom_data::xcom_data(xcom_var &&var):xcom_data()
{
    *_core = std::move(var);
}

xcom_data::xcom_data(const char *value)
{
    *_core = value;
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
    return *this;
}
bool xcom_data::operator == (const char* value) const
{
    return *_core == value;
}


const char *xcom_data::to_json()
{
    if (_core->is_number())
    {
        return _core->val_str();
    }
    else
    {
        
    }
    return "";
}

xcom_data xcom_data::operator[](const char *key)
{
    xcom_var *var = *_core[key];
    return xcom_data(var);
}
bool xcom_data::contains(const char *key)
{
    return _core->contains(key);
}


//}
