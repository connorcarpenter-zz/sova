//
// Created by connor on 7/19/18.
//

#include "HttpRequest.h"
#include "Sova/Network/Impls/HttpRequestImpl.h"

namespace Sova
{

    HttpRequest::HttpRequest(Ref<String> method, Ref<String> url)
    {
        this->method = method;
        this->url = url;

        this->headerKeys = New<List<String>>();
        this->headerValues = New<List<String>>();

        this->impl = new Sova::_priv::HttpRequestImpl(this);
    }

    HttpRequest::~HttpRequest()
    {
        delete this->impl;
    }

    void HttpRequest::setRequestHeader(Ref<String> headerName, Ref<String> headerValue)
    {
        this->headerKeys->Add(headerName);
        this->headerValues->Add(headerValue);
    }

    void HttpRequest::onResponse(std::function<void(Ref<HttpResponse>)> responseFunction)
    {
        this->responseFunction = responseFunction;
    }

    void HttpRequest::send()
    {
        this->impl->send();
    }

    void HttpRequest::receiveResponse(int status, char* data, int dataSize)
    {
        Ref<String> responseText = New<String>(data);
        Ref<HttpResponse> response = New<HttpResponse>(status, responseText);
        this->responseFunction(response);
    }
}