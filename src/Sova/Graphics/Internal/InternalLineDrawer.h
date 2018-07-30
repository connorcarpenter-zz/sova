#pragma once

//
// Created by connor on 7/30/18.
//

#include <Modules/Gfx/GfxTypes.h>
#include <Sova/Graphics/Line.h>
#include "InternalCamera.h"

namespace Sova {
    class InternalLineDrawer {
    public:
        static InternalLineDrawer* getInstance();

        void draw(Sova::Line *mainLine, Sova::InternalCamera *internalCamera, int xoffset, int yoffset);

    private:
        InternalLineDrawer();
        static InternalLineDrawer* singleton;
        Oryol::DrawState drawState;

        struct data_t {
            float vertices[2 * 6];
        };
        data_t data;
    };
}