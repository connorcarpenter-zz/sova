//
// Created by connor on 7/8/18.
//

#include "DisplayObject.h"

namespace Sova
{
    Sova::DisplayObject::DisplayObject()
    {
        this->position = NewRef<Point>();
    }
}