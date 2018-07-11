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

        this->loader = NewRef<Loader>();
        this->viewports = NewRef<List<Viewport>>();
    }

    void App::start() {
        OryolApp oryolApp(this);
        oryolApp.StartMainLoop();
    };

    Ref<Loader> App::load(Ref<List<String>> resources) {
        this->loader->addResourcesToLoad(resources);
        return this->loader;
    };

    void App::onUpdate(std::function<void()> updateFunction){
        this->updateFunction = updateFunction;
    }

    void App::addViewport(Ref<Viewport> viewport) {
        this->viewports->Add(viewport);
    }

    void App::draw()
    {
        for (Ref<ListIterator<Viewport>> iterator = this->viewports->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Viewport> viewport = iterator->Get();
            viewport->draw();
        }
    }
}