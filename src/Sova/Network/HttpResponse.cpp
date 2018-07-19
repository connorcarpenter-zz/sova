//
// Created by connor on 7/19/18.
//

#include "HttpResponse.h"

namespace Sova
{
    HttpResponse::HttpResponse(int status, Ref<String> responseText) {
        this->status = status;
        this->responseText = responseText;
    }
}