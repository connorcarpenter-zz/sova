#pragma once

//
// Created by connor on 12/16/18.
//

#include <Sova/References/Refable.h>
#include <Sova/Common/String.h>
#include <Sova/Graphics/Internal/InternalSpriteAtlasGlyph.h>

namespace Sova {
    class InternalTexture;
    class InternalSpriteAtlas;
    class SpriteAtlas : public Sova::Refable {
    public:
        SpriteAtlas(Ref<Sova::String> atlasDataFileName);
        ~SpriteAtlas();
        int getKey(Ref<Sova::String> textureName);
        InternalSpriteAtlasGlyph* getGlyph(int key);
        InternalTexture* internalTexture = nullptr;
    private:
        InternalSpriteAtlas* internalSpriteAtlas = nullptr;
    };
}
