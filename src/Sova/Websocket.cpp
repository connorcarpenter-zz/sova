//
// Created by connor on 7/18/18.
//

#include "Websocket.h"
#include "Sova/Internal/WebSocketClientImpl.h"

namespace Sova
{
    Sova::Websocket::Websocket(Ref<String> address)
    {
        this->address = address;
        this->webSocketClient = new Sova::WebSocketClientImpl(this, address);
    }

    Websocket::~Websocket()
    {
        delete this->webSocketClient;
    }

    void Websocket::onOpen(std::function<void()> openFunction) {
        this->openFunction = openFunction;
    }

    void Websocket::onError(std::function<void(Ref<String>)> errorFunction) {
        this->errorFunction = errorFunction;
    }

    void Websocket::onMessage(std::function<void(Ref<String>)> messageFunction) {
        this->messageFunction = messageFunction;
    }

    void Websocket::send(Ref<String> message) {
        this->webSocketClient->send(Oryol::String(message->AsCStr()));
    }

    void Websocket::close() {

    }

    void Websocket::update() {
        this->webSocketClient->update();
    }

    void Websocket::receiveMessage(const char* message) {
        this->messageFunction(NewRef<String>(message));
    }
}