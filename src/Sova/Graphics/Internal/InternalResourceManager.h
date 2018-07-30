#pragma once

//
// Created by connor on 7/12/18.
//

#include <Modules/Core/Containers/Map.h>
#include <Modules/Gfx/GfxTypes.h>

#include <Sova/Common/String.h>
#include "Sova/Graphics/Internal/InternalTexture.h"

namespace Sova
{
    class InternalResourceManager
    {

    public:
        ~InternalResourceManager();
        void loadResource(Ref<String> resourceString);

        void setup();

        Oryol::Map<Oryol::String, InternalTexture*> textures;

        Oryol::Id getMesh();
        void releaseMesh(const Oryol::Id& id);

    private:
        Oryol::TextureSetup textureSetup;

        void updateResource(Oryol::String resourceString, const Oryol::TextureSetup& texSetup);

        Oryol::Set<Oryol::Id> freeMeshes;
        Oryol::Set<Oryol::Id> usedMeshes;
    };
}

