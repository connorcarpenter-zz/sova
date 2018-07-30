//
// Created by connor on 7/8/18.
//

#include "DisplayObject.h"
#include "Sova/Math/Point.h"

namespace Sova
{
    Sova::DisplayObject::DisplayObject()
    {
        this->position = New<Point>();
        this->scale = New<Point>(1,1);
    }


    void DisplayObject::drawSelf(Ref<Camera> camera, int xoffset, int yoffset)
    {
        // do nothing, this should be overrided
    }
}