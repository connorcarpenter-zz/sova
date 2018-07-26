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
    };
}