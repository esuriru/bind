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

        app& run_hostfxr(const std::filesystem::path& config_path);

        // To be called after `run_hostfxr`
        app& load_assembly(const std::filesystem::path& path,
            dotnet::assembly*& assembly);

    private:
        dotnet::hostfxr_ctx* hostfxr_ctx;
        dotnet::assembly* assembly;
    };
}