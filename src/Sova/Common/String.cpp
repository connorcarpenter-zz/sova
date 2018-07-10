//
// Created by connor on 7/9/18.
//

#include "String.h"

namespace Sova
{
    String::String(const char* cp)
    {
        int i = 0;
        const char* tp = cp;
        while(*tp++)
        {
            i++;
        }

        buffer = new char[i];
        int j = 0;

        for(j;*tp;tp++,j++)
        {
            buffer[j] = *tp;
        }
        size = j;
    }

    inline const char* String::AsCStr() const
    {
        return buffer;
    }

    String::~String() {
        delete[] buffer;
    }

    int String::length() const {
        return size;
    }
}