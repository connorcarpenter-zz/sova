//
// Created by connor on 7/9/18.
//

#include <cstring>
#include "String.h"

namespace Sova
{
    String::String(const char* str)
    {
        this->strPtr = str;
        this->length = (int) strlen(this->strPtr);
    }

    const char* String::AsCStr() const
    {
        return this->strPtr;
    }

    int String::Length() const {
        return length;
    }
}