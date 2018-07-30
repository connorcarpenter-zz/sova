//
// Created by connor on 7/12/18.
//

#include "InternalTexture.h"

namespace Sova
{
    InternalTexture::InternalTexture(const Oryol::Id& id)
    {
        this->textureId = id;
    }

    void InternalTexture::updateAfterLoad(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->loaded = true;
    }
}