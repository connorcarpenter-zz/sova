#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>

#include "Sova/References/Ref.h"
#include "Internal/ShaderHandler.h"
#include "Viewport.h"
#include "Loader.h"
#include "Sprite.h"

using namespace Sova;

namespace Sova {

    class Sprite;
    class App : public virtual Refable
    {
    public:
        App(int width, int height, Ref<String> windowTitle, Ref<ShaderHandler> shaderHandler);

        Loader& load(Ref<List<Ref<String>>> resources);
        void start();
        void onUpdate(std::function<void()> updateFunction);
        void addViewport(Ref<Viewport> viewport);

        int width;
        int height;
        Ref<ShaderHandler> shaderHandler = NullRef<ShaderHandler>();
        Ref<Loader> loader = NullRef<Loader>();

        Ref<Sprite> createSprite(Ref<String> textureName);

    private:
        Ref<List<Ref<Viewport>>> viewports;
        Ref<String> windowTitle;
    };

}