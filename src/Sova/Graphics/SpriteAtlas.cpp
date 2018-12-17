//
// Created by connor on 12/16/18.
//

#include <Modules/Core/String/String.h>
#include <Sova/Internal/InternalApp.h>
#include "SpriteAtlas.h"

#include "Internal/InternalSpriteAtlas.h"

namespace Sova
{
    SpriteAtlas::SpriteAtlas(Ref<Sova::String> atlasDataFileName): internalSpriteAtlas(
            new InternalSpriteAtlas(this, atlasDataFileName)) {
    }

    SpriteAtlas::~SpriteAtlas() {
        delete this->internalSpriteAtlas;
    }

    int SpriteAtlas::getKey(Ref<Sova::String> textureName) {
        return this->internalSpriteAtlas->getKey(textureName);
    }

    InternalSpriteAtlasGlyph *SpriteAtlas::getGlyph(int key) {
        return this->internalSpriteAtlas->getGlyph(key);
    }
}