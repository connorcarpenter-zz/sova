#pragma once

//
// Created by connor on 7/8/18.
//

#include "Camera.h"

namespace Sova
{
    class Viewport : public Refable
    {

    public:
        Viewport(int x, int y, int width, int height, Ref<Camera> camera);
        void draw();
    private:
        int x;
        int y;
        int width;
        int height;
        Ref<Camera> camera = NullRef<Camera>();
    };
}
