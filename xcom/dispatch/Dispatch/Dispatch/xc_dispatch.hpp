//
//  xc_dispatch.hpp
//  Dispatch
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef xc_dispatch_hpp
#define xc_dispatch_hpp

namespace xcom
{
    class Dispatch
    {
//    public:
//        
//        enum ID {
//            // The main thread.
//            UI = 0,
//            // This is the thread that interacts with the io.
//            IO,
//            // This is the thread that interacts with the db.
//            DB,
//            // This is the thread that process logic.
//            LOGIC,
//            // count
//            ID_COUNT
//        };
//        
//        static void Init();
//        static void Stop();
//        
//        static Thread* CreateThread(const char* name);
//        static Thread* GlobalThread();
//        
//        static bool PostTask(ID identifier, const std::function<void()>& task);
//        static bool PostDelayedTask(ID identifier, const std::function<void()>& task, TimeDelta delay);
//        static bool PostNonNestableTask(ID identifier, const std::function<void()>& task);
//        static bool PostNonNestableDelayedTask(ID identifier, const std::function<void()>& task, TimeDelta delay);
//        
//        static bool PostTask(Thread* thread, const std::function<void()>& task);
//        static bool PostDelayedTask(Thread* thread, const std::function<void()>& task, TimeDelta delay);
//        static bool PostNonNestableTask(Thread* thread, const std::function<void()>& task);
//        static bool PostNonNestableDelayedTask(Thread* thread, const std::function<void()>& task, TimeDelta delay);
//        
//    private:
//        
//        static Thread* CreateThread(const char* name, ID identifier);
//        
//        static bool PostTaskHelper(ID identifier, const std::function<void()>& task, TimeDelta delay, bool nestable);
//        static bool PostTaskHelper(Thread* thread, const std::function<void()>& task, TimeDelta delay, bool nestable);
//        
//    private:
//        Dispatch& operator=(const Dispatch&) = delete;
//        Dispatch(const Dispatch&) = delete;
//        Dispatch(const Dispatch&&) = delete;
        
        
    };
};

#endif /* xc_dispatch_hpp */
