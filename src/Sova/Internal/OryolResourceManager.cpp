//
// Created by connor on 7/12/18.
//

#include <Sova/References/Ref.h>
#include <Modules/Gfx/Gfx.h>
#include <Modules/Gfx/private/gfxResourceContainer.h>
#include "OryolResourceManager.h"
#include "PNGLoader.h"
#include "OryolApp.h"

using namespace Oryol;

void OryolResourceManager::setup()
{
    textureSetup.Sampler.MinFilter = TextureFilterMode::Nearest;
    textureSetup.Sampler.MagFilter = TextureFilterMode::Nearest;
    textureSetup.Sampler.WrapU = TextureWrapMode::ClampToEdge;
    textureSetup.Sampler.WrapV = TextureWrapMode::ClampToEdge;
}

void OryolResourceManager::loadResource(Ref<String> resourceString)
{
    Oryol::String oryolStringId = Oryol::String(resourceString->AsCStr());

    Oryol::StringBuilder sb("content:");
    sb.Append(resourceString->AsCStr());

    std::function<void(TextureSetup&)> loadedFunc = [this, oryolStringId](Oryol::TextureSetup& texSetup) {
        this->updateResource(oryolStringId, texSetup);
    };

    Id oryolTextureId = Gfx::LoadResource(
            PNGLoader::Create(
                    TextureSetup::FromFile(sb.GetString().AsCStr(), textureSetup),
                    loadedFunc));

    OryolTexture* oryolTexture = new OryolTexture(oryolTextureId);

    textures.Add(oryolStringId, oryolTexture);
}

void OryolResourceManager::updateResource(Oryol::String resourceString, const Oryol::TextureSetup& texSetup) {
    OryolTexture* oryolTexture = textures[resourceString];
    oryolTexture->updateAfterLoad(texSetup.Width, texSetup.Height);
}

OryolResourceManager::~OryolResourceManager() {
    //unload all OryolTextures

    for (auto textureKV : textures){
        delete textureKV.value;
    }
}

Id OryolResourceManager::getMesh() {
    if (freeMeshes.Size() > 0)
    {
        Id id = freeMeshes.ValueAtIndex(0);
        freeMeshes.Erase(id);
        usedMeshes.Add(id);
        return id;
    }
    else
    {
        Id newId = Gfx::CreateResource(OryolApp::getOryolApp()->meshSetup);
        usedMeshes.Add(newId);
        return newId;
    }
}

void OryolResourceManager::releaseMesh(const Id& id) {
    if (usedMeshes.Contains(id))
    {
        usedMeshes.Erase(id);
        freeMeshes.Add(id);
    }
}


