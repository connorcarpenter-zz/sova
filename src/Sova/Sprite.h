#pragma once

//
// Created by connor on 7/8/18.
//

#include "Container.h"
#include "App.h"

using namespace Sova;

namespace Sova {

    class Sprite : public Container {
    public:
        Sprite(App& app, const char* resourceString);
    private:
    };
}