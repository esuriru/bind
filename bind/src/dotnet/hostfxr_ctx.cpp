#include "dotnet/hostfxr_ctx.hpp"
#include "hostfxr.h"
#include "nethost.h"

#include <cstdint>
#include <iostream>

namespace
{
    constexpr size_t MAX_PATH = 512;
}

namespace bind::dotnet
{
    int hostfxr_ctx::init()
    {
        char_t path_buf[MAX_PATH];
        size_t path_length {};

        int result = get_hostfxr_path(path_buf, &path_length, nullptr);
        if (result != 0)
        {
            return -1;
        }

        std::cout << path_length << std::endl;

        return 0;
    }
}
