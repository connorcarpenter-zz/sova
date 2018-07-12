//
// Created by connor on 7/12/18.
//

#include "OryolTexture.h"

namespace Sova
{
    OryolTexture::OryolTexture(const Oryol::Id& id)
    {
        this->textureId = id;
        this->loaded = false;
    }

    void OryolTexture::updateAfterLoad(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->loaded = true;
    }
}