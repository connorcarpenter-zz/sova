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
    private:
        //DisplayObject* sovaDisplayObject = nullptr;
        Oryol::DrawState drawState;
        OryolApp* oryolApp;

        const void* updateVertices(int x, int y, int width, int height, int canvasWidth, int canvasHeight);
        int writeVertex(int index, float x, float y, float u, float v);
    };
}