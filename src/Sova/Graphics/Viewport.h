#pragma once

//
// Created by connor on 7/8/18.
//

#include "Camera.h"
#include "Sova/Math/Point.h"

namespace Sova
{
    class Viewport : public Refable
    {

    public:
        Viewport(int x, int y, int width, int height, Ref<Camera> camera);
        virtual const char* getClassName() { return "Viewport"; }
        void draw();

        Ref<Point> position = Null<Point>();
    private:
        int width;
        int height;
        Ref<Camera> camera = Null<Camera>();
    };
}
