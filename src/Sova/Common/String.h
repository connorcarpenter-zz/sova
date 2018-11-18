#pragma once

//
// Created by connor on 7/9/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include "List.h"

using namespace Sova;

namespace Sova
{
    class String : public Refable
    {
    public:
        explicit String(const char* cstr);
        String(const char *str, int length, bool createNew);
        String(const char *str, bool createNew);
        String(char str);
        ~String();

        const char* AsCStr() const;
        void PrintChars();
        virtual const char* getClassName() { return "String"; }
        int Length() const;
        const char CharAt(int index) const;
        Ref<List<String>> Split(char separator);
        const bool Equals(const char* cstr) const;
        const bool Equals(Ref<String> other) const;
        const bool StartsWith(const char* cstr) const;
        const bool EndsWith(const char* cstr) const;
        Ref<String> TrimEnd(const char* cstr);
        Ref<String> TrimStart(const char* cstr);
        Ref<String> Substring(int startIndex, int endIndex);

        static Ref<String> getStringFromNumber(int number);

    private:
        int length;
        const char* strPtr = nullptr;     // direct pointer to string data, necessary to see something in the debugger
        char* charArray = nullptr;
        bool useCharArray = false;



        static int getDigits(int number);
    };

}