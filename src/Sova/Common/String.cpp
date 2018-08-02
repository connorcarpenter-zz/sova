//
// Created by connor on 7/9/18.
//

#include <cstring>
#include <Modules/Core/Assertion.h>
#include <Sova/References/Ref.h>
#include <iostream>
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
        this->charArray[this->length] = '\0';
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

    void String::PrintChars()
    {
        for (int i = 0; i<this->length;i++)
        {
            char c = CharAt(i);
            if (c == '\n'){
                std::cout << "'newline'";
            } else if (c == '\r'){
                std::cout << "'backr'";
            } else {
                std::cout << "'" << c << "'";
            }
        }
    }

    int String::Length() const {
        return this->length;
    }

    const char String::CharAt(int index) const {
        o_assert(index < this->length);
        if (this->useCharArray)
            return this->charArray[index];
        return strPtr[index];
    }

    Ref<List<String>> String::Split(char separator)
    {
        Ref<List<String>> stringList = New<List<String>>();

        int start = 0;
        int i = 0;
        while(i <= this->length)
        {
            bool foundSeparator = false;
            if (i==this->length) foundSeparator = true;
            if (!foundSeparator)
                foundSeparator = (CharAt(i) == separator);
            if (foundSeparator)
            {
                //found a separator! lets make a new string
                int newLength = i-start;

                if (newLength == 0)
                {
                    //add new string here and bypass string allocation later
                    stringList->Add(New<String>(""));
                }
                else
                {
                    char* newCharArray = new char[newLength];
                    for (int j = 0; j < newLength; j++)
                    {
                        newCharArray[j] = CharAt(start+j);
                    }
                    auto newString = New<String>(newCharArray, newLength, true);
                    stringList->Add(newString);

                    delete newCharArray;//not sure if this is necessary, or will break things, just checking
                    start = i+1;
                }
            }

            if (i==this->length) break;
            i += 1;
        }

        //We want to return a null list instead of an empty list... I think
        if (stringList->Size() == 0)
            return Null<List<String>>();

        return stringList;
    }

    const bool String::Equals(const char *cstr) const
    {
        for (int i = 0; i<this->length; i++)
        {
//            std::cout << "Equals(): '" << CharAt(i) << "'=='"<< cstr[i] << "'?" << std::endl;
            if (CharAt(i) != cstr[i]) {
//                std::cout << "Equals() return false" << std::endl;
                return false;
            }
        }

//        std::cout << "Equals() return true" << std::endl;
        return true;
    }

    const bool String::Equals(Ref<String> other) const {
        return Equals(other->AsCStr());
    }

    const bool String::StartsWith(const char *cstr) const
    {
        int cstrlength = (int) strlen(cstr);
        for (int i = 0; i<cstrlength; i++)
        {
            if(CharAt(i) != cstr[i])
                return false;
        }

        return true;
    }

    const bool String::EndsWith(const char *cstr) const
    {
        int cstrlength = (int) strlen(cstr);
        for (int i = 0; i<cstrlength; i++)
        {
            if(CharAt(this->length-1-i) != cstr[cstrlength-1-i])
                return false;
        }

        return true;
    }

    Ref<String> String::TrimEnd(const char *cstr)
    {
        if (EndsWith(cstr)){
            int cstrlength = (int) strlen(cstr);
            return Substring(0, this->length - cstrlength);
        }
        else
        {
            return ThisRef<String>();
        }
    }

    Ref<String> String::TrimStart(const char *cstr)
    {
        if (StartsWith(cstr)){
            int cstrlength = (int) strlen(cstr);
            return Substring(cstrlength, this->length);
        }
        else
        {
            return ThisRef<String>();
        }
    }

    Ref<String> String::Substring(int start, int end)
    {
        int newLength = end - start;
        char* newCharArray = new char[newLength];
        for (int i = 0; i < newLength; i++)
        {
            newCharArray[i] = CharAt(start+i);
        }
        Ref<String> newString = New<String>(newCharArray, newLength, true);
        delete newCharArray;
        return newString;
    }


}