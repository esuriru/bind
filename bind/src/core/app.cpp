#include "core/app.hpp"

#include "dotnet/hostfxr_ctx.hpp"

namespace bind::core
{
    app::app()
    {
        hostfxr_ctx = new dotnet::hostfxr_ctx();
        hostfxr_ctx->init();
    }

    app::~app()
    {
        delete hostfxr_ctx;
    }
}
