#pragma once

//
// Created by connor on 7/12/18.
//

#include <Modules/Resource/Id.h>

namespace Sova
{
    class InternalTexture
    {
    public:
        InternalTexture(const Oryol::Id& id);
        Oryol::Id textureId;
        int width = 0;
        int height = 0;
        bool loaded = false;

        void updateAfterLoad(int width, int height);
    };
}
