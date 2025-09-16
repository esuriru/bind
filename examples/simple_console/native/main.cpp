#include "bind.hpp"
#include "dotnet/assembly.hpp"

int main()
{
    bind::dotnet::assembly* assembly = nullptr;

    bind::core::app app;

    app.run_hostfxr("Debug/net9.0/managed.runtimeconfig.json")
        .load_assembly("Debug/net9.0/managed.dll", assembly);

    if (assembly)
    {
        assembly->call_func(L"SimpleConsole.Test", L"Write");
    }

    return 0;
}