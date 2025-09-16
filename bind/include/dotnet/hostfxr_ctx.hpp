#pragma once

namespace bind::dotnet
{
    class hostfxr_ctx
    {
    public:
        hostfxr_ctx() = default;
        ~hostfxr_ctx() = default;

        [[__maybe_unused__]]
        int init();
    };
}