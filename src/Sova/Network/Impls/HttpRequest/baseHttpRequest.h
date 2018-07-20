#pragma once

//
// Created by connor on 7/19/18.
//

#include "IO/private/ioRequests.h"

namespace Oryol
{
    namespace _priv
    {
        class baseHttpRequest
        {
        public:
            /// process one HTTPRequest
            bool doRequest(const Ptr<IORead>& ioRequest) {}
        };
    }
}
