//
// Created by connor on 7/8/18.
//

#include "DisplayObject.h"
#include "Point.h"

namespace Sova
{
    Sova::DisplayObject::DisplayObject()
    {
        this->position = NewRef<Point>();
    }

    void DisplayObject::drawSelf(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera)
    {

    }
}