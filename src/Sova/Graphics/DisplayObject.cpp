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
        this->anchor = New<Point>();
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
        this->oryolDisplayObject->draw(camera->getInternalCamera(), xoffset + this->position->x - this->anchor->x, yoffset + this->position->y - this->anchor->y);
    }

    int DisplayObject::getWidth() {
        return this->oryolDisplayObject->getWidth();
    }

    int DisplayObject::getHeight() {
        return this->oryolDisplayObject->getHeight();
    }

    bool DisplayObject::getVisible() {
        return this->oryolDisplayObject->visible;
    }

    void DisplayObject::setVisible(bool visible) {
        this->oryolDisplayObject->visible = visible;
    }
}