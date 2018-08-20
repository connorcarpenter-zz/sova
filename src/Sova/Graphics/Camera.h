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
    class InternalCamera;

    class Camera : public Refable
    {
    public:
        Camera(int x, int y, int width, int height, Ref <Container> target, bool autoDraw = true);
        ~Camera();
        virtual const char* getClassName() { return "Camera"; }
        void draw(int xoffset, int yoffset);
        InternalCamera* getInternalCamera();

        Ref<Point> position = Null<Point>();
        int width;
        int height;
        bool autoDraw = true;
    private:

        Ref<Container> target = Null<Container>();
        InternalCamera* internalCamera = nullptr;
    };
}