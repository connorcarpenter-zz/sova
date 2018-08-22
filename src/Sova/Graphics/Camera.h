#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Ref.h>
#include <Sova/References/Refable.h>
#include "Color.h"

namespace Sova
{
    class Container;
    class Point;
    class InternalCamera;

    class Camera : public Refable
    {
    public:
        Camera(int x, int y, int width, int height, Ref<Container> target, Color bckColor = Color::Black, float bckAlpha = 1.0f, bool drawTarget = true,
                       bool autoRedraw = true);
        ~Camera();
        virtual const char* getClassName() { return "Camera"; }
        void draw(int xoffset, int yoffset);
        InternalCamera* getInternalCamera();

        Ref<Point> position = Null<Point>();
        int width;
        int height;
        bool drawTarget = true;
        bool autoRedraw = true;
        Color backgroundColor = Color::Black;
        float backgroundAlpha;
        int SkipFramesToDrawFramesRatio = 0;

    private:

        Ref<Container> target = Null<Container>();
        InternalCamera* internalCamera = nullptr;
        int skipFrames = 0;
    };
}