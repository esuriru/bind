#pragma once

#include "dotnet/hostfxr_ctx.hpp"

namespace bind::dotnet
{
    class assembly
    {
    public:
        assembly(hostfxr_ctx& ctx, const std::filesystem::path& path);
        ~assembly();

        bool is_valid() const;

        void call_func(const std::wstring& type_name, 
            const std::wstring& func_name);
    
    private:
        std::wstring name;
        hostfxr_ctx& ctx;
        bool valid;
    };
}