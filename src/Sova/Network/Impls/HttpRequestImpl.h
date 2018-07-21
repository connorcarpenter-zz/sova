#pragma once

//
// Created by connor on 7/19/18.
//

#include <Sova/Network/HttpRequest.h>

#if ORYOL_USE_LIBCURL
#include "Sova/Network/Impls/HttpRequest/curl/curlHttpRequest.h"
namespace Sova
{
    namespace _priv
    {
        class HttpRequestImpl : public Oryol::_priv::curlHttpRequest
#elif ORYOL_OSX
//implement later //remember to edit CMakeLists.txt!
#elif ORYOL_WINDOWS
//implement later //remember to edit CMakeLists.txt!
#elif ORYOL_EMSCRIPTEN
#include "Sova/Network/Impls/HttpRequest/emsc/emscHttpRequest.h"
namespace Sova
{
    namespace _priv
    {
        class HttpRequestImpl : public Oryol::_priv::emscHttpRequest
#else
//implement later
#endif

        {
        public:
            explicit HttpRequestImpl(Sova::HttpRequest* parentRequest);

            void send();

            Oryol::Ptr<Oryol::IORead>& getIoReq();
            
            void onReceive(HttpRequestImpl* req);

        private:
            Sova::HttpRequest* parentRequest = nullptr;
            Oryol::Ptr<Oryol::IORead> ioReq;
            std::function<void(Sova::_priv::HttpRequestImpl* req)> receiveFunction;
        };
    }
}