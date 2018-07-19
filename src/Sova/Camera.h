#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Ref.h>
#include <Sova/References/Refable.h>

namespace Sova
{
    class Container;
    class Point;

    class Camera : public Refable
    {
    public:
        Camera(int x, int y, int width, int height, Ref <Container> target);
        virtual const char* getClassName() { return "Camera"; }
        void draw(int xoffset, int yoffset);

        Ref<Point> position = NullRef<Point>();
        int width;
        int height;
    private:

        Ref<Container> target = NullRef<Container>();
    };
}