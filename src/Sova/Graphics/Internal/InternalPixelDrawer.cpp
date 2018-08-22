//
// Created by connor on 7/30/18.
//

#include "InternalPixelDrawer.h"

#include "Pre.h"
#include <Modules/Gfx/Gfx.h>
#include <Sova/Internal/InternalApp.h>

using namespace Oryol;

namespace Sova
{
    InternalPixelDrawer* InternalPixelDrawer::singleton = nullptr;

    InternalPixelDrawer* InternalPixelDrawer::getInstance()
    {
        if (singleton == nullptr)
            singleton = new InternalPixelDrawer();
        return singleton;
    }

    InternalPixelDrawer::InternalPixelDrawer()
    {
        auto meshSetup = MeshSetup::FromData();
        meshSetup.VertexUsage = Usage::Stream;
        meshSetup.NumVertices = 1;
        meshSetup.Layout = {
                {VertexAttr::Position, VertexFormat::Float2},
                {VertexAttr::Color0,   VertexFormat::Float4}
        };
        meshSetup.AddPrimitiveGroup({0, 1});
        meshSetup.VertexDataOffset = 0;
        this->drawState.Mesh[0] = Gfx::CreateResource(meshSetup, &data, sizeof(data));

        Id shapeShader = InternalApp::getSovaApp()->shaderHandler->getShapeShader();
        auto ps = PipelineSetup::FromLayoutAndShader(meshSetup.Layout, shapeShader);
        ps.PrimType = PrimitiveType::Points;
        ps.BlendState.BlendEnabled = true;
        ps.BlendColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        ps.BlendState.ColorWriteMask = PixelChannel::RGBA;
        ps.BlendState.DepthFormat = PixelFormat::None;
        ps.BlendState.SrcFactorRGB = (BlendFactor::Code) 4;
        ps.BlendState.DstFactorRGB = (BlendFactor::Code) 5;
        ps.BlendState.SrcFactorAlpha = (BlendFactor::Code) 1;
        ps.BlendState.DstFactorAlpha = (BlendFactor::Code) 0;
        ps.BlendState.OpAlpha = BlendOperation::Add;
        this->drawState.Pipeline = Gfx::CreateResource(ps);
    }

    void
    InternalPixelDrawer::draw(Sova::Pixel* mainPixel, Sova::InternalCamera* internalCamera,
                                  int xoffset, int yoffset) {
        float x = mainPixel->position->x;
        float y = mainPixel->position->y;
        float canW = internalCamera->getWidth();
        float canH = internalCamera->getHeight();

        //start
        data.vertices[0] = x / canW;
        data.vertices[1] = y / canH;
        data.vertices[2] = (float) mainPixel->lineColor.red / 255;
        data.vertices[3] = (float) mainPixel->lineColor.green / 255;
        data.vertices[4] = (float) mainPixel->lineColor.blue / 255;
        data.vertices[5] = mainPixel->lineAlpha;

        Gfx::UpdateVertices(drawState.Mesh[0], &data, 24);

        Gfx::ApplyDrawState(drawState);
        Gfx::Draw();
    }
}