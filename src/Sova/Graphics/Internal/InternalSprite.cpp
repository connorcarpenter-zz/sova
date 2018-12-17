//
// Created by connor on 7/11/18.
//

#include <Sova/Graphics/Sprite.h>
#include <Sova/Graphics/AnimatedSprite.h>
#include <Sova/Internal/InternalApp.h>
#include "InternalSprite.h"
#include "Sova/Graphics/Internal/InternalCamera.h"
#include "InternalSpriteAtlasGlyph.h"

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

    void InternalSprite::draw(Sova::InternalCamera *internalCamera, int xoffset, int yoffset, AnimatedSprite *animSprite)
    {
        if (!this->mainSprite->checkSpriteAtlasLoaded())return;

        if (this->mainSprite->visible && this->texture != nullptr && this->texture->loaded) {
            if (this->spriteAtlasGlyph == nullptr) {

                if (animSprite == nullptr) {
                    this->updateVertices(nullptr, xoffset, yoffset, this->texture->width,
                                         this->texture->height,
                                         internalCamera->getWidth(), internalCamera->getHeight(),
                                         this->texture->width, this->texture->height, 0, 0, 1.0f, 1.0f, 0, 0);
                } else {
                    this->updateVertices(nullptr, xoffset, yoffset, this->texture->width,
                                         this->texture->height,
                                         internalCamera->getWidth(), internalCamera->getHeight(),
                                         animSprite->frameWidth,
                                         animSprite->frameHeight, animSprite->padding,
                                         (int) animSprite->imageIndex + animSprite->frameStartIndex,
                                         animSprite->scale->x,
                                         animSprite->scale->y, animSprite->skew->x, animSprite->skew->y);
                }
            }
            else {
                if (animSprite == nullptr) {
                    this->updateVertices(this->spriteAtlasGlyph, xoffset, yoffset, this->texture->width,
                                         this->texture->height,
                                         internalCamera->getWidth(), internalCamera->getHeight(),
                                         this->spriteAtlasGlyph->w, this->spriteAtlasGlyph->h, 0, 0, 1.0f, 1.0f, 0, 0);
                } else {
                    this->updateVertices(this->spriteAtlasGlyph, xoffset, yoffset, this->texture->width,
                                         this->texture->height,
                                         internalCamera->getWidth(), internalCamera->getHeight(),
                                         animSprite->frameWidth,
                                         animSprite->frameHeight, animSprite->padding,
                                         (int) animSprite->imageIndex + animSprite->frameStartIndex,
                                         animSprite->scale->x,
                                         animSprite->scale->y, animSprite->skew->x, animSprite->skew->y);
                }
            }
        }
    }

    void InternalSprite::updateVertices(InternalSpriteAtlasGlyph *spriteAtlasGlyph, int x, int y, int texWidth, int texHeight,
                                            int canWidth, int canHeight, int frameWidth, int frameHeight, int padding,
                                            int frameIndex, float xscale, float yscale, int xskew, int yskew)
    {
        //0 is 0, 1 is canvasWidth, canvasHeight
        int tw = (int) ((frameWidth - (padding*2)) * xscale);
        int th = (int) ((frameHeight - (padding*2)) * yscale);

        //0 is 0, 1 is texWidth/texHeight
        //This is the texture
        float x0, x1, y0, y1, rxskew, u0, u1, v0, v1;
        if (spriteAtlasGlyph == nullptr)
        {
            x0 = (x) / (float) canWidth;
            y0 = (y) / (float) canHeight;
            x1 = (x + tw) / (float) canWidth;
            y1 = (y + th) / (float) canHeight;
            rxskew = xskew / (float) canWidth;

            u0 = (float) ((frameIndex * frameWidth) + padding) / (float) texWidth;
            v0 = (float) padding / (float) texHeight;
            u1 = (float) (((frameIndex + 1) * frameWidth) - padding) / (float) texWidth;
            v1 = (float) (frameHeight - padding) / (float) texHeight;
        }
        else
        {
            x0 = (x) / (float) canWidth;
            y0 = (y) / (float) canHeight;
            x1 = (x + tw) / (float) canWidth;
            y1 = (y + th) / (float) canHeight;
            rxskew = xskew / (float) canWidth;

            int U0, U1, V0, V1;
            U0 = ((frameIndex * frameWidth) + padding + spriteAtlasGlyph->x);
            V0 = (padding + spriteAtlasGlyph->y);
            U1 = (((frameIndex + 1) * frameWidth) - padding + spriteAtlasGlyph->x);
            V1 = (frameHeight - padding + spriteAtlasGlyph->y);

            u0 = ((float) U0) / (float) texWidth;
            v0 = ((float) V0) / (float) texHeight;
            u1 = ((float) U1) / (float) texWidth;
            v1 = ((float) V1) / (float) texHeight;
        }
        InternalApp::getInternalApp()->drawer->draw(x0, y0, x1, y1, u0, v0, u1, v1, rxskew, this->texture->textureId,
                                                    this->mainSprite->tint, this->mainSprite->alpha);
    }

    int InternalSprite::getWidth() {
        if (this->spriteAtlasGlyph != nullptr)
            return this->spriteAtlasGlyph->w;
        if (this->texture != nullptr)
            return this->texture->width;
        return 0;
    }

    int InternalSprite::getHeight() {
        if (this->spriteAtlasGlyph != nullptr)
            return this->spriteAtlasGlyph->h;
        if (this->texture != nullptr)
            return this->texture->height;
        return 0;
    }

    bool InternalSprite::getTextureLoaded() {
        if (this->texture == nullptr) return false;
        return this->texture->loaded;
    }
}