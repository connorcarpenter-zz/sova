#pragma once

//
// Created by connor on 7/29/18.
//

#include "Shape.h"

namespace Sova
{
    class Pixel : public Sova::Shape
    {
        SovaTypeDecl(Pixel, Shape);
    public:
        virtual const char* getClassName() { return "Pixel"; }
        virtual void drawSelf(Ref<Camera> camera, int xoffset, int yoffset);
    };
}
