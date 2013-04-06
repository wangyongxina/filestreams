#pragma once
#include <windows.h>
#include <functional>
#include <memory>

// CloseHandle deleter for std::unique_ptr
struct CloseHandleDeleter
{
    typedef HANDLE pointer;

    void operator()(HANDLE handle) const
    {
        CloseHandle(handle);
    }
};

typedef std::unique_ptr<HANDLE, CloseHandleDeleter> auto_handle;

// Find file deleter for std::unique_ptr
struct FindCloseDeleter
{
    typedef HANDLE pointer;

    void operator()(HANDLE handle) const
    {
        FindClose(handle);
    }
};

typedef std::unique_ptr<HANDLE, FindCloseDeleter> find_handle;