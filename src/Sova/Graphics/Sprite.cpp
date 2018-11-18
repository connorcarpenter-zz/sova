//
// Created by connor on 7/8/18.
//

#include <Sova/Math/Math.h>
#include "Sprite.h"
#include "Sova/Graphics/Internal/InternalSprite.h"

using namespace Sova;

namespace Sova
{
    Sprite::Sprite(): internalSprite(new InternalSprite(this))
    {
        this->anchor = New<Point>();
    }

    Sprite::Sprite(Ref<String> textureName): internalSprite(new InternalSprite(this))
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

    void Sprite::setTexture(Ref<AnimatedSpriteInfo> animatedSpriteInfo)
    {
        this->textureName = animatedSpriteInfo->filename;

        this->internalSprite->setTexture(animatedSpriteInfo->internalTexture);
    }

    void Sprite::drawSelf(Ref<Camera> camera, int xoffset, int yoffset) {
        int rx = xoffset + this->position->x - this->anchor->x;
        int ry = yoffset + this->position->y - this->anchor->y;
        if (!this->spriteInsideCameraBounds(camera, rx, ry)) return;
        this->internalSprite->draw(camera->getInternalCamera(), rx, ry);
    }

    int Sprite::getWidth() {
        return this->internalSprite->getWidth();
    }

    int Sprite::getHeight() {
        return this->internalSprite->getHeight();
    }

    bool Sprite::spriteInsideCameraBounds(Ref<Camera> camera, int xoffset, int yoffset) {
        return Math::BoxesOverlap(xoffset, yoffset, xoffset + this->getWidth(), yoffset + this->getHeight(),
                0, 0, camera->width, camera->height);
    }

    void Sprite::useSpriteInfo(Ref<AnimatedSpriteInfo> animatedSpriteInfo) {
        if (animatedSpriteInfo == nullptr) return;
        this->setTexture(animatedSpriteInfo);
        this->anchor->x = animatedSpriteInfo->anchorX;
        this->anchor->y = animatedSpriteInfo->anchorY;
    }
}