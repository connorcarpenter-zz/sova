//
// Created by connor on 7/31/18.
//

#include "Int.h"

#include <string>

namespace Sova
{
    Int::Int(int i)
    {
        this->value = i;
    }

    Ref<String> Int::ToString()
    {
        return New<String>(std::to_string(this->value).c_str());
    }
}
