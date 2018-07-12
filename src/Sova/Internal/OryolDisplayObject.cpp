//
// Created by connor on 7/11/18.
//

#include "OryolDisplayObject.h"
//#include "../DisplayObject.h"
#include "OryolApp.h"

using namespace Oryol;

namespace Sova
{
    Sova::OryolDisplayObject::OryolDisplayObject()//DisplayObject* sovaDisplayObject)
    {
        //this->sovaDisplayObject = sovaDisplayObject;

        this->oryolApp = OryolApp::getOryolApp();

        this->drawState.Mesh[0] = Gfx::CreateResource(this->oryolApp->meshSetup);
        this->drawState.Pipeline = Gfx::CreateResource(this->oryolApp->pipelineSetup);
        this->drawState.FSTexture[0] = this->oryolApp->texture;
    }

    void OryolDisplayObject::draw(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera)
    {
        const auto resState = Gfx::QueryResourceInfo(this->oryolApp->texture).State;
        if (resState == ResourceState::Valid)
        {
            const void* data = this->updateVertices(xoffset, yoffset, 128, 96, 640, 360);
            Gfx::UpdateVertices(this->drawState.Mesh[0], data, OryolApp::numVertexesInQuad);
            Gfx::ApplyDrawState(this->drawState);
        }

        Gfx::Draw();
    }

    const void* OryolDisplayObject::updateVertices(int x, int y, int width, int height, int canvasWidth, int canvasHeight)
    {
        int vIndex = 0;

        //0 is 0, 1 is canvasWidth, canvasHeight
        float x0 = (0.0f + x) / canvasWidth;
        float y0 = (0.0f + y) / canvasHeight;
        float x1 = (128.0f + x) / canvasWidth;
        float y1 = (96.0f + y) / canvasHeight;

        //0 is 0, 1 is texWidth/texHeight
        //This is the texture
        float u0 = 0.0f;
        float v0 = 0.0f;
        float u1 = 1.0f;
        float v1 = 1.0f;

        vIndex = this->writeVertex(vIndex, x0, y0, u0, v0);
        vIndex = this->writeVertex(vIndex, x1, y0, u1, v0);
        vIndex = this->writeVertex(vIndex, x1, y1, u1, v1);
        vIndex = this->writeVertex(vIndex, x0, y0, u0, v0);
        vIndex = this->writeVertex(vIndex, x1, y1, u1, v1);
        vIndex = this->writeVertex(vIndex, x0, y1, u0, v1);

        return OryolApp::getOryolApp()->vertexBuffer;
    }

//------------------------------------------------------------------------------
    int OryolDisplayObject::writeVertex(int index, float x, float y, float u, float v) {
        OryolApp::getOryolApp()->vertexBuffer[index].x = x;
        OryolApp::getOryolApp()->vertexBuffer[index].y = y;
        OryolApp::getOryolApp()->vertexBuffer[index].u = u;
        OryolApp::getOryolApp()->vertexBuffer[index].v = v;
        return index + 1;
    }
}