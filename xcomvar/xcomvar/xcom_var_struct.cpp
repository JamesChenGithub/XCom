#include "xcom_var_struct.h"

#ifdef __cplusplus
extern "C" {
#endif
    //==============================
    static int xcom_var_new_count = 0;
    xcom_var::~xcom_var()
    {
        printf("var_struct dealloc [%d]: [%p] [%s] \n", --xcom_var_new_count, this, this->to_json());
        this->reset();
    }
    
    void xcom_var::reset()
    {
        if (this->type >= xcom_vtype_bytes)
        {
            switch(this->type)
            {
                case xcom_vtype_array:
                {
                    if (this->obj.array_val != nullptr)
                    {
                        delete this->obj.array_val;
                        this->obj.array_val = nullptr;
                    }
                    
                    break;
                }
                case xcom_vtype_dict:
                {
                    if (this->obj.dict_val != nullptr)
                    {
                        delete this->obj.dict_val;
                        this->obj.dict_val = nullptr;
                    }
                    break;
                }
                case xcom_vtype_bytes:
                {
                    if (this->obj.buf_val != nullptr)
                    {
                        delete this->obj.buf_val;
                        this->obj.buf_val = nullptr;
                    }
                    break;
                }
                
                case xcom_vtype_null:
                case xcom_vtype_bool:
                case xcom_vtype_int8:
                case xcom_vtype_uint8:
                case xcom_vtype_int16:
                case xcom_vtype_uint16:
                case xcom_vtype_int32:
                case xcom_vtype_uint32:
                case xcom_vtype_int64:
                case xcom_vtype_uint64:
                case xcom_vtype_float:
                case xcom_vtype_double:
                case xcom_vtype_string:
                case xcom_vtype_ref:
                {
                    this->obj.ref_val = nullptr;
                    break;
                }
                default:
                {
                    break;
                }
                    
            }
        }
    }
    
    void xcom_var::reset(const xcom_var &var)
    {
        reset();
        switch(var.type)
        {
            case xcom_vtype_array:
            {
                if (var.obj.array_val)
                {
                    this->obj.array_val = new xcom_var_vec;
                    auto it = var.obj.array_val->begin();
                    while (it != var.obj.array_val->end()) {
                        this->obj.array_val->emplace_back(*it);
                        it++;
                    }
                }

                break;
            }
            case xcom_vtype_dict:
            {
                if (var.obj.dict_val)
                {
                    this->obj.dict_val = new xcom_var_dict;
                    auto it = var.obj.dict_val->begin();
                    while (it != var.obj.dict_val->end()) {
                        this->obj.dict_val->insert(std::make_pair(it->first, it->second));
                        it++;
                    }
                }
                break;
            }
            case xcom_vtype_bytes:
            {
                if (var.obj.buf_val)
                {
                    this->obj.buf_val = new xcom_var_buf(var.obj.buf_val->buf, var.obj.buf_val->len);
                }
                break;
            }

            case xcom_vtype_null:
            {
                break;
            }
            case xcom_vtype_bool: this->obj.bool_val = var.obj.bool_val; break;
            case xcom_vtype_int8: this->obj.int8_val = var.obj.int8_val; break;
            case xcom_vtype_uint8: this->obj.uint8_val = var.obj.uint8_val; break;
            case xcom_vtype_int16: this->obj.int16_val = var.obj.int16_val; break;
            case xcom_vtype_uint16: this->obj.uint16_val = var.obj.uint16_val; break;
            case xcom_vtype_int32: this->obj.int32_val = var.obj.int32_val; break;
            case xcom_vtype_uint32: this->obj.uint32_val = var.obj.uint32_val; break;
            case xcom_vtype_int64: this->obj.int64_val = var.obj.int64_val; break;
            case xcom_vtype_uint64: this->obj.uint64_val = var.obj.uint64_val; break;
            case xcom_vtype_float: this->obj.float_val = var.obj.float_val; break;
            case xcom_vtype_double: this->obj.double_val = var.obj.double_val; break;
            case xcom_vtype_string: this->obj.string_val = var.obj.string_val; break;
            case xcom_vtype_ref: this->obj.ref_val = var.ref_val(); break;
            default:
            {
                break;
            }

        }
    
    }
    void xcom_var::reset(xcom_var &&var)
    {
        reset();
        switch(var.type)
        {
            case xcom_vtype_array:
            {
                if (var.obj.array_val)
                {
                    this->obj.array_val = var.obj.array_val;
                    var.obj.array_val = nullptr;
                }
                
                break;
            }
            case xcom_vtype_dict:
            {
                if (var.obj.dict_val)
                {
                    this->obj.dict_val = var.obj.dict_val;
                    var.obj.dict_val = nullptr;
                }
                break;
            }
            case xcom_vtype_bytes:
            {
                if (var.obj.buf_val)
                {
                    this->obj.buf_val = var.obj.buf_val;
                    var.obj.buf_val = nullptr;
                }
                break;
            }
            case xcom_vtype_bool: this->obj.bool_val = var.obj.bool_val; var.obj.bool_val = false; break;
            case xcom_vtype_int8: this->obj.int8_val = var.obj.int8_val; var.obj.int8_val = 0; break;
            case xcom_vtype_uint8: this->obj.uint8_val = var.obj.uint8_val; var.obj.uint8_val = 0; break;
            case xcom_vtype_int16: this->obj.int16_val = var.obj.int16_val; var.obj.int16_val = 0; break;
            case xcom_vtype_uint16: this->obj.uint16_val = var.obj.uint16_val; var.obj.uint16_val = 0; break;
            case xcom_vtype_int32: this->obj.int32_val = var.obj.int32_val; var.obj.int32_val = 0; break;
            case xcom_vtype_uint32: this->obj.uint32_val = var.obj.uint32_val; var.obj.uint32_val = 0; break;
            case xcom_vtype_int64: this->obj.int64_val = var.obj.int64_val; var.obj.int64_val = 0; break;
            case xcom_vtype_uint64: this->obj.uint64_val = var.obj.uint64_val; var.obj.uint64_val = 0;break;
            case xcom_vtype_float: this->obj.float_val = var.obj.float_val; var.obj.float_val = 0; break;
            case xcom_vtype_double: this->obj.double_val = var.obj.double_val; var.obj.double_val = 0; break;
            case xcom_vtype_string: this->obj.string_val = var.obj.string_val; var.obj.string_val = ""; break;
            case xcom_vtype_ref: this->obj.ref_val = var.ref_val(); var.obj.ref_val = NULL; break;
            default:
            {
                break;
            }
                
        }
    }
    
    xcom_var::xcom_var()
    {
        this->type = xcom_vtype_null;
        printf("var_struct new [%d]: [%p] \n", ++xcom_var_new_count, this);
    }
    
    //================
    const char *xcom_var::to_json() const
    {
        
        std::string typestr = xcom_var_type_string(this->type);
        std::string valstr = "" ;
        switch(this->type)
        {
            case xcom_vtype_null: { valstr = "null"; break; };
            case xcom_vtype_bool: { valstr = this->bool_val() ? "true" : "false"; break; };
            case xcom_vtype_int8: { valstr = std::to_string(this->int8_val()); break;};
            case xcom_vtype_uint8: { valstr = std::to_string(this->uint8_val()); break;};
            case xcom_vtype_int16: { valstr = std::to_string(this->int8_val()); break;};
            case xcom_vtype_uint16: { valstr = std::to_string(this->int16_val()); break;};
            case xcom_vtype_int32: { valstr = std::to_string(this->int32_val()); break;};
            case xcom_vtype_uint32: { valstr = std::to_string(this->uint32_val()); break;};
            case xcom_vtype_int64: { valstr = std::to_string(this->uint64_val()); break;};
            case xcom_vtype_uint64: { valstr = std::to_string(this->int64_val()); break;};
            case xcom_vtype_float: { valstr = std::to_string(this->float_val()); break;};
            case xcom_vtype_double: { valstr = std::to_string(this->double_val()); break;};
            case xcom_vtype_string: { valstr = "\""+this->string_val() + "\""; break;};
            case xcom_vtype_bytes: {
                valstr = this->obj.buf_val->to_json();
                break;
            };
            case xcom_vtype_array:
            {
                std::ostringstream ostr;
                ostr << "[";
                auto it = this->obj.dict_val->begin();
                auto end = this->obj.dict_val->end();
                while(it != end){
                    ostr << "\""<<it->first << "\":" << it->second->to_json();
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "]";
                std::string str = ostr.str();
                return str.c_str();
                break;
                
            };
            case xcom_vtype_dict: {
                std::ostringstream ostr;
                ostr << "{";
                auto it = this->obj.dict_val->begin();
                auto end = this->obj.dict_val->end();
                while(it != end){
                    ostr << "\""<<it->first << "\":" << it->second->to_json();
                    it++;
                    if (it != end)
                    {
                        ostr << ",";
                    }
                }
                ostr << "}";
                std::string str = ostr.str();
                return str.c_str();
                break;
            };
            
            case xcom_vtype_ref: {
                char buf[32];
                sprintf(buf, "%p", this->obj.ref_val);
                valstr = buf;
                break;
            };
        }
        
        std::string str = "{ \"" + typestr + "\" : " + valstr + " }";
        return str.c_str();
    }
    
    //=====================
    //string
    // string
    xcom_var::xcom_var(const std::string &str): xcom_var() {
        this->type = xcom_vtype_string;
        this->obj.string_val = str;
    }
    xcom_var::xcom_var(const char *cstr) : xcom_var() {
        this->type = xcom_vtype_string;
        this->obj.string_val = cstr;
    }
    
     xcom_var::operator const char *() const {
         return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : "";
     }
     xcom_var::operator std::string () const {
         return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : std::string("");
     }
    
     const char *xcom_var::cstr_val() const  {
         return this->type == xcom_vtype_string ? this->obj.string_val.c_str() : "";
     }
     std::string xcom_var::string_val() const {
         return this->type == xcom_vtype_string ? this->obj.string_val : std::string("");
     }
    
    xcom_var & xcom_var::operator= (const char *cstr) {
        this->reset();
        this->type = xcom_vtype_string;
        this->obj.string_val = cstr;
        return *this;
    }
    xcom_var & xcom_var::operator= (const std::string &str) {
        this->reset();
        this->type = xcom_vtype_string;
        this->obj.string_val = str;
        return *this;
    }
    
    bool xcom_var::operator == (const char *cstr) const {
        return this->type != xcom_vtype_string && cstr ?  false : this->obj.string_val == std::string(cstr);
    }
    bool xcom_var::operator == (const std::string str) const {
        return this->type != xcom_vtype_string  ?  false : this->obj.string_val == str;
    }
    //=====================
    /* array */
    xcom_var_ptr xcom_var::operator[](uint32_t index) {
        if (this->type != xcom_vtype_array)
            return nullptr;
        
        return at(index);
    }
    
    /* 'index' based array methods */
    void xcom_var::append(xcom_var data)
    {
        if (data.type == xcom_vtype_null)
            return;
        
        init_varray();
        if (this->type == xcom_vtype_array)
        {
            xcom_var *ptr = new xcom_var(data);
            xcom_var_ptr var_ptr(ptr);
            this->obj.array_val->emplace_back(ptr);
        }
    }
    

    
    /* 'index' based array methods */
    xcom_var_ptr xcom_var::at(uint32_t index) {
        
        if(index >=0 && index < this->obj.array_val->size())
        {
            return (*this->obj.array_val)[index];
        }
        
        return nullptr;
    }
    
    void xcom_var::init_varray()
    {
        if (this->type != xcom_vtype_array)
        {
            this->type = xcom_vtype_array;
            this->reset();
            this->obj.array_val = new xcom_var_vec;
        }
    }
    //=====================
    /* dict */
    xcom_var_ptr xcom_var::operator[](const char *key) {
        if (!key || !*key)
            return nullptr;
        
        if (this->type != xcom_vtype_dict)
            init_vdict();
        
        if (!this->contains(key))
        {
            printf("\ntest put \n");
            xcom_var emp = xcom_var(false);
            this->put(key, emp);
        }
        printf("test put done\n");
        xcom_var_ptr ptr = get(key);
        return ptr;
    }
    bool xcom_var::contains(const char *key)
    {
        if (this->type != xcom_vtype_dict)
            return false;
        
        bool succ = this->obj.dict_val->find(key) != this->obj.dict_val->end();
        return succ;
    }
    
    bool xcom_var::erase(const char *key) {
        if (this->type != xcom_vtype_dict)
            return false;
        
        auto it = this->obj.dict_val->find(key);
        if (it != this->obj.dict_val->end())
        {
            it->second.reset();
            this->obj.dict_val->erase(it);
            return true;
        }
        return false;
    }

    void xcom_var::init_vdict()
    {
        if (this->type != xcom_vtype_dict)
        {
            this->type = xcom_vtype_dict;
            this->reset();
            this->obj.dict_val = new xcom_var_dict;
        }
    }
    
    /* 'key-value' dictionary methods */
    void xcom_var::put(const char *key, const xcom_var data) {
        init_vdict();
        xcom_var *ptr = new xcom_var(data);
        xcom_var_ptr var_ptr(ptr);
        this->obj.dict_val->insert(std::make_pair(key, var_ptr));
    }
    
    xcom_var_ptr xcom_var::get(const char *key) {
        auto it = this->obj.dict_val->find(key);
        if (it == this->obj.dict_val->end())
        {
            return nullptr;
        }
        return it->second;
    }
    //=====================
    /* buffer */
    void xcom_var::set_buffer(const void *data, uint32_t len) {
        if (data != nullptr && len > 0) {
            this->reset();
            this->type = xcom_vtype_bytes;
            this->obj.buf_val = new xcom_var_buf(data, len);
        }
    }
    //================
    bool xcom_var::empty()
    {
        if (this->type == xcom_vtype_array )
        {
            return this->obj.array_val->empty();
        }
        else if (this->type == xcom_vtype_dict)
        {
            return this->obj.dict_val->empty();
        }
        else
        {
            return true;
        }
    }
    uint32_t xcom_var::size()
    {
        if (this->type == xcom_vtype_array )
        {
            return (uint32_t)this->obj.array_val->size();
        }
        else if (this->type == xcom_vtype_dict)
        {
            return (uint32_t)this->obj.dict_val->size();
        }
        else
        {
            return 1;
        }
    }
#ifdef __cplusplus
}
#endif
