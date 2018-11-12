//
// Created by connor on 7/11/18.
//

#include <Sova/Graphics/Sprite.h>
#include <Sova/Graphics/AnimatedSprite.h>
#include "InternalSprite.h"
#include "Sova/Graphics/Internal/InternalCamera.h"

using namespace Oryol;

namespace Sova
{
    Sova::InternalSprite::InternalSprite(Sova::Sprite *mainSprite)//DisplayObject* sovaDisplayObject)
    {
        this->mainSprite = mainSprite;
    }

    Sova::InternalSprite::~InternalSprite()
    {
    }

    void InternalSprite::setTexture(Ref<String> textureName)
    {
        Oryol::String textureString = Oryol::String(textureName->AsCStr());
        this->texture = InternalApp::getInternalApp()->resourceManager.textures[textureString];

        this->mainSprite->visible = true;
    }

    void InternalSprite::draw(Sova::InternalCamera* internalCamera, int xoffset, int yoffset)
    {
        if (this->mainSprite->visible)
        {
            const auto resState = Gfx::QueryResourceInfo(this->texture->textureId).State;
            if (resState == ResourceState::Valid)
            {
                auto drawState = internalCamera->getDrawState(); //for some reason, copying the DrawState is necessary before using it... perhaps it's because only one DrawState can be used at a time

                drawState.FSTexture[0] = this->texture->textureId;
                this->setupTint();
                const void *data = this->updateVertices(xoffset,
                                                        yoffset,
                                                        this->texture->width,
                                                        this->texture->height,
                                                        internalCamera->getWidth(),
                                                        internalCamera->getHeight());
                Gfx::UpdateVertices(drawState.Mesh[0], data, InternalApp::numVertexesInQuad);
                Gfx::ApplyDrawState(drawState);
            }
        }

        Gfx::Draw();
    }

    void InternalSprite::draw(Sova::InternalCamera *internalCamera, int xoffset, int yoffset, AnimatedSprite *animSprite)
    {
        if (this->mainSprite->visible)
        {
            const auto resState = Gfx::QueryResourceInfo(this->texture->textureId).State;
            if (resState == ResourceState::Valid)
            {
                auto drawState = internalCamera->getDrawState(); //for some reason, copying the DrawState is necessary before using it... perhaps it's because only one DrawState can be used at a time

                drawState.FSTexture[0] = this->texture->textureId;
                this->setupTint();
                const void *data = this->updateVertices(xoffset, yoffset, this->texture->width, this->texture->height,
                                                        internalCamera->getWidth(), internalCamera->getHeight(),
                                                        animSprite->frameWidth, animSprite->frameHeight,
                                                        animSprite->padding,
                                                        (int) animSprite->imageIndex + animSprite->frameStartIndex,
                                                        animSprite->scale->x, animSprite->scale->y, animSprite->skew->x, animSprite->skew->y);
                Gfx::UpdateVertices(drawState.Mesh[0], data, InternalApp::numVertexesInQuad);
                Gfx::ApplyDrawState(drawState);
            }
        }

        Gfx::Draw();
    }

    const void* InternalSprite::updateVertices(int x, int y, int texWidth, int texHeight, int canvasWidth, int canvasHeight)
    {
        int vIndex = 0;

        //0 is 0, 1 is canvasWidth, canvasHeight
        float x0 = (float) x / (float) canvasWidth;
        float y0 = (float) y / (float) canvasHeight;
        float x1 = (float) (texWidth + x) / (float) canvasWidth;
        float y1 = (float) (texHeight + y) / (float) canvasHeight;

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

        return InternalApp::getInternalApp()->vertexBuffer;
    }

    const void * InternalSprite::updateVertices(int x, int y, int texWidth, int texHeight, int canWidth, int canHeight, int frameWidth,
                                                    int frameHeight, int padding, int frameIndex, float xscale, float yscale, int xskew,
                                                    int yskew)
    {
        int vIndex = 0;

        //0 is 0, 1 is canvasWidth, canvasHeight
        int tw = (int) ((frameWidth - (padding*2)) * xscale);
        int th = (int) ((frameHeight - (padding*2)) * yscale);
        float x0 = (x) / (float) canWidth;
        float y0 = (y) / (float) canHeight;
        float x1 = (x + tw) / (float) canWidth;
        float y1 = (y + th) / (float) canHeight;

        float rxskew = xskew / (float) canWidth;

        //0 is 0, 1 is texWidth/texHeight
        //This is the texture
        float u0 = (float) ((frameIndex * frameWidth) + padding) / (float) texWidth;
        float v0 = (float) padding / (float) texHeight;
        float u1 = (float) (((frameIndex+1) * frameWidth) - padding) / (float) texWidth;
        float v1 = (float) (frameHeight - padding) / (float) texHeight;

        vIndex = this->writeVertex(vIndex, x0 + rxskew, y0, u0, v0);
        vIndex = this->writeVertex(vIndex, x1 + rxskew, y0, u1, v0);
        vIndex = this->writeVertex(vIndex, x1, y1, u1, v1);
        vIndex = this->writeVertex(vIndex, x0 + rxskew, y0, u0, v0);
        vIndex = this->writeVertex(vIndex, x1, y1, u1, v1);
        vIndex = this->writeVertex(vIndex, x0, y1, u0, v1);

        return InternalApp::getInternalApp()->vertexBuffer;
    }

//------------------------------------------------------------------------------
    int InternalSprite::writeVertex(int index, float x, float y, float u, float v) {
        InternalApp::getInternalApp()->vertexBuffer[index].x = x;
        InternalApp::getInternalApp()->vertexBuffer[index].y = y;
        InternalApp::getInternalApp()->vertexBuffer[index].u = u;
        InternalApp::getInternalApp()->vertexBuffer[index].v = v;
        InternalApp::getInternalApp()->vertexBuffer[index].r = this->tintR;
        InternalApp::getInternalApp()->vertexBuffer[index].g = this->tintG;
        InternalApp::getInternalApp()->vertexBuffer[index].b = this->tintB;
        InternalApp::getInternalApp()->vertexBuffer[index].a = this->mainSprite->alpha;
        return index + 1;
    }

    int InternalSprite::getWidth() {
        if (this->texture != nullptr)
            return this->texture->width;
        return 0;
    }

    int InternalSprite::getHeight() {
        if (this->texture != nullptr)
            return this->texture->height;
        return 0;
    }

    bool InternalSprite::getTextureLoaded() {
        return this->texture->loaded;
    }

    void InternalSprite::setupTint() {
        if (this->mainSprite->tint != this->currentTint){
            this->currentTint = this->mainSprite->tint;
            this->tintR = (float) this->currentTint.red / 255;
            this->tintG = (float) this->currentTint.green / 255;
            this->tintB = (float) this->currentTint.blue / 255;
        }
    }
}