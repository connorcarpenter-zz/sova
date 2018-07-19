//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/OryolApp.h>
#include <Modules/Input/Input.h>
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
        this->websockets = NewRef<List<Websocket>>();
    }

    void App::start() {
        OryolApp::initOryolApp(this);
        OryolApp::getOryolApp()->StartMainLoop();
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

    bool App::keyPressed(Sova::Key::Code key) {
        return OryolApp::getOryolApp()->keyPressed(key);
    }

    bool App::mouseButtonPressed(MouseButton::Code btn) {
        return OryolApp::getOryolApp()->mouseButtonPressed(btn);
    }

    int App::getMouseX() {
        return OryolApp::getOryolApp()->getMouseX();
    }

    int App::getMouseY() {
        return OryolApp::getOryolApp()->getMouseY();
    }

    Ref<Websocket> App::openWebsocket(Ref<String> address)
    {
        auto newWebsocket = NewRef<Websocket>(address);
        websockets->Add(newWebsocket);
        return newWebsocket;
    }

    void App::updateWebsockets()
    {
        for (Ref<ListIterator<Websocket>> iterator = this->websockets->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Websocket> websocket = iterator->Get();
            websocket->update();
        }
    }
}