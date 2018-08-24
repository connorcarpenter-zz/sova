#pragma once

//
// Created by connor on 7/8/18.
//

#include "Camera.h"
#include "Sova/Math/Point.h"

namespace Sova
{
    class InternalViewport;
    class InternalCamera;

    class Viewport : public Refable
    {

    public:
        Viewport(int x, int y, int width, int height, Ref<Camera> camera, bool firstViewport);
        ~Viewport();
        virtual const char* getClassName() { return "Viewport"; }
        void drawCamera();
        void drawViewport();
        InternalCamera* getInternalCamera();

        Ref<Point> position = Null<Point>();
        int width;
        int height;
    private:

        Ref<Camera> camera = Null<Camera>();
        InternalViewport* internalViewport = nullptr;

    };
}
