//
// Created by connor on 7/26/18.
//

#include <Modules/Gfx/Gfx.h>
#include <Sova/Internal/InternalApp.h>
#include "InternalCamera.h"

namespace Sova {
    InternalCamera::InternalCamera(Sova::Camera *mainCamera)
    {
        this->mainCamera = mainCamera;

        setupCanvas();
    }

    Oryol::Id InternalCamera::getCanvasPass()
    {
        return this->canvasPass;
    }

    void InternalCamera::setupCanvas()
    {
        //Setup offscreen render target
        auto renderTargetSetup = Oryol::TextureSetup::RenderTarget2D(this->mainCamera->width, this->mainCamera->height);
        renderTargetSetup.Sampler.MinFilter = Oryol::TextureFilterMode::Nearest;
        renderTargetSetup.Sampler.MagFilter = Oryol::TextureFilterMode::Nearest;
        this->canvasTexture = Oryol::Gfx::CreateResource(renderTargetSetup);
        auto passSetup = Oryol::PassSetup::From(this->canvasTexture);
        if (!this->mainCamera->autoDraw)
            passSetup.DefaultAction = PassAction::Load();
        this->canvasPass = Oryol::Gfx::CreateResource(passSetup);

        this->drawState.Mesh[0] = InternalApp::getInternalApp()->meshResource;
        this->drawState.Pipeline = InternalApp::getInternalApp()->pipelineResource;
    }

    Oryol::Id InternalCamera::getCanvasTexture() {
        return this->canvasTexture;
    }

    Oryol::DrawState InternalCamera::getDrawState() {
        return this->drawState;
    }

    int InternalCamera::getWidth() {
        return this->mainCamera->width;
    }

    int InternalCamera::getHeight() {
        return this->mainCamera->height;
    }
}
