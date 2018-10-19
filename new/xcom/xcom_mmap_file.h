//
//  xcom_mmap_file.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#ifndef XCOM_MMAP_FILE_H_
#define XCOM_MMAP_FILE_H_

#include <unistd.h>
#include "xcom_path.h"

#if defined(_WIN32)
typedef void*  file_handle;  // A.k.a. HANDLE
#else
typedef int file_handle;
#endif

#if defined(_WIN32)
# if defined(_MSC_VER) || defined(__MSVCRT__) // MSVC, MinGW
#  define XCOM_FDSEEK    _lseeki64
#  define XCOM_FDOFFSET  __int64
# else                                          // Borland, Metrowerks, ...
#  define XCOM_FDSEEK    lseek
#  define XCOM_FDOFFSET  long
# endif
#else // Non-windows
# if defined(_LARGEFILE64_SOURCE) && !defined(__APPLE__) && \
(!defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS != 64) || \
defined(_AIX) && !defined(_LARGE_FILES)
/**/

/* Systems with transitional extensions for large file support */

#  define XCOM_FDSEEK      lseek64
#  define XCOM_FDTRUNCATE  ftruncate64
#  define XCOM_FDMMAP      mmap64
#  define XCOM_FDSTAT      stat64
#  define XCOM_FDFSTAT     fstat64
#  define XCOM_FDOFFSET    off64_t
# else
#  define XCOM_FDSEEK      lseek
#  define XCOM_FDTRUNCATE  ftruncate
#  define XCOM_FDMMAP      mmap
#  define XCOM_FDSTAT      stat
#  define XCOM_FDFSTAT     fstat
#  define XCOM_FDOFFSET    off_t
# endif
#endif

namespace XCom_NameSpace
{
    class xcom_mmap_file_params {
    public:
        enum xcom_mmap_mode {
            xcom_mmap_mode_read_only = 1,
            xcom_mmap_mode_read_write = 2,
            xcom_mmap_mode_priv = 4
        };
        
        xcom_path path;
        xcom_mmap_mode flags;
        size_t offset;
        size_t length;
        size_t newFileSize;
        const char *hint;
        
        xcom_mmap_file_params();
        
        ~xcom_mmap_file_params();
        
        void normalize();
    };
    
    class xcom_mmap_file
    {
    public:
        const static size_t max_length = static_cast<size_t >(-1);
        
        xcom_mmap_file();
        
        ~xcom_mmap_file();
        
        void open(xcom_mmap_file_params p);
        
        bool is_open() const;
        
        void close();
        
        bool error() const;
        
        xcom_mmap_file_params::xcom_mmap_mode flags() const;
        
        std::size_t size() const;
        
        char *data() const;
        
        void resize(size_t newSize);
        
        static int alignment();
        
    private:
        bool open_file(xcom_mmap_file_params p);
        
        bool try_map_file(xcom_mmap_file_params p);
        
        bool map_file(xcom_mmap_file_params &p);
        
        bool unmap_file();
        
        void clear(bool error);
        
        void cleanup(const char *msg);
        
    private:
        
        char *_data;
        
        xcom_mmap_file_params m_params;
        
        size_t _size;
        
        file_handle _handle;
        
#if defined(_WIN32)
        file_handle 			m_mapped_handle;
#endif
        
        bool _error;
    };
    
}

#endif //XCOM_MMAP_FILE_H_
