//
// Created by connor on 7/8/18.
//

#include "Sprite.h"

using namespace Sova;

namespace Sova
{
    Sprite::Sprite(Ref<App> app, Ref<String> textureName) {
        this->app = app;
        this->textureName = textureName;
    }
}