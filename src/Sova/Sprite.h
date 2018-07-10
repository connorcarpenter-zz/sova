#pragma once

//
// Created by connor on 7/8/18.
//

#include "Sova/Common/String.h"
#include "Sova/Container.h"
#include <Sova/References/RefTypes.h>

using namespace Sova;

namespace Sova
{
    class Sprite : public Container {
    public:
        SovaTypeDecl(Sprite, Container);
        Sprite(Ref<String> textureName);

    private:

        //Ref<App> app = NullRef<App>();
        Ref<String> textureName = NullRef<String>();
    };
}