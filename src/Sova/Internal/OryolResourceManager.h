#pragma once

//
// Created by connor on 7/12/18.
//

#include <Modules/Core/Containers/Map.h>
#include <Modules/Gfx/GfxTypes.h>

#include <Sova/Common/String.h>
#include "OryolTexture.h"

namespace Sova
{
    class OryolResourceManager
    {

    public:
        ~OryolResourceManager();
        void loadResource(Ref<String> resourceString);

        void setup();

        Oryol::Map<Oryol::String, OryolTexture*> textures;
    private:
        Oryol::TextureSetup textureSetup;

        void updateResource(Oryol::String resourceString, const Oryol::TextureSetup& texSetup);
    };
}

