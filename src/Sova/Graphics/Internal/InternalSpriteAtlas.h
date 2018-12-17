#pragma once

//
// Created by connor on 12/16/18.
//

#include <Sova/Graphics/SpriteAtlas.h>
#include "InternalSpriteAtlasGlyph.h"

namespace Sova {
    class InternalSpriteAtlas {
    public:
        InternalSpriteAtlas(SpriteAtlas *spriteAtlas, Ref<String> param);
        ~InternalSpriteAtlas();

        int getKey(Ref<String> textureName);

        InternalSpriteAtlasGlyph *getGlyph(int key);

    private:

        void checkDataLoaded();

        SpriteAtlas *mainSpriteAtlas = nullptr;
        std::map<int, InternalSpriteAtlasGlyph*> glyphMap;
        InternalJson *internalData = nullptr;
        bool loaded = false;

        cJSON *findTexture(Ref<String> name);

    };
}