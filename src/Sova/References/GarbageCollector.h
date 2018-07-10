#pragma once

//
// Created by Connor Carpenter on 4/16/18.
//

#include <set> //remove later!
#include <map> //remove later!

#include "Refable.h"

namespace Sova
{
    class GarbageCollector
    {
    public:

        static GarbageCollector* getGC(); // Initialize Garbage Collector, only for use from main Memory class

        // Perform garbage collection
        void collect(Refable* obj);

        // Add object to heap
        template<typename DerivedObj>
        void addToHeap(DerivedObj* obj) {

            static_assert(std::is_base_of<Refable, DerivedObj>::value, "DerivedObj should inherit from Refable");

            objHeap.insert(obj);
        }

        // Remove object from heap
        template<typename DerivedObj>
        void removeFromHeap(DerivedObj* obj) {

            static_assert(std::is_base_of<Refable, DerivedObj>::value, "DerivedObj should inherit from Refable");

            objHeap.erase(obj);
        }

        int getHeapObjectsNumber();

    private:

        static GarbageCollector* singleton;

        // Go through all objects in the heap, unmarking the live
        // objects and destroying the unreferenced ones.
        void sweep();

        // A collection of all active heap objects.
        std::set<Refable*> objHeap;

        GarbageCollector(); //to remain private. Singleton only got by createGC

        static void resetGC(); //to remain private, for testing only

    };

    static GarbageCollector* GC() { return Sova::GarbageCollector::getGC(); }
}