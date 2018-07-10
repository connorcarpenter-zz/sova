#pragma once

//
// Created by connor on 7/7/18.
//

#include "Pre.h"
#include "Core/Main.h"
#include "Core/Containers/StaticArray.h"
#include "IO/IO.h"
#include "HttpFS/HTTPFileSystem.h"
#include "LocalFS/LocalFileSystem.h"
#include "Gfx/Gfx.h"
#include "Assets/Gfx/ShapeBuilder.h"
#include "PNGLoader.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Sova/App.h>

using namespace Oryol;
using namespace Sova;

class OryolApp : public Oryol::App {

public:
    OryolApp(Sova::App* sovaApp);
    AppState::Code OnRunning();
    AppState::Code OnInit();
    AppState::Code OnCleanup();
private:
    Sova::App* sovapp = nullptr;
    Id texture;
    Id canvasPass;
    DrawState canvasDrawState;

    int viewPortX = 0;
    int viewPortY = 0;
    int viewPortW = 0;
    int viewPortH = 0;

    int Width = 0;
    int Height = 0;
    int canvasWidth = 0;
    int canvasHeight = 0;
    int dispWidth = 0;
    int dispHeight = 0;

    void applyViewPort();

    void renderCanvas();
    void setupCanvas(const TextureSetup& rtSetup);
    Oryol::DrawState drawState;
    int numVertices;
    struct vertex {
        float x, y, u, v;
    };
    static const int MaxNumVertices = 6;
    vertex vertexBuffer[MaxNumVertices];

    const void* updateVertices(int& outNumBytes);

    int writeVertex(int index, float x, float y, float u, float v);
};