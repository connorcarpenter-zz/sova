//
// Created by connor on 7/8/18.
//

#include "Camera.h"
#include "Container.h"

namespace Sova
{
    Sova::Camera::Camera(int x, int y, int width, int height, Ref <Container> target)
    {
        this->position = NewRef<Point>(x, y);
        this->width = width;
        this->height = height;
        this->target = target;
    }

    void Sova::Camera::draw(int xoffset, int yoffset)
    {
        this->target->Draw(xoffset - this->position->x, yoffset - this->position->y);
    }
}