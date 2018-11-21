//
// Created by connor on 7/18/18.
//

#include "WebsocketImpl.h"

namespace Sova
{
    WebsocketImpl::WebsocketImpl(Websocket* wrapperWebsocket, Ref <String> address)
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

    void WebsocketImpl::update()
    {
        this->webSocketClient.update();
    }

    void WebsocketImpl::send(Oryol::String message)
    {
        this->webSocketClient.send(message);
    }

    void WebsocketImpl::close()
    {
        this->webSocketClient.close();
    }

    int WebsocketImpl::getReadyState() {
        return this->webSocketClient.getReadyState();
    }

    void WebsocketImpl::setEscapeCharacter(char c) {
        this->webSocketClient.setEscapeCharacter(c);
    }
}