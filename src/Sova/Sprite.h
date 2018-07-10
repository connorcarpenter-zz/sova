#pragma once

//
// Created by connor on 7/8/18.
//

#include "Container.h"
#include "App.h"

using namespace Sova;

namespace Sova
{

    class App;
    class Sprite : public Container {
    public:

        Sprite(Ref<App> app, Ref<String> textureName);

    private:

        Ref<App> app;
        Ref<String> textureName;
    };
}