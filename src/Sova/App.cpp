//
// Created by connor on 7/8/18.
//

#include "App.h"

namespace Sova {

    App::App(int width, int height, const char* windowTitle) {
        this->width = width;
        this->height = height;
        this->windowTitle = windowTitle;
        this->loader = New<Loader>();
    }

    void App::start() {
        OryolApp* oryolApp = new OryolApp(this);
        oryolApp->StartMainLoop();
        delete oryolApp;
    };

    Loader& App::load(std::initializer_list l) {

        return loader;
    };

    void App::onUpdate(std::function<void()> updateFunction){

    }

    void App::addViewport(const Viewport& viewport) {

    };
}