//
// Created by connor on 7/9/18.
//

#include "String.h"

namespace Sova
{
    String::String(const char* str)
    {
        this->strPtr = str;
    }

    const char* String::AsCStr() const
    {
        return this->strPtr;
    }
}