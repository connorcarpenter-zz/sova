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
        void draw(int xoffset, int yoffset);
        void setTexture(Ref<String> textureName);
        int getWidth();
        int getHeight();
    private:

        OryolTexture* texture = nullptr;
        bool visible = false;

        const void* updateVertices(int x, int y, int width, int height, int canvasWidth, int canvasHeight);
        int writeVertex(int index, float x, float y, float u, float v);

    };
}