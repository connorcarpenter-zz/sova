//
// Created by connor on 12/16/18.
//

#include <Modules/Core/String/String.h>
#include <Sova/Internal/InternalApp.h>
#include <cstring>
#include "InternalSpriteAtlas.h"

namespace Sova {

    InternalSpriteAtlas::InternalSpriteAtlas(SpriteAtlas *spriteAtlas, Ref<String> atlasDataString) {
        this->mainSpriteAtlas = spriteAtlas;

        Oryol::String dataString = Oryol::String(atlasDataString->AsCStr());
        this->internalData = InternalApp::getInternalApp()->resourceManager.data[dataString];
    }

    InternalSpriteAtlasGlyph* InternalSpriteAtlas::getGlyph(int key) {
        return this->glyphMap.at(key);
    }

    int InternalSpriteAtlas::getKey(Ref<String> textureName) {
        checkDataLoaded();
        if (!this->loaded) return -1;

        cJSON* myTextureJson = findTexture(textureName);
        if (myTextureJson == nullptr) return -2;

        cJSON* frameObj = InternalJson::get(myTextureJson, "frame");
        if (frameObj == nullptr) return -2;

        cJSON* xObj = InternalJson::get(frameObj, "x");
        if (xObj == nullptr) return -2;
        int x = xObj->valueint;

        cJSON* yObj = InternalJson::get(frameObj, "y");
        if (yObj == nullptr) return -2;
        int y = yObj->valueint;

        cJSON* wObj = InternalJson::get(frameObj, "w");
        if (wObj == nullptr) return -2;
        int w = wObj->valueint;

        cJSON* hObj = InternalJson::get(frameObj, "h");
        if (hObj == nullptr) return -2;
        int h = hObj->valueint;

        cJSON* sprSrcSizeObj = InternalJson::get(myTextureJson, "spriteSourceSize");
        if (sprSrcSizeObj == nullptr) return -2;

        cJSON* srcXObj = InternalJson::get(sprSrcSizeObj, "x");
        if (srcXObj == nullptr) return -2;
        x -= srcXObj->valueint;

        cJSON* srcYObj = InternalJson::get(sprSrcSizeObj, "y");
        if (srcYObj == nullptr) return -2;
        y -= srcYObj->valueint;

        auto g = new InternalSpriteAtlasGlyph(x, y, w, h);
        int key = this->glyphMap.size();
        this->glyphMap.insert(std::pair<int,InternalSpriteAtlasGlyph*>(key, g));
        return key;
    }

    InternalSpriteAtlas::~InternalSpriteAtlas() {
        for (auto glyphKV : glyphMap){
            delete glyphKV.second;
        }
    }

    void InternalSpriteAtlas::checkDataLoaded() {
        if (this->loaded) return;
        if (!this->internalData->loaded) return;

        auto dataJson = internalData->json;
        cJSON* metaObj = InternalJson::get(dataJson, "meta");
        if (metaObj == nullptr) return;
        cJSON* imageObj = InternalJson::get(metaObj, "image");
        if (imageObj == nullptr) return;
        char* imageName = imageObj->valuestring;
        Oryol::StringBuilder sb("images/");
        sb.Append(imageName);
        this->mainSpriteAtlas->internalTexture = InternalApp::getInternalApp()->resourceManager.textures[sb.GetString()];

        this->loaded = true;
    }

    cJSON *InternalSpriteAtlas::findTexture(Ref<String> name) {
        auto dataJson = internalData->json;
        cJSON* framesObj = InternalJson::get(dataJson, "frames");
        if (framesObj == nullptr) return nullptr;
        cJSON* frameArrObj = framesObj->child;
        if (frameArrObj == nullptr) return nullptr;

        auto newName = name->TrimStart("images/");
        while(true)
        {
            if (strcmp(frameArrObj->child->valuestring, newName->AsCStr()) == 0)
            {
                //found the value!
                return frameArrObj;
            }

            frameArrObj = frameArrObj->next;
            if (frameArrObj == nullptr)
                return nullptr;
        }
    }
}