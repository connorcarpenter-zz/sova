//
// Created by connor on 7/19/18.
//

#include "HttpRequestImpl.h"

namespace Sova
{
    namespace _priv
    {
        HttpRequestImpl::HttpRequestImpl(Sova::HttpRequest* parentRequest)
        {
            this->parentRequest = parentRequest;
        }

        void HttpRequestImpl::send()
        {
            this->ioReq = Oryol::IORead::Create();
            this->ioReq->Url = Oryol::URL(this->parentRequest->url->AsCStr());
            this->receiveFunction = [&](HttpRequestImpl* req)
            {
                this->parentRequest->receiveResponse(req->getIoReq()->Status, (char*) req->getIoReq()->Data.Data(), req->getIoReq()->Data.Size());
            };
            this->doRequest(this);
        }

        Oryol::Ptr<Oryol::IORead>& HttpRequestImpl::getIoReq()
        {
            return this->ioReq;
        }

        void HttpRequestImpl::onReceive(HttpRequestImpl *req)
        {
            this->receiveFunction(req);
        }
    }
}