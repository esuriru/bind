#include "dotnet/hostfxr_ctx.hpp"
#include "hostfxr.h"

#ifdef BIND_WIN
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#else
namespace
{
    constexpr size_t MAX_PATH = 260;
}
#endif

#include "coreclr_delegates.h"
#include "nethost.h"

#include <iostream>

// TODO - To replace with own assert
#include <cassert>


// TODO - Is there a need to separate out the different stages of init?
namespace bind::dotnet
{
    hostfxr_ctx::hostfxr_ctx()
        : lib_handle(nullptr)
        , handle(nullptr)
        , init_func(nullptr)
        , get_delegate_func(nullptr)
        , close_func(nullptr)
    {
    }

    int hostfxr_ctx::init()
    {
        char_t path_buf[MAX_PATH];
        size_t path_length = MAX_PATH;

        int result = get_hostfxr_path(path_buf, &path_length, nullptr);
        if (result != 0)
        {
            return -1;
        }

        auto view = std::wstring_view(path_buf, path_length);
        std::wcout << "Found hostfxr at " << view << "\n";

        // TODO - Defines
#ifdef BIND_WIN
        lib_handle = LoadLibraryW(path_buf);
#else
    #error "Platform not supported"
#endif

        if (!lib_handle)
        {
            return -1;
        }

#ifdef BIND_WIN
        init_func = reinterpret_cast<hostfxr_initialize_for_runtime_config_fn>(
            GetProcAddress(reinterpret_cast<HMODULE>(lib_handle),
                "hostfxr_initialize_for_runtime_config"));
        get_delegate_func = reinterpret_cast<hostfxr_get_runtime_delegate_fn>(
            GetProcAddress(reinterpret_cast<HMODULE>(lib_handle),
                "hostfxr_get_runtime_delegate"));
        close_func = reinterpret_cast<hostfxr_close_fn>(GetProcAddress(
            reinterpret_cast<HMODULE>(lib_handle), "hostfxr_close"));
#endif

        if (!init_func || !get_delegate_func || !close_func)
        {
            return -1;
        }

        return 0;
    }

    bool hostfxr_ctx::is_init() const
    {
        return static_cast<bool>(lib_handle);
    }

    int hostfxr_ctx::run(const std::filesystem::path& config_path)
    {
        assert(init_func && close_func);

        std::wstring wide_str = config_path.wstring();
        int result = init_func(wide_str.c_str(), nullptr, &handle);
        if (result != 0 || handle == nullptr)
        {
            std::cerr << "Could not initialize hostfxr handle\n";
            close_func(handle);
            return -1;
        }

        result = get_delegate_func(handle,
            hdt_load_assembly,
            reinterpret_cast<void**>(&load_assembly_func));
        if (result != 0)
        {
            return -1;
        }

        return 0;
    }

    int hostfxr_ctx::cleanup()
    {
        if (lib_handle)
        {
#ifdef BIND_WIN
            FreeLibrary(reinterpret_cast<HMODULE>(lib_handle));
#else
    #error "Platform not supported"
#endif
        }

        return 0;
    }
}
