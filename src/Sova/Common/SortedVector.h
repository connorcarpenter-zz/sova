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
    class SortedVector : public Refable
    {
    public:

        SortedVector()
        {
            this->vVector = new std::vector<T*>();
        }

        ~SortedVector()
        {
            for(auto it = this->vVector->begin(); it != this->vVector->end(); ++it) {
                T* item = *it;
                this->releaseItem(item);
            }
            delete this->vVector;
        }

        virtual const char *getClassName() { return "Vector"; }

        void releaseItem(T *item) {
            Refable* refable = (Refable*) item;
            if (refable->Release() == 0){
                Sova::GarbageCollector::getGC()->removeFromHeap(refable);
                delete item;
            }
        }

        void Mark() override {
            if (!marked)
            {
                marked = true;
                for(auto it = this->vVector->begin(); it != this->vVector->end(); ++it) {
                    T* item = *it;
                    Refable* obj = (Refable*) item;
                    obj->Mark();
                }
            }
        }

        void Add(Ref<T> item)
        {
            T* myT = item.obj;
            Sova::Refable* refable = (Sova::Refable*) myT;
            refable->Hold();
            this->vVector->push_back(myT);
            this->markForResort();
        }

        void Remove(Ref<T> item)
        {
            typename std::vector<T*>::iterator eraseIndex;

            eraseIndex = std::find_if(this->vVector->begin(), this->vVector->end(), [&](T* vItem){
                return (vItem == item.obj);
            });

            // And then erase if found
            if (eraseIndex != this->vVector->end())
            {
                releaseItem(*eraseIndex);

                this->vVector->erase(eraseIndex);
                this->markForResort();
            }
        }

        int Size()
        {
            return this->vVector->size();
        }

        void resortIfNeeded(std::function<bool(T*,T*)> sortFunction)
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

        Ref<T> At(int index)
        {
            T* item = this->vVector->at(index);
            auto newRef = Null<T>();
            newRef.set(item);
            return newRef;
        }

    private:

        std::vector<T*>* vVector = nullptr;
        bool needToResort = false;
    };
}