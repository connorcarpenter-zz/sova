#pragma once

//
// Created by connor on 7/8/18.
//

#include "Camera.h"

namespace Sova
{
    class Viewport
    {

    public:
        Viewport(int x, int y, int width, int height, const Camera& camera);
    };
}
