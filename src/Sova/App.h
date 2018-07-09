#pragma once

//
// Created by connor on 7/8/18.
//

#include <Modules/Core/String/String.h>
#include <Modules/Core/Containers/Array.h>
#include <functional>
#include <Sova/Internal/ShaderHandler.h>
#include "Viewport.h"
#include "Loader.h"
#include "Resource/Id.h"

using namespace Oryol;
using namespace Sova;

namespace Sova {

    class App
    {
    public:
        App(int width, int height, const char *windowTitle, ShaderHandler* shaderHandler);

        App();

        Loader& load(const Array<String>& resources);
        void start();
        void onUpdate(std::function<void()> updateFunction);
        void addViewport(const Viewport& viewport);

        int width;
        int height;
        ShaderHandler* shaderHandler = nullptr;
    private:
        Array<Viewport> viewports;
        String windowTitle;
        Loader loader;
    };

}