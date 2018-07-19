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
#include "Input.h"
#include "Websocket.h"

using namespace Sova;

namespace Sova {

    class App : public Refable
    {
    public:
        App(int width, int height, Ref<String> windowTitle, Ref<ShaderHandler> shaderHandler);
        virtual const char* getClassName() { return "App"; }

        Ref<Loader> load(Ref<List<String>> resources);
        void start();
        void onUpdate(std::function<void()> updateFunction);
        void addViewport(Ref<Viewport> viewport);
        void draw();

        std::function<void()> updateFunction = nullptr;
        
        //Input
        bool keyPressed(Key::Code key);
        bool mouseButtonPressed(MouseButton::Code btn);
        int getMouseX();
        int getMouseY();

        //Window
        int width;
        int height;
        Ref<String> windowTitle = Null<String>();
        Ref<ShaderHandler> shaderHandler = Null<ShaderHandler>();
        
        //Resource loading
        Ref<Loader> loader = Null<Loader>();

        //Sockets
        Ref<Websocket> openWebsocket(Ref<String> address);

        void updateWebsockets();

    private:
        Ref<List<Viewport>> viewports = Null<List<Viewport>>();
        Ref<List<Websocket>> websockets = Null<List<Websocket>>();
    };

}