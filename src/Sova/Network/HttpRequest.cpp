//
// Created by connor on 7/19/18.
//

#include "HttpRequest.h"

namespace Sova
{

    HttpRequest::HttpRequest(Ref<String> method, Ref<String> url) {

    }

    void HttpRequest::setRequestHeader(Ref<String> headerName, Ref<String> headerValue) {

    }

    void HttpRequest::onResponse(std::function<void(Ref<HttpResponse>)> responseFunction) {

    }

    void HttpRequest::send() {

    }
}