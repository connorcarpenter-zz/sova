#pragma once

//
// Created by connor on 10/22/18.
//

#include <Sova/References/Refable.h>
#include <assert.h>

namespace Sova
{
    template<class T>
    class Array : public Refable
    {
    public:

        Array(unsigned int capacity)
        {
            Reserve(capacity);
        }

        ~Array()
        {
            for (int i=0;i<vCapacity;i++)
            {
                if (vArray[i] != nullptr)
                    delete vArray[i];
            }

            delete [] vArray;
        }

        virtual const char *getClassName() { return "Array"; }

        Ref<T> Get(unsigned int index)
        {
            assert((index >= 0) && (index < vCapacity));
            if (vArray[index] == nullptr)
                return Null<T>();

            return (*vArray[index]);
        }

        void Set(unsigned int index, Ref<T> item)
        {
            assert((index >= 0) && (index < vCapacity));

            if (vArray[index] == nullptr)
                vArray[index] = NullPtr<T>();

            (*vArray[index]) = item;
        }

        void Reserve(unsigned int n)
        {
            Ref<T>** newArray = nullptr;

            newArray = new Ref<T>*[n];
            assert(newArray != nullptr); //if this throws, it means we weren't able to allocate the new space for the array

            for (int i=0;i<n;i++)
            {
                newArray[i] = nullptr;
            }

            assert(vArray == nullptr);

            vArray = newArray;
            vCapacity = n;
        }

    private:

        int vCapacity = 0;
        Ref<T>** vArray = nullptr;
    };
}