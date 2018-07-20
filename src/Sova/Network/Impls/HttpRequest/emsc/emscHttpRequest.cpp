//------------------------------------------------------------------------------
//  emscHttpRequest.cpp
//------------------------------------------------------------------------------
#include "Pre.h"
#include "emscHttpRequest.h"
#include <emscripten/emscripten.h>

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
bool
emscHttpRequest::doRequest(const Ptr<IORead>& req) {
    this->startRequest(req);
    return true;
}

//------------------------------------------------------------------------------
void
emscHttpRequest::startRequest(const Ptr<IORead>& req) {
    o_assert(req.isValid() && !req->Handled);

    // bump the requests refcount and get a raw pointer
    IORead* reqPtr = req.get();
    reqPtr->addRef();

    // start the asynchronous XHR
    // NOTE: we can only load from our own HTTP server, so the host part of 
    // the URL is completely irrelevant...
    String urlPath = req->Url.PathToEnd();
    emscripten_async_wget_data(urlPath.AsCStr(), (void*) reqPtr, emscHttpRequest::onLoaded, emscHttpRequest::onFailed);
}

//------------------------------------------------------------------------------
void
emscHttpRequest::onLoaded(void* userData, void* buffer, int size) {
    o_assert(0 != userData);
    o_assert(0 != buffer);
    o_assert(size > 0);

    Ptr<IORead> req((IORead*)userData);
    req->release();
    req->Status = IOStatus::OK;
    req->Data.Add((const uint8_t*)buffer, size);
    req->Handled = true;
}

//------------------------------------------------------------------------------
void
emscHttpRequest::onFailed(void* userData) {
    o_assert(0 != userData);

    // user data is a HTTPRequest ptr, put it back into a smart pointer
    Ptr<IORead> req((IORead*)userData);
    req->release();
    Log::Dbg("emscHttpRequest::onFailed(url=%s)\n", req->Url.AsCStr());

    // hmm we don't know why it failed, so make something up, we should definitely
    // fix this somehow (looks like the wget2 functions also pass a HTTP status code)
    const IOStatus::Code ioStatus = IOStatus::NotFound;
    req->Status = ioStatus;
    req->Handled = true;
}

}
}

