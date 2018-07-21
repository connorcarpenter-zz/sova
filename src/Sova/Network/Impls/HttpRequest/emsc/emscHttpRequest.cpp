//------------------------------------------------------------------------------
//  emscHttpRequest.cpp
//------------------------------------------------------------------------------
#include "Pre.h"
#include <emscripten/emscripten.h>

#include "emscHttpRequest.h"
#include "Sova/Network/Impls/HttpRequestImpl.h"

namespace Oryol {
namespace _priv {

    class EmscUserData : public RefCounted
    {
    public:
        IORead* reqPtr = nullptr;
        std::function<void(Ptr<IORead> req)> receiveFunction = nullptr;
    };

//------------------------------------------------------------------------------
bool
emscHttpRequest::doRequest(Sova::_priv::HttpRequestImpl* req) {
    this->startRequest(req);
    return true;
}

//------------------------------------------------------------------------------
void
emscHttpRequest::startRequest(Sova::_priv::HttpRequestImpl* req) {
    o_assert(req->getIoReq()->isValid() && !req->getIoReq()->Handled);

    // start the asynchronous XHR
    // NOTE: we can only load from our own HTTP server, so the host part of 
    // the URL is completely irrelevant...
    String urlPath = req->getIoReq()->Url.PathToEnd();

    emscripten_async_wget_data(urlPath.AsCStr(), (void*) req, emscHttpRequest::onLoaded, emscHttpRequest::onFailed);
}

//------------------------------------------------------------------------------
void
emscHttpRequest::onLoaded(void* userData, void* buffer, int size) {

    o_assert(0 != userData);
    o_assert(0 != buffer);
    o_assert(size > 0);

    Sova::_priv::HttpRequestImpl* req = (Sova::_priv::HttpRequestImpl*) userData;

    req->getIoReq()->Status = IOStatus::OK;
    req->getIoReq()->Data.Add((const uint8_t*)buffer, size);
    req->getIoReq()->Handled = true;

        req->onReceive(req);
}

//------------------------------------------------------------------------------
void
emscHttpRequest::onFailed(void* userData) {

    o_assert(0 != userData);

    Sova::_priv::HttpRequestImpl* req = (Sova::_priv::HttpRequestImpl*) userData;

    Log::Dbg("emscHttpRequest::onFailed(url=%s)\n", req->getIoReq()->Url.AsCStr());

    // hmm we don't know why it failed, so make something up, we should definitely
    // fix this somehow (looks like the wget2 functions also pass a HTTP status code)
    const IOStatus::Code ioStatus = IOStatus::NotFound;
        req->getIoReq()->Status = ioStatus;
        req->getIoReq()->Handled = true;

        req->onReceive(req);
}

}
}

