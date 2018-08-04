//
// Created by connor on 7/31/18.
//

#include "Int.h"

#include <string>
#include <Sova/References/Ref.h>
#include <cstring>

namespace Sova
{
    Int::Int(int i)
    {
        this->value = i;
    }

    Ref<Sova::String> Int::ToString()
    {
        const char* cstr = std::to_string(this->value).c_str();
        Ref<Sova::String> newStr = New<String>(cstr, strlen(cstr), true);
        return newStr;
    }

    int Int::getInt() {
        return value;
    }
}
