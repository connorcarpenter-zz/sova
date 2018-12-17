#pragma once

//
// Created by connor on 7/11/18.
//

#include "Gfx/Gfx.h"

#include <Sova/References/Ref.h>
#include <Sova/Graphics/Sprite.h>
#include <Sova/Graphics/AnimatedSprite.h>

namespace Sova
{
    class Viewport;
    class Camera;
    class InternalSpriteAtlasGlyph;

    class InternalSprite
    {
    public:
        explicit InternalSprite(Sova::Sprite *mainSprite);
        ~InternalSprite();
        void draw(Sova::InternalCamera *internalCamera, int xoffset, int yoffset, AnimatedSprite *animSprite);
        void setTexture(Ref<String> textureName);
        int getWidth();
        int getHeight();
        bool getTextureLoaded();
        void setTexture(InternalTexture *internalTexture);

        InternalSpriteAtlasGlyph *spriteAtlasGlyph = nullptr;
    private:

        void updateVertices(InternalSpriteAtlasGlyph *spriteAtlasGlyph, int x, int y, int texWidth, int texHeight,
                                    int canWidth, int canHeight, int frameWidth, int frameHeight, int padding,
                                    int frameIndex, float xscale, float yscale, int xskew, int yskew);

        InternalTexture* texture = nullptr;
        Sprite *mainSprite = nullptr;
    };
}