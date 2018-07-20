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
            Oryol::Ptr<Oryol::IORead> ioReq = Oryol::IORead::Create();
            ioReq->Url = Oryol::URL(this->parentRequest->url->AsCStr());
            this->doRequest(ioReq);

            this->parentRequest->receiveResponse(ioReq->Status, (char*) ioReq->Data.Data(), ioReq->Data.Size());
        }
    }
}