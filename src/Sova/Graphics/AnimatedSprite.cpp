//
// Created by connor on 7/26/18.
//

#include "AnimatedSprite.h"
#include "Sova/Internal/OryolDisplayObject.h"
#include "Sova/Graphics/Internal/InternalCamera.h"

namespace Sova
{

    AnimatedSprite::AnimatedSprite() {}

    AnimatedSprite::AnimatedSprite(Ref<String> textureName, int frameWidth, int frameHeight, int padding) {
        this->setTexture(textureName);
        this->frameWidth = frameWidth;
        this->frameHeight = frameHeight;
        this->padding = padding;
    }

    void AnimatedSprite::Update() {
        if (imageNumber == -1)
        {
            if (this->getTextureLoaded())
                this->imageNumber = this->getWidth() / this->frameWidth;
        }
        else
        {
            imageIndex += imageSpeed;
            if (imageIndex >= imageNumber)
                imageIndex -= imageNumber;
        }

        Container::Update();
    }

    void AnimatedSprite::drawSelf(Ref<Camera> camera, int xoffset, int yoffset) {
        this->oryolDisplayObject->draw(camera->getInternalCamera(), xoffset + this->position->x - this->anchor->x,
                                       yoffset + this->position->y - this->anchor->y, frameWidth, frameHeight, padding,
                                       (int) imageIndex, this->scale->x, this->scale->y);
    }

    bool AnimatedSprite::getTextureLoaded() {
        return this->oryolDisplayObject->getTextureLoaded();
    }
}