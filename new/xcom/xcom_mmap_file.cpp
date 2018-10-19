//
//  xcom_util_bootrun.h
//  xcom
//
//  Created by AlexiChen on 2018/10/10.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//
#include "xcom_mmap_file.h"
//#include "txg_log.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <cstdint>
#include <stdlib.h>
#include <algorithm>

namespace XCom_NameSpace {
#if UWP
    
    DWORD SetFilePointer(
                         _In_ HANDLE hFile,
                         _In_ LONG lDistanceToMove,
                         _Inout_opt_ PLONG lpDistanceToMoveHigh,
                         _In_ DWORD dwMoveMethod
                         );
    
    
    HANDLE
    CreateFileW(
                _In_ LPCWSTR lpFileName,
                _In_ DWORD dwDesiredAccess,
                _In_ DWORD dwShareMode,
                _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                _In_ DWORD dwCreationDisposition,
                _In_ DWORD dwFlagsAndAttributes,//
                _In_opt_ HANDLE hTemplateFile
                );
    
    
    
    
    DWORD GetFileSize(
                      _In_      HANDLE  hFile,
                      _Out_opt_ LPDWORD lpFileSizeHigh
                      );
    
    
    HANDLE
    WINAPI
    CreateFileA(
                _In_ LPCSTR lpFileName,
                _In_ DWORD dwDesiredAccess,
                _In_ DWORD dwShareMode,
                _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                _In_ DWORD dwCreationDisposition,
                _In_ DWORD dwFlagsAndAttributes,
                _In_opt_ HANDLE hTemplateFile
                );
    
    
    HANDLE
    CreateFileMappingA(
                       _In_     HANDLE hFile,
                       _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
                       _In_     DWORD flProtect,
                       _In_     DWORD dwMaximumSizeHigh,
                       _In_     DWORD dwMaximumSizeLow,
                       _In_opt_ LPCSTR lpName
                       );
    
    LPVOID
    WINAPI
    MapViewOfFileEx(
                    _In_ HANDLE hFileMappingObject,
                    _In_ DWORD dwDesiredAccess,
                    _In_ DWORD dwFileOffsetHigh,
                    _In_ DWORD dwFileOffsetLow,
                    _In_ SIZE_T dwNumberOfBytesToMap,
                    _In_opt_ LPVOID lpBaseAddress
                    );
    
#endif
}


#else

# include <errno.h>
# include <fcntl.h>
# include <sys/mman.h>      // mmap, munmap.
# include <sys/stat.h>
# include <sys/types.h>     // struct stat.
# include <unistd.h>        // sysconf.
//#include "txg_log.h"

#endif

namespace XCom_NameSpace
{
    
    xcom_mmap_file_params::xcom_mmap_file_params() : flags(static_cast<xcom_mmap_mode >(0)), offset(0), length(static_cast<size_t>(-1)), newFileSize(0), hint(0)
    {
        
    }
    
    xcom_mmap_file_params::~xcom_mmap_file_params() {
        
    }
    
    void xcom_mmap_file_params::normalize()
    {
        if (flags)
        {
            switch (flags)
            {
                case xcom_mmap_mode::xcom_mmap_mode_read_only:
                case xcom_mmap_mode::xcom_mmap_mode_read_write:
                case xcom_mmap_mode::xcom_mmap_mode_priv:
                    break;
                default:
                    
                    break;
            }
        }
    }
    
    xcom_mmap_file::xcom_mmap_file() {
        clear(false);
    }
    
    xcom_mmap_file::~xcom_mmap_file() {
        close();
    }
    
    void xcom_mmap_file::open(xcom_mmap_file_params p)
    {
        if (is_open())
        {
            return;
        }
        p.normalize();
        open_file(p);
        // May modify p.hint
        map_file(p);
        m_params = p;
    }
    
    bool xcom_mmap_file::is_open() const
    {
        return (_data != 0 && _handle >= 0);
    }
    
    void xcom_mmap_file::close()
    {
        if (_data == 0)
            return;
        
        bool error = false;
        error = !unmap_file() || error;
#if defined(_WIN32)
        if(_handle != INVALID_HANDLE_VALUE)
#else
            if (_handle >= 0)
#endif
            {
                error =
#if defined(_WIN32)
                !::CloseHandle(_handle)
#else
                ::close(_handle) != 0
#endif
                || error;
            }
        clear(error);
        if (error)
        {
            //		throw_system_failure("failed closing mapped file");
        }
    }
    
    bool xcom_mmap_file::error() const {
        return _error;
    }
    
    xcom_mmap_file_params::xcom_mmap_mode xcom_mmap_file::flags() const {
        return m_params.flags;
    }
    
    std::size_t xcom_mmap_file::size() const {
        return _size;
    }
    
    char *xcom_mmap_file::data() const {
        return _data;
    }
    
