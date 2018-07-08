#pragma once

//
// Created by connor on 7/8/18.
//

#include <Modules/Core/String/String.h>
#include <Modules/Core/Containers/Array.h>
#include <functional>
#include "Viewport.h"
#include "Loader.h"

using namespace Oryol;

namespace Sova {

    class App
    {
    public:
        App(int width, int height, const char* windowTitle);
        Loader& load(std::initializer_list l);
        void start();
        void onUpdate(std::function<void()> updateFunction);
        void addViewport(const Viewport& viewport);

        int width;
        int height;
    private:
        Array<Viewport> viewports;
        String windowTitle;
        Loader loader;
    };

}