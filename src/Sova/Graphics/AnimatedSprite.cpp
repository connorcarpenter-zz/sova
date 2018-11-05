//
// Created by connor on 7/26/18.
//

#include "AnimatedSprite.h"
#include "Sova/Graphics/Internal/InternalSprite.h"
#include "Sova/Graphics/Internal/InternalCamera.h"
#include "AnimatedSpriteInfo.h"
#include "AnimatedSequenceInfo.h"

namespace Sova
{

    AnimatedSprite::AnimatedSprite() {}

    AnimatedSprite::AnimatedSprite(Ref<String> textureName, int frameWidth, int frameHeight, int padding) {
        this->setTexture(textureName);
        this->frameWidth = frameWidth;
        this->frameHeight = frameHeight;
        this->padding = padding;
    }

    void AnimatedSprite::Update(float deltaFrameMs) {
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

        Container::Update(deltaFrameMs);
    }

    void AnimatedSprite::drawSelf(Ref<Camera> camera, int xoffset, int yoffset) {
        int rx = xoffset + this->position->x - (this->anchor->x * this->scale->x);
        int ry = yoffset + this->position->y - (this->anchor->y * this->scale->y);
        if (!this->spriteInsideCameraBounds(camera, rx, ry)) return;
        this->internalSprite->draw(camera->getInternalCamera(),
                                       rx, ry,
                                       frameWidth, frameHeight,
                                       padding,
                                       (int) imageIndex + frameStartIndex,
                                       this->scale->x, this->scale->y);
    }

    bool AnimatedSprite::getTextureLoaded() {
        return this->internalSprite->getTextureLoaded();
    }

    void AnimatedSprite::useAnimatedSpriteInfo(Ref<AnimatedSpriteInfo> animatedSpriteInfo) {

            if (animatedSpriteInfo == nullptr) return;
        {
            this->setTexture(animatedSpriteInfo->filename);
        }
            this->frameWidth = animatedSpriteInfo->frameWidth;
            this->frameHeight = animatedSpriteInfo->frameHeight;
            this->padding = animatedSpriteInfo->padding;
            this->anchor->x = animatedSpriteInfo->anchorX;
            this->anchor->y = animatedSpriteInfo->anchorY;
            this->imageNumber = this->getWidth() / this->frameWidth;

    }

    void AnimatedSprite::useAnimatedSequenceInfo(Ref<Sova::AnimatedSequenceInfo> animatedSequenceInfo) {
        if (animatedSequenceInfo == nullptr) return;
        this->useAnimatedSpriteInfo(animatedSequenceInfo->spriteInfo);

        this->frameStartIndex = animatedSequenceInfo->frameStart;
        this->frameEndIndex = animatedSequenceInfo->frameEnd;
        this->imageNumber = (this->frameEndIndex - this->frameStartIndex) + 1;
    }
}