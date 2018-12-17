#pragma once

//
// Created by connor on 7/12/18.
//

#include <Modules/Core/Containers/Map.h>
#include <Modules/Gfx/GfxTypes.h>

#include <Sova/Common/String.h>
#include <Sova/Internal/InternalJson.h>
#include "Sova/Graphics/Internal/InternalTexture.h"

namespace Sova
{
    class InternalSound;

    class InternalResourceManager
    {

    public:
        ~InternalResourceManager();
        void loadResource(Ref<String> resourceString);

        void setup();

        Oryol::Map<Oryol::String, InternalTexture*> textures;
        Oryol::Map<Oryol::String, InternalSound*> sounds;
        Oryol::Map<Oryol::String, InternalJson*> data;


    private:
        Oryol::TextureSetup textureSetup;

        void updateResource(Oryol::String resourceString, const Oryol::TextureSetup& texSetup);
    };
}

