//
// Created by connor on 7/18/18.
//

#include "WebSocketClientImpl.h"

namespace Sova
{
    WebSocketClientImpl::WebSocketClientImpl(Websocket* wrapperWebsocket, Ref <String> address)
    {
        this->wrapperWebsocket = wrapperWebsocket;

        this->webSocketClient.onMessage([&](Oryol::String msg) {
            this->wrapperWebsocket->receiveMessage(msg.AsCStr());
        });

        this->webSocketClient.onError([&](Oryol::String msg) {
            this->wrapperWebsocket->receiveError(msg.AsCStr());
        });

        this->webSocketClient.onOpen([&]() {
            this->wrapperWebsocket->receiveOpen();
        });

        this->webSocketClient.onClose([&](Oryol::String msg) {
            this->wrapperWebsocket->receiveClose(msg.AsCStr());
        });

        this->webSocketClient.connect(address->AsCStr());
    }

    void WebSocketClientImpl::update()
    {
        this->webSocketClient.update();
    }

    void WebSocketClientImpl::send(Oryol::String message)
    {
        this->webSocketClient.send(message);
    }

    void WebSocketClientImpl::close()
    {
        this->webSocketClient.close();
    }

    int WebSocketClientImpl::getReadyState() {
        return this->webSocketClient.getReadyState();
    }
}