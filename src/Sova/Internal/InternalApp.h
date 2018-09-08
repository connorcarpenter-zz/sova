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
#include "Sova/Graphics/Internal/PNGLoader.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Sova/Graphics/Internal/InternalResourceManager.h"
#include "InternalDestructionManager.h"
#include "soloud.h"

#include <Sova/App.h>

namespace Sova {
    class InternalApp : public Oryol::App {

    public:
        InternalApp(Sova::App *sovaApp);

        Oryol::AppState::Code OnRunning();

        Oryol::AppState::Code OnInit();

        Oryol::AppState::Code OnCleanup();

        static InternalApp *getInternalApp();

        static Sova::App *getSovaApp();

        static void initInternalApp(Sova::App *sovaApp);

        static void *getGlobal();

        struct vertex {
            float x, y, u, v, r, g, b;
        };
        vertex vertexBuffer[6];
        Oryol::MeshSetup meshSetup;
        Oryol::Id pipelineResource;
        Oryol::Id meshResource;

        static const int numVertexesInQuad = 6 * sizeof(vertex);

        int dispWidth = 0;
        int dispHeight = 0;

        InternalResourceManager resourceManager;
        InternalDestructionManager destructionManager;

        static bool keyPressed(Sova::Key::Code key);

        static bool mouseButtonPressed(Sova::MouseButton::Code btn);

        static int getMouseX();

        static int getMouseY();

        SoLoud::Soloud soloud;
    private:
        static InternalApp *singleton;
        Sova::App *sovapp = nullptr;
    };
}