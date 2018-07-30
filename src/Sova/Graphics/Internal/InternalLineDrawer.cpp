//
// Created by connor on 7/30/18.
//

#include "InternalLineDrawer.h"

#include "Pre.h"
#include <Modules/Gfx/Gfx.h>
#include <Sova/Internal/InternalApp.h>

using namespace Oryol;

namespace Sova
{
    InternalLineDrawer* InternalLineDrawer::singleton = nullptr;

    InternalLineDrawer* InternalLineDrawer::getInstance()
    {
        if (singleton == nullptr)
            singleton = new InternalLineDrawer();
        return singleton;
    }

    InternalLineDrawer::InternalLineDrawer()
    {
        auto meshSetup = MeshSetup::FromData();
        meshSetup.VertexUsage = Usage::Stream;
        meshSetup.NumVertices = 2;
        meshSetup.Layout = {
                {VertexAttr::Position, VertexFormat::Float2},
                {VertexAttr::Color0,   VertexFormat::Float4}
        };
        meshSetup.AddPrimitiveGroup({0, 2});
        meshSetup.VertexDataOffset = 0;
        this->drawState.Mesh[0] = Gfx::CreateResource(meshSetup, &data, sizeof(data));

        Id shapeShader = InternalApp::getSovaApp()->shaderHandler->getShapeShader();
        auto ps = PipelineSetup::FromLayoutAndShader(meshSetup.Layout, shapeShader);
        ps.PrimType = PrimitiveType::Lines;
        ps.BlendState.BlendEnabled = true;
        ps.BlendColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        ps.BlendState.ColorWriteMask = PixelChannel::RGB;
        ps.BlendState.DepthFormat = PixelFormat::None;
        ps.BlendState.SrcFactorRGB = (BlendFactor::Code) 4;
        ps.BlendState.DstFactorRGB = (BlendFactor::Code) 5;
        this->drawState.Pipeline = Gfx::CreateResource(ps);
    }

    void
    InternalLineDrawer::draw(Sova::Line* mainLine, Sova::InternalCamera* internalCamera,
                                  int xoffset, int yoffset) {
        float x = mainLine->position->x;
        float y = mainLine->position->y;
        float canW = internalCamera->getWidth();
        float canH = internalCamera->getHeight();

        //start
        data.vertices[0] = x / canW;
        data.vertices[1] = y / canH;
        data.vertices[2] = (float) mainLine->lineColor.red / 255;
        data.vertices[3] = (float) mainLine->lineColor.green / 255;
        data.vertices[4] = (float) mainLine->lineColor.blue / 255;
        data.vertices[5] = mainLine->lineAlpha;

        //end
        data.vertices[6] = (float) mainLine->endPosition->x / canW;
        data.vertices[7] = (float) mainLine->endPosition->y / canH;
        data.vertices[8] = (float) mainLine->lineColor.red / 255;
        data.vertices[9] = (float) mainLine->lineColor.green / 255;
        data.vertices[10] = (float) mainLine->lineColor.blue / 255;
        data.vertices[11] = mainLine->lineAlpha;

        Gfx::UpdateVertices(drawState.Mesh[0], &data, 48);

        Gfx::ApplyDrawState(drawState);
        Gfx::Draw();

    }
}