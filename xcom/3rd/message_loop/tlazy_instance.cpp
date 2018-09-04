//
//  tlazy_instance.cpp
//  lite
//
//  Created by jasenhuang on 15/7/23.
//  Copyright (c) 2015年 tencent. All rights reserved.
//

#include "tlazy_instance.h"


#ifdef USE_NAMESPACE
namespace Lite {
#endif


bool NeedsLazyInstance(long* state) {
    
    if (CompareAndSwap(state, 0,kLazyInstanceStateCreating) == 0)
        return true;
    
    while (((AtomicLocation)state)->load(std::memory_order_acquire) == kLazyInstanceStateCreating) {
#if defined(WIN32)
		Sleep(0);
		SwitchToThread();
#else
        sched_yield();
#endif
    }
    return false;
}

#ifdef USE_NAMESPACE
};
#endif