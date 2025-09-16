#include "core/app.hpp"

#include "dotnet/hostfxr_ctx.hpp"

#include <iostream>

namespace bind::core
{
    app::app()
    {
        hostfxr_ctx = new dotnet::hostfxr_ctx();
        int result = hostfxr_ctx->init();

        if (result == 0)
        {
            std::cout << "Hostfxr initialized\n";
        }
    }

    app::~app()
    {
        hostfxr_ctx->cleanup();
        delete hostfxr_ctx;
    }

    app& app::load_assembly(const std::filesystem::path& path)
    {
        assembly = new dotnet::assembly(*hostfxr_ctx, path);
        return *this;
    }
}
