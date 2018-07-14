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
#include "OryolResourceManager.h"

#include <Sova/App.h>

using namespace Oryol;
using namespace Sova;

class OryolApp : public Oryol::App {

public:
    OryolApp(Sova::App* sovaApp);
    AppState::Code OnRunning();
    AppState::Code OnInit();
    AppState::Code OnCleanup();

    static OryolApp* getOryolApp();
    static void initOryolApp(Sova::App* sovaApp);

    struct vertex {
        float x, y, u, v;
    };
    vertex vertexBuffer[6];
    PipelineSetup pipelineSetup;
    MeshSetup meshSetup;
    Id pipelineResource;
    Id meshResource;

    static const int numVertexesInQuad = 6 * sizeof(vertex);

    int canvasWidth = 0;
    int canvasHeight = 0;
    int dispWidth = 0;
    int dispHeight = 0;

    OryolResourceManager resourceManager;

    bool keyPressed(Sova::Key::Code key);

    bool mouseButtonPressed(Sova::MouseButton::Code btn);

    int getMouseX();

    int getMouseY();

private:
    static OryolApp* singleton;
    Sova::App* sovapp = nullptr;

    Id canvasPass;
    DrawState windowDrawState;

    void setupCanvas(const TextureSetup& rtSetup);
};