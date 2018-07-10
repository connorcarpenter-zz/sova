#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>

#include "Sova/References/Ref.h"
#include "Internal/ShaderHandler.h"
#include "Viewport.h"
#include "Loader.h"
#include "Sova/Common/List.h"

using namespace Sova;

namespace Sova {

    class App : public Refable
    {
    public:
        App(int width, int height, Ref<String> windowTitle, Ref<ShaderHandler> shaderHandler);

        Ref<Loader> load(Ref<List<String>> resources);
        void start();
        void onUpdate(std::function<void()> updateFunction);
        void addViewport(Ref<Viewport> viewport);

        int width;
        int height;
        Ref<ShaderHandler> shaderHandler = NullRef<ShaderHandler>();
        Ref<Loader> loader = NewRef<Loader>();

    private:
        Ref<List<Viewport>> viewports = NullRef<List<Viewport>>();
        Ref<String> windowTitle = NullRef<String>();
    };

}