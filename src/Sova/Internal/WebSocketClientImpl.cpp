//
// Created by connor on 7/18/18.
//

#include "WebSocketClientImpl.h"

namespace Sova {
    WebSocketClientImpl::WebSocketClientImpl(Websocket *wrapperWebsocket, Ref <String> address) {
        this->wrapperWebsocket = wrapperWebsocket;

        this->webSocketClient.connect(address->AsCStr());

        this->webSocketClient.receive([&](Oryol::String msg) {
            this->wrapperWebsocket->receiveMessage(msg.AsCStr());
        });
    }

    void WebSocketClientImpl::update() {
        this->webSocketClient.update();
    }

    void WebSocketClientImpl::send(Oryol::String message) {
        this->webSocketClient.send(message);
    }
}