    void xcom_mmap_file::resize(size_t newSize) {
        if (!is_open()) {
            //		mars_boost::throw_exception(BOOST_IOSTREAMS_FAILURE("file is closed"));
            return;
        }
        if (flags() & xcom_mmap_file_params::xcom_mmap_mode::xcom_mmap_mode_priv) {
            //		mars_boost::throw_exception(BOOST_IOSTREAMS_FAILURE("can't resize private mapped file"));
            return;
        }
        if (!(flags() & xcom_mmap_file_params::xcom_mmap_mode::xcom_mmap_mode_read_write)) {
            //		mars_boost::throw_exception(BOOST_IOSTREAMS_FAILURE("can't resize readonly mapped file"));
            return;
        }
        if (m_params.offset >= newSize) {
            //		mars_boost::throw_exception(BOOST_IOSTREAMS_FAILURE("can't resize below mapped offset"));
            return;
        }
        if (!unmap_file()) {
            cleanup("failed unmapping file");
            return;
        }
#if defined(_WIN32)
        DWORD offset = ::SetFilePointer(_handle, 0, NULL, FILE_CURRENT);
        if (offset == INVALID_SET_FILE_POINTER && ::GetLastError() != NO_ERROR) {
            cleanup("failed querying file pointer");
            return;
        }
        LONG sizehigh = (newSize >> (sizeof(LONG) * 8));
        LONG sizelow = (newSize & 0xffffffff);
        DWORD result = ::SetFilePointer(_handle, sizelow, &sizehigh, FILE_BEGIN);
        if ((result == INVALID_SET_FILE_POINTER && ::GetLastError() != NO_ERROR)
            || !::SetEndOfFile(_handle)) {
            cleanup("failed resizing mapped file");
            return;
        }
        sizehigh = (offset >> (sizeof(LONG) * 8));
        sizelow = (offset & 0xffffffff);
        ::SetFilePointer(_handle, sizelow, &sizehigh, FILE_BEGIN);
#else
        if (XCOM_FDTRUNCATE(_handle, newSize) == -1) {
            cleanup("failed resizing mapped file");
            return;
        }
#endif
        _size = newSize;
        map_file(m_params);
    }
    
    int xcom_mmap_file::alignment() {
#if defined(_WIN32)
        SYSTEM_INFO info;
        ::GetSystemInfo(&info);
        return static_cast<int>(info.dwAllocationGranularity);
#else
        return static_cast<int>(sysconf(_SC_PAGESIZE));
#endif
    }
    
    bool xcom_mmap_file::open_file(xcom_mmap_file_params p) {
        bool readonly = p.flags != xcom_mmap_file_params::xcom_mmap_mode::xcom_mmap_mode_read_write;
#if defined(_WIN32)
        // Open file
        DWORD dwDesiredAccess =
        readonly ?
        GENERIC_READ :
        (GENERIC_READ | GENERIC_WRITE);
        DWORD dwCreationDisposition = (p.newFileSize != 0 && !readonly) ?
        CREATE_ALWAYS :
        OPEN_EXISTING;
        DWORD dwFlagsandAttributes =
        readonly ?
        FILE_ATTRIBUTE_READONLY :
        FILE_ATTRIBUTE_TEMPORARY;
        _handle = p.path.is_wide() ?
        ::CreateFileW(
                      p.path.wstr().c_str(),
                      dwDesiredAccess,
                      FILE_SHARE_READ,
                      NULL,
                      dwCreationDisposition,
                      dwFlagsandAttributes,
                      NULL ) :
        ::CreateFileA(
                      p.path.str().c_str(),
                      dwDesiredAccess,
                      FILE_SHARE_READ,
                      NULL,
                      dwCreationDisposition,
                      dwFlagsandAttributes,
                      NULL );
        if (_handle == INVALID_HANDLE_VALUE) {
            cleanup("failed opening file");
            return false;
        }
        
        // Set file size
        if (p.newFileSize != 0 && !readonly) {
            LONG sizehigh = (p.newFileSize >> (sizeof(LONG) * 8));
            LONG sizelow = (p.newFileSize & 0xffffffff);
            DWORD result = ::SetFilePointer(_handle, sizelow, &sizehigh, FILE_BEGIN);
            if ((result == INVALID_SET_FILE_POINTER && ::GetLastError() != NO_ERROR) || !::SetEndOfFile(_handle)) {
                cleanup("failed setting file size");
                return false;
            }
        }
        
        // Determine file size. Dynamically locate GetFileSizeEx for compatibility
        // with old Platform SDK (thanks to Pavel Vozenilik).
        typedef BOOL (WINAPI *func)(HANDLE, PLARGE_INTEGER);
#ifdef UWP
        func get_size = &GetFileSizeEx;
#else
        HMODULE hmod = ::GetModuleHandleA("kernel32.dll");
        func get_size = reinterpret_cast<func>(::GetProcAddress(hmod, "GetFileSizeEx"));
#endif
        if (get_size) {
            LARGE_INTEGER info;
            if (get_size(_handle, &info)) {
                intmax_t size = ( (static_cast<intmax_t>(info.HighPart) << 32) | info.LowPart );
                _size = static_cast<std::size_t>( p.length != max_length ? (std::min<intmax_t>)(p.length, size) :size);
            } else {
                cleanup("failed querying file size");
                return false;
            }
        } else {
            DWORD hi;
            DWORD low;
            if ( (low = ::GetFileSize(_handle, &hi)) != INVALID_FILE_SIZE )
            {
                intmax_t size = (static_cast<intmax_t>(hi) << 32) | low;
                _size = static_cast<std::size_t>( p.length != max_length ? (std::min<intmax_t>)(p.length , size) : size);
            } else {
                cleanup("failed querying file size");
                return false;
            }
        }
#else
        // Open file
        int flags = (readonly ? O_RDONLY : O_RDWR);
        if (p.newFileSize != 0 && !readonly)
            flags |= (O_CREAT | O_TRUNC);
#ifdef _LARGEFILE64_SOURCE
        flags |= O_LARGEFILE;
#endif
        errno = 0;
        _handle = ::open(p.path.str().c_str(), flags, S_IRWXU);
        if (errno != 0) {
            cleanup("failed opening file");
            return false;
        }
        
        //--------------Set file size---------------------------------------------//
        
        if (p.newFileSize != 0 && !readonly)
            if (XCOM_FDTRUNCATE(_handle, p.newFileSize) == -1) {
                cleanup("failed setting file size");
                return false;
            }
        
        //--------------Determine file size---------------------------------------//
        
        bool success = true;
        if (p.length != max_length) {
            _size = p.length;
        } else {
            struct XCOM_FDSTAT info;
            success = ::XCOM_FDFSTAT(_handle, &info) != -1;
            _size = info.st_size;
        }
        if (!success) {
            cleanup("failed querying file size");
            return false;
        }
#endif
        return true;
    }
    
