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
        const char* AsCStr() const;
        virtual const char* getClassName() { return "String"; }
        int Length() const;
    private:
        int length;
        const char* strPtr;     // direct pointer to string data, necessary to see something in the debugger
    };

}