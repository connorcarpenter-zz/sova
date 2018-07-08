#pragma once

//
// Created by connor on 7/8/18.
//

#include "Container.h"

namespace Sova {

    class Camera
    {

    public:
        Camera(int width, int height, const Container& container);

        Camera();
    };
}