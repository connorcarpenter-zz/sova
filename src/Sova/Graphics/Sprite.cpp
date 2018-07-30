//
// Created by connor on 7/8/18.
//

#include "Sprite.h"
#include "Sova/Graphics/Internal/InternalSprite.h"

using namespace Sova;

namespace Sova
{
    Sprite::Sprite(): internalSprite(new InternalSprite())
    {
        this->anchor = New<Point>();
    }

    Sprite::Sprite(Ref<String> textureName): internalSprite(new InternalSprite())
    {
        this->anchor = New<Point>();
        this->setTexture(textureName);
    }

    Sprite::~Sprite() {
        delete this->internalSprite;
    }

    void Sprite::setTexture(Ref<String> textureName)
    {
        this->textureName = textureName;

        this->internalSprite->setTexture(textureName);
    }

    void Sprite::drawSelf(Ref<Camera> camera, int xoffset, int yoffset) {
        this->internalSprite->draw(camera->getInternalCamera(),
                                       xoffset + this->position->x - this->anchor->x,
                                       yoffset + this->position->y - this->anchor->y);
    }

    int Sprite::getWidth() {
        return this->internalSprite->getWidth();
    }

    int Sprite::getHeight() {
        return this->internalSprite->getHeight();
    }

    bool Sprite::getVisible() {
        return this->internalSprite->visible;
    }

    void Sprite::setVisible(bool visible) {
        this->internalSprite->visible = visible;
    }
}