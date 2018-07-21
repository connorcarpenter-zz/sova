#pragma once

//
// Created by connor on 7/19/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include <Sova/Common/String.h>
#include <functional>
#include <Sova/Common/List.h>
#include "HttpResponse.h"

namespace Sova {
    namespace _priv {
        class HttpRequestImpl;
    }
}

namespace Sova
{
    class HttpRequest : public Refable
    {
    public:
        HttpRequest(Ref<String> method, Ref<String> url);
        ~HttpRequest();
        virtual const char* getClassName() { return "HttpRequest"; }
        void setRequestHeader(Ref<String> headerName, Ref<String> headerValue);
        void onResponse(std::function<void(Ref<HttpResponse>)> responseFunction);
        void send();
        void update();
        bool isFinished();

        void receiveResponse(int status, const char* data, int dataSize);

        Ref<List<String>> headerKeys = Null<List<String>>();
        Ref<List<String>> headerValues = Null<List<String>>();
        Ref<String> method = Null<String>();
        Ref<String> url = Null<String>();

    private:
        Sova::_priv::HttpRequestImpl* impl;

        std::function<void(Ref<HttpResponse>)> responseFunction = nullptr;

        bool responseSent = false;
        Ref<HttpResponse> response = Null<HttpResponse>();
    };
}
