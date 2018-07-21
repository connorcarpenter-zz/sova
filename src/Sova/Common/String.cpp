//
// Created by connor on 7/9/18.
//

#include <cstring>
#include <Modules/Core/Assertion.h>
#include "String.h"

namespace Sova
{
    String::String(const char* str)
    {
        this->length = (int) strlen(str);
        this->strPtr = str;
        this->useCharArray = false;
    }

    String::String(const char* str, bool createNew)
    {
        o_assert(createNew == true);
        this->length = (int) strlen(str);
        this->charArray = new char[this->length+1];
        for (int i = 0; i<this->length; i++)
        {
            this->charArray[i] = str[i];
        }
        this->charArray[this->length] = '\n';

        this->useCharArray = true;
    }

    String::String(const char* str, int length, bool createNew)
    {
        o_assert(createNew == true);
        this->length = length;
        this->charArray = new char[this->length+1];
        for (int i = 0; i<this->length; i++)
        {
            this->charArray[i] = str[i];
        }
        this->charArray[this->length] = '\n';
        this->useCharArray = true;
    }

    String::~String()
    {
        if(this->useCharArray)
            delete this->charArray;
    }

    const char* String::AsCStr() const
    {
        if (this->useCharArray)
            return this->charArray;
        return strPtr;
    }

    int String::Length() const {
        return length;
    }
}