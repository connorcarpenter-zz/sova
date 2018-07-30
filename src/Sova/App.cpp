//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/InternalApp.h>
#include <Modules/Input/Input.h>
#include "App.h"

using namespace Sova;

namespace Sova {

    App::App(int width, int height, Ref<String> windowTitle, Ref<ShaderHandler> shaderHandler) {
        this->width = width;
        this->height = height;
        this->windowTitle = windowTitle;
        this->shaderHandler = shaderHandler;

        this->loader = New<Loader>();
        this->viewports = New<List<Viewport>>();
        this->websockets = New<List<Websocket>>();
        this->httpRequests = New<List<HttpRequest>>();
        this->finishedHttpRequests = New<List<HttpRequest>>();
    }

    void App::start() {
        InternalApp::initInternalApp(this);
        InternalApp::getInternalApp()->StartMainLoop();
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

    void App::drawCameras()
    {
        for (Ref<ListIterator<Viewport>> iterator = this->viewports->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Viewport> viewport = iterator->Get();
            viewport->drawCamera();
        }
    }

    void App::drawViewports()
    {
        for (Ref<ListIterator<Viewport>> iterator = this->viewports->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Viewport> viewport = iterator->Get();
            viewport->drawViewport();
        }
    }

    bool App::keyPressed(Sova::Key::Code key) {
        return InternalApp::getInternalApp()->keyPressed(key);
    }

    bool App::mouseButtonPressed(MouseButton::Code btn) {
        return InternalApp::getInternalApp()->mouseButtonPressed(btn);
    }

    int App::getMouseX() {
        return InternalApp::getInternalApp()->getMouseX();
    }

    int App::getMouseY() {
        return InternalApp::getInternalApp()->getMouseY();
    }

    Ref<Websocket> App::openWebsocket(Ref<String> address)
    {
        Ref<Websocket> newWebsocket = New<Websocket>(address);
        websockets->Add(newWebsocket);
        return newWebsocket;
    }

    void App::updateWebsockets()
    {
        if (this->websockets->Size() > 0) {
            for (Ref<ListIterator<Websocket>> iterator = this->websockets->GetIterator(); iterator->Valid(); iterator->Next()) {
                Ref<Websocket> websocket = iterator->Get();
                websocket->update();
            }
        }
    }

    Ref<HttpRequest> App::makeHttpRequest(Ref<String> method, Ref<String> address)
    {
        Ref<HttpRequest> newRequest = New<HttpRequest>(method, address);
        httpRequests->Add(newRequest);
        return newRequest;
    }

    void App::updateHttpRequests()
    {
        if (this->httpRequests->Size() > 0) {
            for (Ref<ListIterator<HttpRequest>> iterator = this->httpRequests->GetIterator(); iterator->Valid(); iterator->Next()) {
                Ref<HttpRequest> request = iterator->Get();
                request->update();
                if (request->isFinished())
                    finishedHttpRequests->Add(request);
            }
        }
        
        if (this->finishedHttpRequests->Size() > 0)
        {
            for (Ref<ListIterator<HttpRequest>> iterator = this->finishedHttpRequests->GetIterator(); iterator->Valid(); iterator->Next())
            {
                Ref<HttpRequest> request = iterator->Get();
                this->httpRequests->Remove(request);
            }
            this->finishedHttpRequests->Clear();
        }
    }

    void App::setGlobal(void *globalPtr) {
        this->globalObj = globalPtr;
    }

    void *App::getGlobal() {
        return this->globalObj;
    }
}