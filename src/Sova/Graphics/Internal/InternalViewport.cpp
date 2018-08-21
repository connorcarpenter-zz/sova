//
// Created by connor on 7/26/18.
//

#include <Modules/Gfx/Gfx.h>
#include <Sova/Internal/InternalApp.h>
#include "InternalViewport.h"
#include "InternalCamera.h"

namespace Sova {
    InternalViewport::InternalViewport(Sova::Viewport *mainViewport)
    {
        this->mainViewport = mainViewport;
        setupWindow();
    }

    void InternalViewport::setupWindow()
    {
        //Setup onscreen render
        auto meshSetup = getMeshSetup();
        this->windowDrawState.Mesh[0] = Oryol::Gfx::CreateResource(meshSetup, &data, sizeof(data));

        Oryol::Id normalShader = InternalApp::getInternalApp()->getSovaApp()->shaderHandler->getNormalShader();
        auto ps = Oryol::PipelineSetup::FromLayoutAndShader(meshSetup.Layout, normalShader);

        if (this->mainViewport->getInternalCamera()->getBackgroundAlpha() != 1.0f) {
            ps.BlendState.BlendEnabled = true;
            ps.BlendColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
            ps.BlendState.ColorWriteMask = PixelChannel::RGB;
            ps.BlendState.DepthFormat = PixelFormat::DEPTHSTENCIL;
            ps.BlendState.SrcFactorRGB = (BlendFactor::Code) 4;
            ps.BlendState.DstFactorRGB = (BlendFactor::Code) 5;
        }

        this->windowDrawState.Pipeline = Oryol::Gfx::CreateResource(ps);
        this->windowDrawState.FSTexture[0] = this->mainViewport->getInternalCamera()->getCanvasTexture();
    }

    Oryol::DrawState InternalViewport::getDrawState()
    {
        return this->windowDrawState;
    }

    Oryol::MeshSetup InternalViewport::getMeshSetup()
    {
        auto ms = Oryol::MeshSetup::FromData();
        ms.NumVertices = 4;
        ms.NumIndices = 6;
        ms.IndicesType = IndexType::Index16;
        ms.Layout.Add(VertexAttr::Position, VertexFormat::Float3);
        ms.Layout.Add(VertexAttr::TexCoord0, VertexFormat::Float2);
        ms.AddPrimitiveGroup(PrimitiveGroup(0, 6));

        // vertices
        ms.VertexDataOffset = 0;
        ms.IndexDataOffset = offsetof(data_t, indices);

        float viewportx = this->mainViewport->position->x;
        float viewporty = this->mainViewport->position->y;
        float appwidth = InternalApp::getInternalApp()->dispWidth;
        float appheight = InternalApp::getInternalApp()->dispHeight;
        float viewportwidth = this->mainViewport->width;
        float viewportheight = this->mainViewport->height;

        float x1 = -1.0f + ((viewportx/appwidth)*2);
        float y1 = 1.0f - ((viewporty/appheight)*2);
        float x2 = -1.0f + (((viewportx+viewportwidth)/appwidth)*2);
        float y2 = 1.0f - (((viewporty+viewportheight)/appheight)*2);

        data.vertices[0] = x1; data.vertices[1] = y1;
        data.vertices[5] = x2; data.vertices[6] = y1;
        data.vertices[10] = x2; data.vertices[11] = y2;
        data.vertices[15] = x1; data.vertices[16] = y2;

        return ms;
    }
}