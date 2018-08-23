#pragma once

//
// Created by connor on 7/11/18.
//

#include "Gfx/Gfx.h"
#include "Sova/Internal/InternalApp.h"

#include <Sova/References/Ref.h>
#include <Sova/Graphics/Sprite.h>

namespace Sova
{
    class Viewport;
    class Camera;

    class InternalSprite
    {
    public:
        explicit InternalSprite(Sova::Sprite *mainSprite);
        ~InternalSprite();
        void draw(Sova::InternalCamera* internalCamera, int xoffset, int yoffset);
        void draw(Sova::InternalCamera *internalCamera, int xoffset, int yoffset, int frameWidth,
                          int frameHeight, int padding, int imageIndex, int xscale, int yscale);
        void setTexture(Ref<String> textureName);
        int getWidth();
        int getHeight();
        bool getTextureLoaded();
    private:

        InternalTexture* texture = nullptr;

        const void* updateVertices(int x, int y, int texWidth, int texHeight, int canvasWidth, int canvasHeight);
        int writeVertex(int index, float x, float y, float u, float v);

        const void *
        updateVertices(int x, int y, int texWidth, int texHeight, int canWidth, int canHeight, int frameWidth, int frameHeight,
                               int padding, int frameIndex, int xscale, int yscale);

        Sprite *mainSprite = nullptr;
        float tintR = 1.0f;
        float tintG = 1.0f;
        float tintB = 1.0f;
        Color currentTint = Color::White;

        void setupTint();
    };
}