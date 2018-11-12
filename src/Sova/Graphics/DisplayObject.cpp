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
        this->scale = New<FloatPoint>(1,1);
        this->skew = New<Point>(0,0);
    }
}