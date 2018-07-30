//
// Created by connor on 7/26/18.
//

#include <Modules/Gfx/Gfx.h>
#include <Sova/Internal/InternalApp.h>
#include "InternalViewport.h"
#include "InternalCamera.h"

namespace Sova {
    InternalViewport::InternalViewport(Sova::Viewport *mainViewport) {
        this->mainViewport = mainViewport;

        setupWindow();
    }

    void InternalViewport::setupWindow(){
        //Setup onscreen render
        auto fullscreenQuadSetup = Oryol::MeshSetup::FullScreenQuad(Oryol::Gfx::QueryFeature(Oryol::GfxFeature::OriginTopLeft));
        this->windowDrawState.Mesh[0] = Oryol::Gfx::CreateResource(fullscreenQuadSetup);

        Oryol::Id normalShader = InternalApp::getInternalApp()->getSovaApp()->shaderHandler->getNormalShader();
        auto ps = Oryol::PipelineSetup::FromLayoutAndShader(fullscreenQuadSetup.Layout, normalShader);
        this->windowDrawState.Pipeline = Oryol::Gfx::CreateResource(ps);
        this->windowDrawState.FSTexture[0] = this->mainViewport->getInternalCamera()->getCanvasTexture();
    }

    Oryol::DrawState InternalViewport::getDrawState() {
        return this->windowDrawState;
    }
}