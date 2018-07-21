//
// Created by connor on 7/20/18.
//

#include "StringBuilder.h"

namespace Sova
{
    Sova::StringBuilder::StringBuilder() {
        this->strings = New<List<String>>();
    }

    StringBuilder::~StringBuilder()
    {

    }

    void StringBuilder::Append(Ref<String> str)
    {
        this->strings->Add(str);
        this->length += str->Length();
    }

    Ref<String> StringBuilder::ToString()
    {
        if (this->length == 0)
        {
            return New<String>("");
        }

        char* newChar = new char[this->length];
        int count = 0;
        for (Ref<ListIterator<String>> iterator = this->strings->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<String> substring = iterator->Get();
            for (int i=0; i<substring->Length();i++)
            {
                newChar[count] = substring->CharAt(i);
                count+=1;
            }
        }

        auto resultString = New<String>(newChar, this->length, true);

        //idk if we need to do this since the String will allocate?
        delete newChar;

        return resultString;
    }
}