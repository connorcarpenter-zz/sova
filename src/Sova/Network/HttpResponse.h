#pragma once

//
// Created by connor on 7/19/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include <Sova/Common/String.h>

namespace Sova
{
    class HttpResponse : public Refable
    {
    public:
        virtual const char* getClassName() { return "HttpResponse"; }
        HttpResponse(int status, Ref<String> responseText);
        int status;
        Ref<String> responseText = Null<String>();
    private:
    };
}
