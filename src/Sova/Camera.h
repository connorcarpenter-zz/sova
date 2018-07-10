#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include "Container.h"

namespace Sova {

    class Camera : public virtual Refable
    {

    public:
        Camera(int width, int height, Ref<Container> container);
    };
}