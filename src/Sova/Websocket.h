#pragma once

//
// Created by connor on 7/18/18.
//

#include <Sova/References/Refable.h>
#include <functional>
#include <Sova/Common/String.h>
#include <Sova/References/Ref.h>

namespace Sova
{
    class WebSocketClient;
    class Websocket : public Refable
    {
    public:
        explicit Websocket(Ref<String> address);
        ~Websocket();
        void onOpen(std::function<void()> openFunction);
        void onError(std::function<void(Ref<String>)> errorFunction);
        void onMessage(std::function<void(Ref<String>)> messageFunction);
        void send(Ref<String> message);
        void close();
        void update();

        Ref<String> address = NullRef<String>();

    private:
        std::function<void()> openFunction = nullptr;
        std::function<void(Ref<String>)> errorFunction = nullptr;
        std::function<void(Ref<String>)> messageFunction = nullptr;

        WebSocketClient* webSocketClient = nullptr;
    };
}