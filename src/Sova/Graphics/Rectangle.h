#pragma once

//
// Created by connor on 7/29/18.
//

#include "Shape.h"

namespace Oryol {
    class DrawState;
}

namespace Sova
{
    class Rectangle : public Sova::Shape
    {
        SovaTypeDecl(Rectangle, Shape);
    public:
        Rectangle(int width, int height);
        ~Rectangle();
        Ref<Point> size = Null<Point>();
        virtual const char* getClassName() { return "Rectangle"; }
        virtual void drawSelf(Ref<Camera> camera, int xoffset, int yoffset);
    private:
        Oryol::DrawState* drawState = nullptr;


    };
}
