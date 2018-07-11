//
// Created by connor on 7/8/18.
//

#include "Camera.h"


namespace Sova
{
    Sova::Camera::Camera(int width, int height, Ref<Container> target)
    {
        this->width = width;
        this->height = height;
        this->target = target;
    }

    void Sova::Camera::draw(Ref<Viewport> viewport)
    {
        this->target->draw(0, 0, viewport, ThisRef<Camera>());
    }
}