#pragma once

//
// Created by connor on 7/8/18.
//

#include "Sova/Common/String.h"
#include "Container.h"
#include <Sova/References/RefTypes.h>

using namespace Sova;

namespace Sova
{
    class Sprite : public Container
    {
    public:
        SovaTypeDecl(Sprite, Container);
        Sprite();
        Sprite(Ref<String> textureName);
        virtual const char* getClassName() { return "Sprite"; }

    protected:
        void setTexture(Ref<String> textureName);

        Ref<String> textureName = Null<String>();
    };
}