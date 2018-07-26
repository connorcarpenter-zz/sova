//
// Created by connor on 7/8/18.
//

#include "DisplayObject.h"
#include "Sova/Math/Point.h"
#include "Sova/Internal/OryolDisplayObject.h"
#include "Sova/Graphics/Internal/InternalCamera.h"

namespace Sova
{
    Sova::DisplayObject::DisplayObject()
    : oryolDisplayObject(new OryolDisplayObject())
    {
        this->position = New<Point>();
    }

    Sova::DisplayObject::~DisplayObject()
    {
        delete this->oryolDisplayObject;
    }

    void Sova::DisplayObject::setTexture(Ref<String> textureName)
    {
        this->oryolDisplayObject->setTexture(textureName);
    }

    void DisplayObject::drawSelf(Ref<Camera> camera, int xoffset, int yoffset)
    {
        this->oryolDisplayObject->draw(camera->getInternalCamera()->getDrawState(), xoffset + this->position->x, yoffset + this->position->y);
    }

    int DisplayObject::getWidth() {
        return this->oryolDisplayObject->getWidth();
    }

    int DisplayObject::getHeight() {
        return this->oryolDisplayObject->getHeight();
    }
}