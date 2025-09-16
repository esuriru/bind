#include "bind.hpp"

int main()
{
    bind::core::app app =
        bind::core::app()
            .run_hostfxr("")
            .load_assembly("");

    return 0;
}