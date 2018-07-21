#pragma once

//
// Created by connor on 7/19/18.
//

#include "Sova/Network/Impls/HttpRequest/baseHttpRequest.h"

namespace Oryol {
namespace _priv {

class curlHttpRequest : public baseHttpRequest {
public:
    /// constructor
    curlHttpRequest();
    /// destructor
    ~curlHttpRequest();
    /// process one request
    bool doRequest(Sova::_priv::HttpRequestImpl* req);

    /// setup curl session
    void setupCurlSession();
    /// discard the curl session
    void discardCurlSession();
    /// process one request (internal)
    void doRequestInternal(Sova::_priv::HttpRequestImpl* httpReq);
    /// curl write-data callback
    static int curlWriteDataCallback(char* ptr, int size, int nmemb, void* userData);
    /// curl header-data callback
    static int curlHeaderCallback(char* ptr, int size, int nmenb, void* userData);

    void* curlSession;
    char* curlError;
};

}
}
