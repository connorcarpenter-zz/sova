#pragma once

//
// Created by connor on 7/30/18.
//

#include <Modules/Gfx/GfxTypes.h>
#include <Sova/Graphics/Pixel.h>
#include "InternalCamera.h"

namespace Sova {
    class InternalPixelDrawer {
    public:
        static InternalPixelDrawer* getInstance();

        void draw(Sova::Pixel *mainPixel, Sova::InternalCamera *internalCamera, int xoffset, int yoffset);

    private:
        InternalPixelDrawer();
        static InternalPixelDrawer* singleton;
        Oryol::DrawState drawState;

        struct data_t {
            float vertices[6];
        };
        data_t data;
    };
}