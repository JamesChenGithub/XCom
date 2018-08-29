#ifndef XCOM_BASE_XCSYSDEF_H
#define XCOM_BASE_XCSYSDEF_H

#if defined(__ANDROID__) || defined (ANDROID)
#define _OS_ANDROID_ 1

#elif (defined(_WIN32) || defined(_WIN64))
#define _OS_WIN_ 1

#elif defined(__APPLE__) || defined(__MACH__)

#if TARGET_OS_IPHONE
#define _OS_IOS_ 1

#if TARGET_IPHONE_SIMULATOR
#define _OS_IOS_SIMULATOR_ 1

#endif
#elif TARGET_OS_MAC
#define _OS_MAC_ 1

#else
#error Unsupported platform
#endif

#elif defined(__linux__) || defined(__CYGWIN__)
#define _OS_LINUX_ 1

#elif (!defined(_OS_MAC_) && !defined(_OS_IOS_) && !defined(_OS_ANDROID_) && !defined(_OS_WIN_) && !defined(_OS_LINUX_))
#error current system is not supported
#endif

#endif
