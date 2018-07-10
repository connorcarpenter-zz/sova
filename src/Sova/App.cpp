//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/OryolApp.h>
#include "App.h"

using namespace Sova;

namespace Sova {

    App::App(int width, int height, Ref<String> windowTitle, Ref<ShaderHandler> shaderHandler) {
        this->width = width;
        this->height = height;
        this->windowTitle = windowTitle;
        this->shaderHandler = shaderHandler;
    }

    void App::start() {
        OryolApp oryolApp(this);
        oryolApp.StartMainLoop();
    };

    Ref<Loader> App::load(Ref<List<Ref<String>>> resources) {
        loader->addResourcesToLoad(resources);
        return loader;
    };

    void App::onUpdate(std::function<void()> updateFunction){

    }

    void App::addViewport(Ref<Viewport> viewport) {

    }
}