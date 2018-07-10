#pragma once

//
// Created by connor on 7/9/18.
//

#include <Sova/References/Refable.h>

using namespace Sova;

namespace Sova
{
    class String : public Refable
    {
    public:
        String(const char* cstr);
        const char* AsCStr() const;
    };

}