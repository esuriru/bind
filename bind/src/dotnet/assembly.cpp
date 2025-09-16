#include "dotnet/assembly.hpp"

#include <cassert>
#include <iostream>

namespace bind::dotnet
{
    assembly::assembly(hostfxr_ctx& ctx, const std::filesystem::path& path)
        : valid(false)
    {
        assert(ctx.is_init());
        std::wstring wide_str = path.wstring();

        valid = ctx.get_load_assembly_func()(wide_str.c_str(), nullptr, nullptr)
            == 0;
        if (!valid)
        {
            std::cerr << "Could not load assembly at " << path << std::endl;
        }
    }

    assembly::~assembly() = default;

    bool assembly::is_valid() const
    {
        return valid;
    }
}
