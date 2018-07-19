//
// Created by connor on 7/8/18.
//

#include "Sprite.h"

using namespace Sova;

namespace Sova
{
    Sprite::Sprite(){}

    Sprite::Sprite(Ref<String> textureName)
    {
        this->setTexture(textureName);
    }

    void Sprite::setTexture(Ref<String> textureName)
    {
        this->textureName = textureName;
        DisplayObject::setTexture(textureName);
    }
}