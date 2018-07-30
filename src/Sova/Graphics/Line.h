#pragma once

//
// Created by connor on 7/29/18.
//

#include "Shape.h"

namespace Sova
{
    class Line : public Sova::Shape
    {
        SovaTypeDecl(Line, Shape);
    public:
        Line();

        Ref<Point> endPosition = Null<Point>();
        virtual const char* getClassName() { return "Line"; }
        virtual void drawSelf(Ref<Camera> camera, int xoffset, int yoffset);
    };
}
