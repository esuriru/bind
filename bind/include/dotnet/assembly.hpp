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
    
    private:
        bool valid;
    };
}