//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/OryolApp.h>

using namespace Oryol;

namespace Sova {

    App::App(int width, int height, const char *windowTitle, Sova::ShaderHandler* shaderHandler) {
        this->width = width;
        this->height = height;
        this->windowTitle = windowTitle;
        this->shaderHandler = shaderHandler;
    }

    void App::start() {
        OryolApp* oryolApp = new OryolApp(this);
        oryolApp->StartMainLoop();
        delete oryolApp;
    };

    Loader& App::load(const Array<String>& resources) {

        return loader;
    };

    void App::onUpdate(std::function<void()> updateFunction){

    }

    void App::addViewport(const Viewport& viewport) {

    }

    App::App() {};
}