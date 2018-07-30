#pragma once

//
// Created by connor on 7/30/18.
//

#include <Modules/Gfx/GfxTypes.h>
#include <Sova/Graphics/Rectangle.h>
#include "InternalCamera.h"

namespace Sova {
    class InternalRectangleDrawer {
    public:
        static InternalRectangleDrawer* getInstance();

        void draw(Sova::Rectangle *mainRectangle, Sova::InternalCamera *internalCamera, int xoffset, int yoffset);

    private:
        InternalRectangleDrawer();
        static InternalRectangleDrawer* singleton;
        Oryol::DrawState drawState;

        struct data_t {
            float vertices[4 * 6];
            const uint16_t indices[2 * 3] = {
                    0, 1, 2,    // first triangle
                    2, 1, 3,    // second triangle
            };
        };
        data_t data;
    };
}