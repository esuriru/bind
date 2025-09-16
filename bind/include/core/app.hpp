#pragma once

#include "dotnet/hostfxr_ctx.hpp"

namespace bind::core
{
    class app
    {
    public:
        app();
        ~app();

    private:
        dotnet::hostfxr_ctx* hostfxr_ctx;
    };
}