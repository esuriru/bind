#include "dotnet/assembly.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

namespace bind::dotnet
{
    assembly::assembly(hostfxr_ctx& ctx, const std::filesystem::path& path)
        : ctx(ctx)
        , valid(false)
    {
        assert(ctx.is_init());
        std::filesystem::path absolute = std::filesystem::absolute(path);
        std::wstring wide_str = absolute.wstring();

        valid = ctx.get_load_assembly_func()(wide_str.c_str(), nullptr, nullptr)
            == 0;
        if (!valid)
        {
            std::cerr << "Could not load assembly at " << absolute << std::endl;
        }
        else
        {
            std::cout << "Loaded assembly at " << absolute << std::endl;
            name = path.stem().wstring();
        }
    }

    assembly::~assembly() = default;

    bool assembly::is_valid() const
    {
        return valid;
    }

    void assembly::call_func(
        const std::wstring& type_name, const std::wstring& func_name)
    {
        void* func = nullptr;
        std::wstringstream stream;
        stream << type_name << ", " << name;
        std::wstring out = stream.str();
        int result = ctx.get_get_func_ptr_func()(out.c_str(),
            func_name.c_str(),
            UNMANAGEDCALLERSONLY_METHOD,
            nullptr,
            nullptr,
            &func);
        if (result == 0 && func)
        {
            (reinterpret_cast<void (*)()>(func))();
        }
    }
}
