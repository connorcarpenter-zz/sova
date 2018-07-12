//
// Created by connor on 7/8/18.
//

#include "DisplayObject.h"
#include "Point.h"
#include "Internal/OryolDisplayObject.h"

namespace Sova
{
    Sova::DisplayObject::DisplayObject()
    : oryolDisplayObject(new OryolDisplayObject())
    {
        this->position = NewRef<Point>();
    }

    Sova::DisplayObject::~DisplayObject()
    {
        delete this->oryolDisplayObject;
    }

    void DisplayObject::drawSelf(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera)
    {
        this->oryolDisplayObject->draw(xoffset + this->position->x, yoffset + this->position->y, viewport, camera);
    }
}