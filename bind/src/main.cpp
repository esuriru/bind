#include "core/app.hpp"

int main()
{
    bind::core::app app =
        bind::core::app()
            .load_assembly("");

    return 0;
}