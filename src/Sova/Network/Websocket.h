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
    enum ReadyState { CONNECTING, OPEN, CLOSING, CLOSED };

    class WebsocketImpl;

    class Websocket : public Refable
    {
    public:
        explicit Websocket(Ref<String> address);
        virtual const char* getClassName() { return "Websocket"; }
        ~Websocket();
        void onOpen(std::function<void()> openFunction);
        void onError(std::function<void(Ref<String>)> errorFunction);
        void onMessage(std::function<void(Ref<String>)> messageFunction);
        void onClose(std::function<void(Ref<String>)> closeFunction);
        void send(Ref<String> message);
        void close();
        void update();
        ReadyState getReadyState();

        void receiveMessage(const char* message);
        void receiveError(const char* message);
        void receiveOpen();
        void receiveClose(const char* message);

        Ref<String> url = Null<String>();


    private:
        std::function<void()> openFunction = nullptr;
        std::function<void(Ref<String>)> errorFunction = nullptr;
        std::function<void(Ref<String>)> messageFunction = nullptr;
        std::function<void(Ref<String>)> closeFunction = nullptr;

        WebsocketImpl* webSocketClient = nullptr;
    };
}