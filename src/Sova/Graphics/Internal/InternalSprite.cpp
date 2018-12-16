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

    void InternalSprite::setTexture(InternalTexture* internalTexture)
    {
        this->texture = internalTexture;
        this->mainSprite->visible = true;
    }

    void InternalSprite::draw(Sova::InternalCamera* internalCamera, int xoffset, int yoffset)
    {
        if (this->mainSprite->visible)
        {
            const auto resState = Gfx::QueryResourceInfo(this->texture->textureId).State;
            if (resState == ResourceState::Valid)
            {
                this->updateVertices(xoffset,yoffset,
                                     this->texture->width,
                                     this->texture->height,
                                     internalCamera->getWidth(),
                                     internalCamera->getHeight());

            }
        }
    }

    void InternalSprite::draw(Sova::InternalCamera *internalCamera, int xoffset, int yoffset, AnimatedSprite *animSprite)
    {
        if (this->mainSprite->visible)
        {
            const auto resState = Gfx::QueryResourceInfo(this->texture->textureId).State;
            if (resState == ResourceState::Valid)
            {
                this->updateVertices(xoffset, yoffset, this->texture->width, this->texture->height,
                                                        internalCamera->getWidth(), internalCamera->getHeight(),
                                                        animSprite->frameWidth, animSprite->frameHeight,
                                                        animSprite->padding,
                                                        (int) animSprite->imageIndex + animSprite->frameStartIndex,
                                                        animSprite->scale->x, animSprite->scale->y, animSprite->skew->x, animSprite->skew->y);
            }
        }
    }

    void InternalSprite::updateVertices(int x, int y, int texWidth, int texHeight, int canvasWidth, int canvasHeight)
    {
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

        InternalApp::getInternalApp()->drawer->draw(x0, y0, x1, y1, u0, v0, u1, v1, this->texture->textureId,
                                                    this->mainSprite->tint, this->mainSprite->alpha);
    }

    void InternalSprite::updateVertices(int x, int y, int texWidth, int texHeight, int canWidth, int canHeight,
                                        int frameWidth,
                                        int frameHeight, int padding, int frameIndex, float xscale, float yscale,
                                        int xskew,
                                        int yskew)
    {
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

        InternalApp::getInternalApp()->drawer->draw(x0, y0, x1, y1, u0, v0, u1, v1, rxskew, this->texture->textureId,
                                                    this->mainSprite->tint, this->mainSprite->alpha);
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
}