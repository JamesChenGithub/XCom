#ifndef XCOM_BASE_XCSYSDEF_H
#define XCOM_BASE_XCSYSDEF_H

#if defined(__ANDROID__) || defined (ANDROID)
#define XCOM_OS_ANDROID 1

#elif (defined(_WIN32) || defined(_WIN64))
#define XCOM_OS_WIN 1

#elif defined(__APPLE__) || defined(__MACH__)

#if TARGET_OS_IPHONE
#define XCOM_OS_IOS 1

#if TARGET_IPHONE_SIMULATOR
#define XCOM_OS_IOS_SIMULATOR 1

#endif
#elif TARGET_OS_MAC
#define XCOM_OS_MAC 1

#else
#error Unsupported platform
#endif

#elif defined(__linux__) || defined(__CYGWIN__)
#define XCOM_OS_LINUX 1

#elif (!defined(XCOM_OS_MAC) && !defined(XCOM_OS_IOS) && !defined(XCOM_OS_ANDROID) && !defined(XCOM_OS_WIN) && !defined(XCOM_OS_LINUX))
#error current system is not supported
#endif

#endif
