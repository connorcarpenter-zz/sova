//
// Created by connor on 8/29/18.
//

#include <Sova/Internal/InternalApp.h>
#include "AnimatedSpriteInfo.h"

namespace Sova {
    AnimatedSpriteInfo::AnimatedSpriteInfo(Ref<Sova::String> fileName, int frameWidth, int frameHeight, int padding,
                                           int anchorX, int anchorY) {
        this->imageName = fileName;
        this->frameWidth = frameWidth;
        this->frameHeight = frameHeight;
        this->padding = padding;
        this->anchorX = anchorX;
        this->anchorY = anchorY;

        this->internalTexture = InternalApp::getInternalApp()->resourceManager.textures[Oryol::String(imageName->AsCStr())];
    }

    AnimatedSpriteInfo::AnimatedSpriteInfo(Ref<Sova::String> fileName, bool autoSize, int anchorX, int anchorY) {
        this->imageName = fileName;
        this->anchorX = anchorX;
        this->anchorY = anchorY;
        this->autoSize = true;

        this->internalTexture = InternalApp::getInternalApp()->resourceManager.textures[Oryol::String(imageName->AsCStr())];
    }

    AnimatedSpriteInfo::AnimatedSpriteInfo(Ref<Sova::SpriteAtlas> spriteAtlas, Ref<Sova::String> fileName, int frameWidth, int frameHeight, int padding,
                                           int anchorX, int anchorY) {
        this->spriteAtlas = spriteAtlas;
        this->imageName = fileName;
        this->frameWidth = frameWidth;
        this->frameHeight = frameHeight;
        this->padding = padding;
        this->anchorX = anchorX;
        this->anchorY = anchorY;
    }

    AnimatedSpriteInfo::AnimatedSpriteInfo(Ref<Sova::SpriteAtlas> spriteAtlas, Ref<Sova::String> fileName, bool autoSize, int anchorX, int anchorY) {
        assert(autoSize);
        this->spriteAtlas = spriteAtlas;
        this->imageName = fileName;
        this->anchorX = anchorX;
        this->anchorY = anchorY;
        this->autoSize = true;
    }

    void AnimatedSpriteInfo::updateSpriteAtlasInfo() {
        if (this->spriteAtlas == nullptr) return;
        if (this->spriteAtlasKey != -1) return;
        if (this->spriteAtlasKey == -2) return;

        this->spriteAtlasKey = spriteAtlas->getKey(this->imageName);
        if (this->spriteAtlasKey == -1) return;
        if (this->spriteAtlasKey == -2) return;

        this->internalTexture = this->spriteAtlas->internalTexture;
        this->spriteAtlasGlyph = spriteAtlas->getGlyph(this->spriteAtlasKey);
    }
}
