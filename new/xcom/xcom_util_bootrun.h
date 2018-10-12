//
//  xcom_util_bootrun.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef XCOM_UTIL_BOOTRUN_H_
#define XCOM_UTIL_BOOTRUN_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

__inline int xcom_boot_run_atstartup(void (*func)(void)) { func(); return 0;}
__inline int xcom_boot_run_atexit(void (*func)(void)) { return atexit(func);}

#ifdef __cplusplus
}
#endif

#define XCOM_BOOT_RUN_STARTUP(func)  static int __anonymous_run_variable_startup_##func = xcom_boot_run_atstartup(func)
#define XCOM_BOOT_RUN_EXIT(func)  static int __anonymous_run_variable_exit_##func = xcom_boot_run_atexit(func)

#endif /* TXG_BOOTRUN_H */
