#pragma once

//
// Created by connor on 7/26/18.
//

#include <Sova/Graphics/Camera.h>

#include <Modules/Resource/Id.h>

namespace Sova {
    class InternalCamera {
    public:
        explicit InternalCamera(Camera* mainCamera);

        Oryol::Id getCanvasPass();
        Oryol::Id getCanvasTexture();
        Oryol::DrawState getDrawState();

        int getWidth();

        int getHeight();

        float getBackgroundAlpha();

    private:
        Camera* mainCamera = nullptr;
        Oryol::Id canvasPass;
        Oryol::Id canvasTexture;
        Oryol::DrawState drawState;

        void setupCanvas();
    };
}