    bool xcom_mmap_file::try_map_file(xcom_mmap_file_params p) {
        bool priv = p.flags == xcom_mmap_file_params::xcom_mmap_mode::xcom_mmap_mode_priv;
        bool readonly = p.flags == xcom_mmap_file_params::xcom_mmap_mode::xcom_mmap_mode_read_only;
#if defined(_WIN32)
        // Create mapping
        DWORD protect = priv ?
        PAGE_WRITECOPY :
        readonly ?
        PAGE_READONLY :
        PAGE_READWRITE;
        m_mapped_handle =
        ::CreateFileMappingA(
                             _handle,
                             NULL,
                             protect,
                             0,
                             0,
                             NULL );
        if (m_mapped_handle == NULL)
            cleanup("failed create mapping");
        
        // Access data
        DWORD access = priv ?
        FILE_MAP_COPY :
        readonly ?
        FILE_MAP_READ :
        FILE_MAP_WRITE;
        void* data =
        ::MapViewOfFileEx(
                          m_mapped_handle,
                          access,
                          (DWORD) (p.offset >> 32),
                          (DWORD) (p.offset & 0xffffffff),
                          _size != max_length ? _size : 0,
                          (LPVOID) p.hint );
        if (!data) {
            cleanup("failed mapping view");
            return false;
        }
#else
        void *data =
        ::XCOM_FDMMAP(const_cast<char *>(p.hint), _size, readonly ? PROT_READ : (PROT_READ | PROT_WRITE), priv ? MAP_PRIVATE : MAP_SHARED, _handle, p.offset);
        if (data == MAP_FAILED)
        {
            cleanup("failed mapping file");
            return false;
        }
#endif
        _data = static_cast<char *>(data);
        return true;
    }
    
    bool xcom_mmap_file::map_file(xcom_mmap_file_params &p) {
        if(!try_map_file(p)){
            if (p.hint) {
                p.hint = 0;
                return try_map_file(p);
            } else {
                return false;
            }
        }
        return true;
    }
    
    bool xcom_mmap_file::unmap_file() {
#if defined(_WIN32)
        bool error = false;
        error = !::UnmapViewOfFile(_data) || error;
        error = !::CloseHandle(m_mapped_handle) || error;
        m_mapped_handle = NULL;
        return !error;
#else
        return ::munmap(_data, _size) == 0;
#endif
    }
    
    void xcom_mmap_file::clear(bool error) {
        m_params = xcom_mmap_file_params();
        _data = 0;
        _size = 0;
#if defined(_WIN32)
        _handle = INVALID_HANDLE_VALUE;
        m_mapped_handle = NULL;
#else
        _handle = -1;
#endif
        _error = error;
    }
    
    void xcom_mmap_file::cleanup(const char *msg) {
#if defined(_WIN32)
        DWORD error = GetLastError();
        if (m_mapped_handle != NULL)
            ::CloseHandle(m_mapped_handle);
        if (_handle != INVALID_HANDLE_VALUE)
            ::CloseHandle(_handle);
        SetLastError(error);
#else
        int error = errno;
        if (_handle >= 0)
            ::close(_handle);
        errno = error;
#endif
        clear(true);
        //        LOGE("%s", msg);
    }
    
}
