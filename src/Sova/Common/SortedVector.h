#pragma once

//
// Created by connor on 10/22/18.
//

#include <Sova/References/Refable.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <functional>

namespace Sova
{
    template<class T>
    class VectorIterator : public Refable
    {
    public:

        explicit VectorIterator(std::vector<Ref<T>*>* vVector)
        {
            this->vVector = vVector;
            this->it = vVector->begin();
        }

        virtual const char* getClassName() { return "VectorIterator"; }

        Ref<T> Get()
        {
            return (**this->it);
        }

        void Next()
        {
            ++this->it;
        }

        bool Valid()
        {
            return this->it != vVector->end();
        }

    private:

        std::vector<Ref<T>*>* vVector = nullptr;
        typename std::vector<Ref<T>*>::iterator it;
    };

    template<class T>
    class SortedVector : public Refable
    {
    public:

        SortedVector()
        {
            this->vVector = new std::vector<Ref<T>*>();
        }

        ~SortedVector()
        {
            for(auto it = this->vVector->begin(); it != this->vVector->end(); ++it) {
                Ref<T>* item = *it;
                delete item;
            }
            delete this->vVector;
        }

        virtual const char *getClassName() { return "Vector"; }

        void Add(Ref<T> item)
        {
            auto nullPtr = NullPtr<T>();
            (*nullPtr) = item;
            this->vVector->push_back(nullPtr);
            this->markForResort();
        }

        void Remove(Ref<T> item)
        {
            typename std::vector<Ref<T>*>::iterator eraseIndex;

            eraseIndex = std::find_if(this->vVector->begin(), this->vVector->end(), [&](Ref<T>* refPtr){
                return (refPtr->obj == item.obj);
            });

            // And then erase if found
            if (eraseIndex != this->vVector->end())
            {
                delete *eraseIndex;

                this->vVector->erase(eraseIndex);
                this->markForResort();
            }
        }

        int Size()
        {
            return this->vVector->size();
        }

        Ref<VectorIterator<T>> GetIterator()
        {
            return New<VectorIterator<T>>(this->vVector);
        }

        void resortIfNeeded(std::function<bool(Ref<T>*,Ref<T>*)> sortFunction)
        {
            if(this->needToResort)
            {
                std::sort(this->vVector->begin(), this->vVector->end(), sortFunction);

                this->needToResort = false;
            }
        }

        void markForResort()
        {
            this->needToResort = true;
        }


    private:

        std::vector<Ref<T>*>* vVector = nullptr;
        bool needToResort = false;
    };
}