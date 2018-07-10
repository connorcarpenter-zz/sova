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
        explicit String(const char* cstr);
        ~String();
        const char* AsCStr() const;
        int length() const;
    private:
        int size;
        char * buffer;
    };

}