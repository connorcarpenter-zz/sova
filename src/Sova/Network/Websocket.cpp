//
// Created by connor on 7/18/18.
//

#include "Websocket.h"
#include "Sova/Network/Impls/WebsocketImpl.h"

namespace Sova
{
    Sova::Websocket::Websocket(Ref<String> address)
    {
        this->url = address;
        this->webSocketClient = new Sova::WebsocketImpl(this, address);
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

    void Websocket::onClose(std::function<void(Ref<String>)> closeFunction) {
        this->closeFunction = closeFunction;
    }

    void Websocket::send(Ref<String> message) {
        this->webSocketClient->send(Oryol::String(message->AsCStr()));
    }

    void Websocket::close() {
        this->webSocketClient->close();
    }

    void Websocket::update() {
        this->webSocketClient->update();
    }

    void Websocket::receiveMessage(const char* message) {
        if (this->messageFunction != nullptr)
            this->messageFunction(New<String>(message));
    }

    void Websocket::receiveError(const char* message) {
        if (this->errorFunction != nullptr)
            this->errorFunction(New<String>(message));
    }

    void Websocket::receiveOpen() {
        if (this->openFunction != nullptr)
            this->openFunction();
    }

    void Websocket::receiveClose(const char* message) {
        if (this->closeFunction != nullptr)
            this->closeFunction(New<String>(message));
    }

    ReadyState Websocket::getReadyState() {
        return static_cast<ReadyState>(this->webSocketClient->getReadyState());
    }

    void Websocket::setEscapeCharacter(char c) {
        this->webSocketClient->setEscapeCharacter(c);
    }
}