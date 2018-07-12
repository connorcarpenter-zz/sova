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
        void draw(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera);
        void setTexture(Ref<String> textureName);
    private:
        //DisplayObject* sovaDisplayObject = nullptr;
        OryolApp* oryolApp;
        Oryol::DrawState drawState;
        Id texture;
        bool visible = false;

        const void* updateVertices(int x, int y, int width, int height, int canvasWidth, int canvasHeight);
        int writeVertex(int index, float x, float y, float u, float v);

    };
}