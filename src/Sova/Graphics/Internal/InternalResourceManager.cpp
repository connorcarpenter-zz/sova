//
// Created by connor on 7/12/18.
//

#include <Sova/References/Ref.h>
#include <Modules/Gfx/Gfx.h>
#include <Modules/Gfx/private/gfxResourceContainer.h>
#include "InternalResourceManager.h"
#include "PNGLoader.h"
#include "Sova/Internal/InternalApp.h"
#include "Sova/Audio/Internal/InternalSound.h"

using namespace Oryol;

void InternalResourceManager::setup()
{
    textureSetup.Sampler.MinFilter = TextureFilterMode::Nearest;
    textureSetup.Sampler.MagFilter = TextureFilterMode::Nearest;
    textureSetup.Sampler.WrapU = TextureWrapMode::ClampToEdge;
    textureSetup.Sampler.WrapV = TextureWrapMode::ClampToEdge;
}

void InternalResourceManager::loadResource(Ref<String> resourceString)
{
    Oryol::String oryolStringId = Oryol::String(resourceString->AsCStr());

    Oryol::StringBuilder sb("content:");
    sb.Append(resourceString->AsCStr());

    if (resourceString->EndsWith(".png"))
    {
        std::function<void(TextureSetup&)> loadedFunc = [this, oryolStringId](Oryol::TextureSetup& texSetup) {
            this->updateResource(oryolStringId, texSetup);
        };

        Id internalTextureId = Gfx::LoadResource(
                PNGLoader::Create(
                        TextureSetup::FromFile(sb.GetString().AsCStr(), textureSetup),
                        loadedFunc));

        InternalTexture* internalTexture = new InternalTexture(internalTextureId);

        textures.Add(oryolStringId, internalTexture);
    }
    else if (resourceString->EndsWith(".wav")){

        InternalSound* internalSound = new InternalSound();
        sounds.Add(oryolStringId, internalSound);

        IO::Load(sb.GetString().AsCStr(), [this, internalSound](IO::LoadResult res) {
            internalSound->myWavData = std::move(res.Data);
            internalSound->myWav.loadMem(internalSound->myWavData.Data(), internalSound->myWavData.Size(), false, false);
            internalSound->updateAfterLoad();
        });
    }
}

void InternalResourceManager::updateResource(Oryol::String resourceString, const Oryol::TextureSetup& texSetup) {
    InternalTexture* oryolTexture = textures[resourceString];
    oryolTexture->updateAfterLoad(texSetup.Width, texSetup.Height);
}

InternalResourceManager::~InternalResourceManager() {
    //unload all OryolTextures

    for (auto textureKV : textures){
        delete textureKV.value;
    }

    for (auto soundKV : sounds){
        delete soundKV.value;
    }
}

Id InternalResourceManager::getMesh() {
    if (freeMeshes.Size() > 0)
    {
        Id id = freeMeshes.ValueAtIndex(0);
        freeMeshes.Erase(id);
        usedMeshes.Add(id);
        return id;
    }
    else
    {
        Id newId = Gfx::CreateResource(InternalApp::getInternalApp()->meshSetup);
        usedMeshes.Add(newId);
        return newId;
    }
}

void InternalResourceManager::releaseMesh(const Id& id) {
    if (usedMeshes.Contains(id))
    {
        usedMeshes.Erase(id);
        freeMeshes.Add(id);
    }
}


