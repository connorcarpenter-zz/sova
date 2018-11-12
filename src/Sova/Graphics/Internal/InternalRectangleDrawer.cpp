//
// Created by connor on 7/30/18.
//

#include "InternalRectangleDrawer.h"

#include "Pre.h"
#include <Modules/Gfx/Gfx.h>

#include <Sova/Internal/InternalApp.h>
#include <Sova/Math/Math.h>

using namespace Oryol;

namespace Sova
{
    InternalRectangleDrawer* InternalRectangleDrawer::singleton = nullptr;

    InternalRectangleDrawer* InternalRectangleDrawer::getInstance()
    {
        if (singleton == nullptr)
            singleton = new InternalRectangleDrawer();
        return singleton;
    }

    InternalRectangleDrawer::InternalRectangleDrawer()
    {
            auto meshSetup = MeshSetup::FromData();
            meshSetup.VertexUsage = Usage::Stream;
            meshSetup.NumVertices = 4;
            meshSetup.NumIndices = 6;
            meshSetup.IndicesType = IndexType::Index16;
            meshSetup.Layout = {
                    {VertexAttr::Position, VertexFormat::Float2},
                    {VertexAttr::Color0,   VertexFormat::Float4}
            };
            meshSetup.AddPrimitiveGroup({0, 6});
            meshSetup.VertexDataOffset = 0;
            meshSetup.IndexDataOffset = offsetof(data_t, indices);
            this->drawState.Mesh[0] = Gfx::CreateResource(meshSetup, &data, sizeof(data));

            Id shapeShader = InternalApp::getSovaApp()->shaderHandler->getShapeShader();
            auto ps = PipelineSetup::FromLayoutAndShader(meshSetup.Layout, shapeShader);
            ps.BlendState.BlendEnabled = true;
            ps.BlendColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
            ps.BlendState.ColorWriteMask = PixelChannel::RGBA;
            ps.BlendState.DepthFormat = PixelFormat::None;
            ps.BlendState.SrcFactorRGB = BlendFactor::SrcAlpha;
            ps.BlendState.DstFactorRGB = BlendFactor::OneMinusSrcAlpha;
            ps.BlendState.SrcFactorAlpha = BlendFactor::One;
            ps.BlendState.DstFactorAlpha = BlendFactor::Zero;
            ps.BlendState.OpAlpha = BlendOperation::Add;
            this->drawState.Pipeline = Gfx::CreateResource(ps);
    }

    void
    InternalRectangleDrawer::draw(Sova::Rectangle* mainRectangle, Sova::InternalCamera* internalCamera,
                                  int xoffset, int yoffset) {
        if (!mainRectangle->filling) return;
        if (mainRectangle->fillAlpha == 0.0f && internalCamera->getBackgroundAlpha()!=0.0f) return;

        float canW = internalCamera->getWidth();
        float canH = internalCamera->getHeight();

        int topLeftX = Math::Min(mainRectangle->position->x, mainRectangle->position->x + mainRectangle->size->x) + 1 + xoffset;
        int topLeftY = Math::Min(mainRectangle->position->y, mainRectangle->position->y + mainRectangle->size->y) + 1 + yoffset;
        int bottomRightX = Math::Max(mainRectangle->position->x, mainRectangle->position->x + mainRectangle->size->x) - 1 + xoffset;
        int bottomRightY = Math::Max(mainRectangle->position->y, mainRectangle->position->y + mainRectangle->size->y) - 1 + yoffset;

        //up-left
        data.vertices[0] = (float) topLeftX / canW;
        data.vertices[1] = (float) topLeftY / canH;

        //up-right
        data.vertices[6] = (float) bottomRightX / canW;
        data.vertices[7] = (float) topLeftY / canH;

        //down-left
        data.vertices[12] = (float) topLeftX / canW;
        data.vertices[13] = (float) bottomRightY / canH;

        //down-right
        data.vertices[18] = (float) bottomRightX / canW;
        data.vertices[19] = (float) bottomRightY / canH;

        //blend / alpha
        data.vertices[2] = (float) mainRectangle->fillColor.red / 255;
        data.vertices[3] = (float) mainRectangle->fillColor.green / 255;
        data.vertices[4] = (float) mainRectangle->fillColor.blue / 255;
        data.vertices[5] = mainRectangle->fillAlpha;
        data.vertices[8] = (float) mainRectangle->fillColor.red / 255;
        data.vertices[9] = (float) mainRectangle->fillColor.green / 255;
        data.vertices[10] = (float) mainRectangle->fillColor.blue / 255;
        data.vertices[11] = mainRectangle->fillAlpha;
        data.vertices[14] = (float) mainRectangle->fillColor.red / 255;
        data.vertices[15] = (float) mainRectangle->fillColor.green / 255;
        data.vertices[16] = (float) mainRectangle->fillColor.blue / 255;
        data.vertices[17] = mainRectangle->fillAlpha;
        data.vertices[20] = (float) mainRectangle->fillColor.red / 255;
        data.vertices[21] = (float) mainRectangle->fillColor.green / 255;
        data.vertices[22] = (float) mainRectangle->fillColor.blue / 255;
        data.vertices[23] = mainRectangle->fillAlpha;

        //draw
        Gfx::UpdateVertices(drawState.Mesh[0], &data, 96);
        Gfx::ApplyDrawState(drawState);
        Gfx::Draw();

    }
}