#pragma once

//
// Created by connor on 7/11/18.
//

#include "Gfx/Gfx.h"
#include "OryolApp.h"

#include <Sova/References/Ref.h>

namespace Sova
{
    class Viewport;
    class Camera;

    class OryolDisplayObject
    {
    public:
        explicit OryolDisplayObject();//DisplayObject* sovaDisplayObject);
        ~OryolDisplayObject();
        void draw(Sova::InternalCamera* internalCamera, int xoffset, int yoffset);
        void draw(Sova::InternalCamera *internalCamera, int xoffset, int yoffset, int frameWidth, int frameHeight,
                  int padding, int imageIndex);
        void setTexture(Ref<String> textureName);
        int getWidth();
        int getHeight();
        bool getTextureLoaded();

    private:

        OryolTexture* texture = nullptr;
        bool visible = false;

        const void* updateVertices(int x, int y, int texWidth, int texHeight, int canvasWidth, int canvasHeight);
        int writeVertex(int index, float x, float y, float u, float v);

        const void *updateVertices(int x, int y, int texWidth, int texHeight, int canWidth, int canHeight,
                                   int frameWidth,
                                   int frameHeight, int padding, int frameIndex);
    };
}