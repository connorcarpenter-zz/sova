#pragma once

//
// Created by connor on 7/9/18.
//

#include <Sova/References/Refable.h>

namespace Sova
{
    class ShaderHandler : public virtual Refable
    {
    public:
        virtual Oryol::Id getNormalShader() = 0;
        virtual Oryol::Id getCanvasShader() = 0;
    };
}