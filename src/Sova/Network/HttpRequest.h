#pragma once

//
// Created by connor on 7/19/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include <Sova/Common/String.h>
#include <functional>
#include "HttpResponse.h"

namespace Sova
{
    class HttpRequest : public Refable
    {
    public:
        virtual const char* getClassName() { return "HttpRequest"; }
        HttpRequest(Ref<String> method, Ref<String> url);
        void setRequestHeader(Ref<String> headerName, Ref<String> headerValue);
        void onResponse(std::function<void(Ref<HttpResponse>)> responseFunction);
        void send();
    };
}
