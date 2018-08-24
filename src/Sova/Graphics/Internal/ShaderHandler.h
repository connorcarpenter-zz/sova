#pragma once

//
// Created by connor on 7/9/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/RefTypes.h>
#include "Resource/Id.h"

using namespace Oryol;

namespace Sova
{
    class ShaderHandler : public Refable
    {
    public:
        SovaBaseTypeDecl(ShaderHandler);
        virtual const char* getClassName() { return "ShaderHandler"; }
        virtual Oryol::Id getScreenShader() = 0;
        virtual Oryol::Id getBackScreenShader() = 0;
        virtual Oryol::Id getCanvasShader() = 0;
        virtual Oryol::Id getShapeShader() = 0;
    };
}