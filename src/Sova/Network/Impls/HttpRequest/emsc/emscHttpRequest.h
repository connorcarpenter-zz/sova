#pragma once

//
// Created by connor on 7/19/18.
//

#include "Sova/Network/Impls/HttpRequest/baseHttpRequest.h"

namespace Oryol {
namespace _priv {

class emscHttpRequest : public baseHttpRequest {
public:
    /// process one request
    bool doRequest(Sova::_priv::HttpRequestImpl* req);

    /// start the next, called from doWork
    void startRequest(Sova::_priv::HttpRequestImpl* req);
    /// success callback
    static void onLoaded(void* userData, void* buffer, int size);
    /// failure callback
    static void onFailed(void* userData);
};

}
}
