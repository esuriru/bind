#pragma once

#include "coreclr_delegates.h"
#include "hostfxr.h"

#include <filesystem>

namespace bind::dotnet
{
    class hostfxr_ctx
    {
    public:
        hostfxr_ctx();
        ~hostfxr_ctx() = default;

        [[__maybe_unused__]]
        int init();
        bool is_init() const;

        int run(const std::filesystem::path& config_path);
        const load_assembly_fn& get_load_assembly_func() const
        {
            return load_assembly_func;
        }

        int cleanup();
    
    private:
        void* lib_handle;

        hostfxr_handle handle;

        hostfxr_initialize_for_runtime_config_fn init_func;
        hostfxr_get_runtime_delegate_fn get_delegate_func;
        load_assembly_fn load_assembly_func;
        hostfxr_close_fn close_func;
    };
}