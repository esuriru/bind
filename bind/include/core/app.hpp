#pragma once

#include "dotnet/assembly.hpp"
#include "dotnet/hostfxr_ctx.hpp"

namespace bind::core
{
    class app
    {
    public:
        app();
        ~app();

        [[__maybe_unused__]]
        app& load_assembly(const std::filesystem::path& path);

    private:
        dotnet::hostfxr_ctx* hostfxr_ctx;
        dotnet::assembly* assembly;
    };
}