#pragma once

//
// Created by connor on 7/29/18.
//

#include "Shape.h"

namespace Sova
{
    class Rectangle : public Sova::Shape
    {
        SovaTypeDecl(Rectangle, Shape);
    public:
        Rectangle(int width, int height);
        Ref<Point> size = Null<Point>();
    };
}
