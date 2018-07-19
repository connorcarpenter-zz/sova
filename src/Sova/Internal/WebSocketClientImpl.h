#pragma once

//
// Created by connor on 7/18/18.
//

#include <Sova/Common/String.h>
#include <Sova/References/Ref.h>
#include "WebSocketClient/WebSocketClient.h"
#include "Sova/Websocket.h"

namespace Sova
{
    class WebSocketClientImpl
    {
    public:
        WebSocketClientImpl(Sova::Websocket* wrapperWebsocket, Ref<String> address);
        void update();
        void send(Oryol::String message);
    private:
        Oryol::WebSocketClient webSocketClient;
        Sova::Websocket* wrapperWebsocket = nullptr;
    };
}