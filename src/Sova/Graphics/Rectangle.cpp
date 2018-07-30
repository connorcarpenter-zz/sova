//
// Created by connor on 7/29/18.
//

#include "Pre.h"
#include <Modules/Gfx/Gfx.h>

#include <Sova/Internal/InternalApp.h>
#include <Sova/Graphics/Internal/InternalCamera.h>
#include "Rectangle.h"

using namespace Oryol;

namespace Sova
{
    Rectangle::Rectangle(int width, int height)
    {
        this->size = New<Point>(width, height);
        this->drawState = new Oryol::DrawState();

        static struct data_t {
            const float vertices[4 * 6] = {
                    // positions            colors
                    -0.5f,  0.5f,     0.5f, 0.0f, 0.0f, 0.5f,
                    0.5f,  0.5f,     0.0f, 0.5f, 0.0f, 0.5f,
                    0.5f, -0.5f,     0.0f, 0.0f, 0.5f, 0.5f,
                    -0.5f, -0.5f,     0.5f, 0.5f, 0.0f, 0.5f,
            };
            const uint16_t indices[2 * 3] = {
                    0, 1, 2,    // first triangle
                    2, 1, 3,    // second triangle
            };
        } data;

        auto meshSetup = MeshSetup::FromData();
        meshSetup.VertexUsage = Usage::Stream;
        meshSetup.NumVertices = 4;
        meshSetup.NumIndices = 6;
        meshSetup.IndicesType = IndexType::Index16;
        meshSetup.Layout = {
                { VertexAttr::Position, VertexFormat::Float2 },
                { VertexAttr::Color0, VertexFormat::Float4 }
        };
        meshSetup.AddPrimitiveGroup({0, 6});
        meshSetup.VertexDataOffset = 0;
        meshSetup.IndexDataOffset = offsetof(data_t, indices);
        this->drawState->Mesh[0] = Gfx::CreateResource(meshSetup, &data, sizeof(data));

        // create shader and pipeline-state-object
//        Id canvasShader = InternalApp::getSovaApp()->shaderHandler->getCanvasShader();
//        auto pipelineSetup = PipelineSetup::FromLayoutAndShader(meshSetup.Layout, canvasShader);
//        pipelineSetup.BlendState.BlendEnabled = true;
//        pipelineSetup.BlendState.SrcFactorRGB = BlendFactor::SrcAlpha;
//        pipelineSetup.BlendState.DstFactorRGB = BlendFactor::OneMinusSrcAlpha;
//        pipelineSetup.BlendState.ColorFormat = PixelFormat::RGBA8;
//        pipelineSetup.BlendState.DepthFormat = PixelFormat::None;
//        pipelineSetup.RasterizerState.CullFaceEnabled = false;
//        this->drawState->Pipeline = Gfx::CreateResource(pipelineSetup);

        Id shapeShader = InternalApp::getSovaApp()->shaderHandler->getShapeShader();
        auto ps = PipelineSetup::FromLayoutAndShader(meshSetup.Layout, shapeShader);
        ps.BlendState.BlendEnabled = true;
        ps.BlendColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        ps.BlendState.ColorWriteMask = PixelChannel::RGB;
        ps.BlendState.DepthFormat = PixelFormat::None;
        ps.BlendState.SrcFactorRGB = (BlendFactor::Code) 4;
        ps.BlendState.DstFactorRGB = (BlendFactor::Code) 5;
        //ps.BlendState.DstFactorAlpha = (BlendFactor::Code) 5;
        this->drawState->Pipeline = Gfx::CreateResource(ps);

    }

    Rectangle::~Rectangle() {
        delete drawState;
    }

    void Rectangle::drawSelf(Ref<Camera> camera, int xoffset, int yoffset)
    {
        float x = this->position->x;
        float y = this->position->y;
        float canW = camera->getInternalCamera()->getWidth();
        float canH = camera->getInternalCamera()->getHeight();

        struct data_t {
            float vertices[4 * 6];
            const uint16_t indices[2 * 3] = {
                    0, 1, 2,    // first triangle
                    0, 0, 0,    // second triangle
            };
        } data;

        //up-left
        data.vertices[0] = x / canW;
        data.vertices[1] = y / canH;
        data.vertices[2] = (float) this->fillColor.red / 255;
        data.vertices[3] = (float) this->fillColor.green / 255;
        data.vertices[4] = (float) this->fillColor.blue / 255;
        data.vertices[5] = this->fillAlpha;

        //up-right
        data.vertices[6] = data.vertices[0] + (float) this->size->x / canW;
        data.vertices[7] = data.vertices[1];
        data.vertices[8] = (float) this->fillColor.red / 255;
        data.vertices[9] = (float) this->fillColor.green / 255;
        data.vertices[10] = (float) this->fillColor.blue / 255;
        data.vertices[11] = this->fillAlpha;

        //down-left
        data.vertices[12] = data.vertices[0];
        data.vertices[13] = data.vertices[1] + (float) this->size->y / canH;
        data.vertices[14] = (float) this->fillColor.red / 255;
        data.vertices[15] = (float) this->fillColor.green / 255;
        data.vertices[16] = (float) this->fillColor.blue / 255;
        data.vertices[17] = this->fillAlpha;

        //down-right
        data.vertices[18] = data.vertices[0] + (float) this->size->x / canW;
        data.vertices[19] = data.vertices[1] + (float) this->size->y / canH;
        data.vertices[20] = (float) this->fillColor.red / 255;
        data.vertices[21] = (float) this->fillColor.green / 255;
        data.vertices[22] = (float) this->fillColor.blue / 255;
        data.vertices[23] = this->fillAlpha;

        Gfx::UpdateVertices(drawState->Mesh[0], &data, 96);

        Gfx::ApplyDrawState(*drawState);
        Gfx::Draw();
    }


}