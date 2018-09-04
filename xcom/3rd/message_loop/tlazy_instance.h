//
//  tlazy_instance.hpp
//  lite
//
//  Created by jasenhuang on 15/7/9.
//  Copyright © 2015年 tencent. All rights reserved.
//

#ifndef tlazy_instance_h
#define tlazy_instance_h

#include <iostream>
#include <atomic>
#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include "tbasictypes.h"

#ifdef USE_NAMESPACE
namespace Lite {
#endif

/** LazyInstance 的 实现 **/
static const long kLazyInstanceStateCreating = 1;
typedef volatile std::atomic<long>* AtomicLocation;

inline long CompareAndSwap(volatile long* ptr,long old_value,long new_value) {
    ((AtomicLocation)ptr)->compare_exchange_strong(old_value,
                                                   new_value,
                                                   std::memory_order_relaxed,
                                                   std::memory_order_relaxed);
    return old_value;
}

bool NeedsLazyInstance(long* state);

template <typename Type>
class LazyInstance {
public:
    
    Type& Get() {
        return *Pointer();
    }
    
    Type* Pointer() {
        
        static const long kLazyInstanceCreatedMask = ~kLazyInstanceStateCreating;
        
        long value = ((AtomicLocation)&private_instance_)->load(std::memory_order_acquire);
        
        if (!(value & kLazyInstanceCreatedMask) && NeedsLazyInstance(&private_instance_)) {
            value = reinterpret_cast<long>( new Type() );
            //把指针地址存进去
            ((AtomicLocation)&private_instance_)->store(value, std::memory_order_release);
        }
        return instance();
    }
    
    bool operator==(Type* p) = delete;
    
    long private_instance_;
    
private:
    Type* instance() {
        return reinterpret_cast<Type*>(((AtomicLocation)&private_instance_)->load(std::memory_order_relaxed));
    }
    
    void Release() {
        Type* me = instance();
        delete me;
        ((AtomicLocation)&me->private_instance_)->store(0, std::memory_order_relaxed);
    }
};



#if defined(WIN32)
// static
inline void AllocateSlot(DWORD* slot) {
    *slot = TlsAlloc();
}

// static
inline void FreeSlot(DWORD slot) {
    TlsFree(slot);
}
// static
inline void* GetValueFromSlot(DWORD slot) {
    return TlsGetValue(slot);
}
// static
inline void SetValueInSlot(DWORD slot, void* value) {
    TlsSetValue(slot, value);
}
#else
// static
inline void AllocateSlot(pthread_key_t* slot) {
    pthread_key_create(slot, NULL);
}

// static
inline void FreeSlot(pthread_key_t slot) {
    pthread_key_delete(slot);
}
// static
inline void* GetValueFromSlot(pthread_key_t slot) {
    return pthread_getspecific(slot);
}
// static
inline void SetValueInSlot(pthread_key_t slot, void* value) {
    pthread_setspecific(slot, value);
}
#endif

template <typename Type>
class ThreadLocalPointer {
public:
    ThreadLocalPointer() : slot_() {
        AllocateSlot(&slot_);
    }
    
    ~ThreadLocalPointer() {
        FreeSlot(slot_);
    }
    
    Type* Get() {
        return static_cast<Type*>(GetValueFromSlot(slot_));
    }
    
    void Set(Type* ptr) {
        SetValueInSlot(slot_, const_cast<void*>(static_cast<const void*>(ptr)));
    }
    
private:
#if defined(WIN32)
	DWORD slot_;
#else
    pthread_key_t slot_;
#endif
    
    DISALLOW_COPY_AND_ASSIGN(ThreadLocalPointer<Type>);
};

#ifdef USE_NAMESPACE
};
#endif
#endif /* tlazy_instance_cpp */
