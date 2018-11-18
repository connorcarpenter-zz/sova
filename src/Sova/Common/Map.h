#pragma once

//
// Created by connor on 10/22/18.
//

#include <Sova/References/Refable.h>
#include <assert.h>
#include <map>

namespace Sova
{
    template<class T>
    class MapIterator : public Refable
    {
    public:

        explicit MapIterator(std::map<unsigned int, Ref<T>*>* vMap)
        {
            this->vMap = vMap;
            this->it = vMap->begin();
        }

        virtual const char* getClassName() { return "MapIterator"; }

        Ref<T> Get()
        {
            return *(this->it->second);
        }

        void Next()
        {
            ++this->it;
        }

        bool Valid()
        {
            return this->it != vMap->end();
        }

    private:

        std::map<unsigned int, Ref<T>*>* vMap = nullptr;
        typename std::map<unsigned int, Ref<T>*>::iterator it;
    };

    template<class T>
    class Map : public Refable
    {
    public:

        Map()
        {
            this->vMap = new std::map<unsigned int, Ref<T>*>();
        }

        ~Map()
        {
            for (auto kvPair : *this->vMap)
            {
                delete kvPair.second;
            }
            delete vMap;

//            for (int i=0;i<vCapacity;i++)
//            {
//                if (vMap[i] != nullptr)
//                    delete vMap[i];
//            }
//
//            delete [] vMap;
        }

        virtual const char *getClassName() { return "Map"; }

        Ref<T> At(unsigned int index)
        {
            if (this->vMap->count(index) == 0)
                return Null<T>();

            return (*this->vMap->at(index));
        }

        void Insert(unsigned int index, Ref<T> item)
        {
            auto nullPtr = NullPtr<T>();
            (*nullPtr) = item;
            this->vMap->insert(std::pair<unsigned int, Ref<T>*>(index, nullPtr));
        }

        void Erase(unsigned int index){

            if (this->vMap->count(index) == 0) return;

            delete this->vMap->at(index);

            this->vMap->erase(index);
        }

        Ref<MapIterator<T>> GetIterator()
        {
            return New<MapIterator<T>>(this->vMap);
        }


    private:

        std::map<unsigned int, Ref<T>*>* vMap = nullptr;
    };
}