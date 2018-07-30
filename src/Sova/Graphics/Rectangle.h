#pragma once

//
// Created by connor on 7/29/18.
//

#include "Shape.h"
#include "Line.h"

namespace Sova
{
    class Rectangle : public Sova::Shape
    {
        SovaTypeDecl(Rectangle, Shape);
    public:
        Rectangle(int width, int height);

        Ref<Point> size = Null<Point>();
        virtual const char* getClassName() { return "Rectangle"; }
        virtual void drawSelf(Ref<Camera> camera, int xoffset, int yoffset);

        void initLines();
    private:
        Ref<Line> topLine = Null<Line>();
        Ref<Line> leftLine = Null<Line>();
        Ref<Line> bottomLine = Null<Line>();
        Ref<Line> rightLine = Null<Line>();
    };
}
