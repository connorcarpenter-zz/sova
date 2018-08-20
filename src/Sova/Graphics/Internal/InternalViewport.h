#pragma once

//
// Created by connor on 7/26/18.
//

#include <Sova/Graphics/Viewport.h>
#include <Modules/Gfx/GfxTypes.h>

namespace Sova {
    class InternalViewport {
    public:
        InternalViewport(Viewport* mainViewport);

        Oryol::DrawState getDrawState();
    private:
        Viewport* mainViewport = nullptr;
        Oryol::DrawState windowDrawState;

        void setupWindow();

        Oryol::MeshSetup getMeshSetup();

        struct data_t {
            float vertices[4 * 5] = {
                    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,     // top-left corner
                    0.0f, 0.0f, 0.0f, 1.0f, 1.0f,     // top-right corner
                    0.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // bottom-right corner
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f      // bottom-left corner
            };
            const uint16_t indices[2 * 3] = {
                    0, 2, 1,            // topleft -> bottomright -> topright
                    0, 3, 2,            // topleft -> bottomleft -> bottomright
            };
        } data;
    };
}