#pragma once

//
// Created by connor on 7/12/18.
//

#include <Modules/Resource/Id.h>

namespace Sova
{
    class OryolTexture
    {
    public:
        OryolTexture(const Oryol::Id& id);
        Oryol::Id textureId;
        int width;
        int height;
        bool loaded;

        void updateAfterLoad(int width, int height);
    };
}
