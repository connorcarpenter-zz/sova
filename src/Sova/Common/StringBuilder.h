#pragma once

//
// Created by connor on 7/20/18.
//
#include <Sova/References/Ref.h>
#include "String.h"
#include "List.h"

namespace Sova
{
    class StringBuilder : public Refable
    {
    public:
        StringBuilder();
        ~StringBuilder();
        void Append(Ref<String> str);
        Ref<String> ToString();
    private:
        Ref<List<String>> strings = Null<List<String>>();
        int length = 0;
    };
}