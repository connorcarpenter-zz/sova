
//
// Created by Connor Carpenter on 4/16/18.
//

#include <vector>
//#include <iostream>
#include "GarbageCollector.h"
#include "IRef.h"

using namespace std;

namespace Sova {

    GarbageCollector* GarbageCollector::singleton = nullptr;

    GarbageCollector* GarbageCollector::getGC() {
        if (singleton == nullptr)
            singleton = new GarbageCollector();
        return singleton;
    }

    void GarbageCollector::resetGC() {
        if (singleton != nullptr)
            delete singleton;
        singleton = nullptr;
        getGC();
    }

    void GarbageCollector::collect(Refable* root) {

        //cout << "GC: " << objHeap.size() << " objects in heap" << endl;

        root->Mark();

        sweep();

        root->marked = false;
    }

    void GarbageCollector::sweep() {

        //cout << "GC: start sweep" << endl;

        unsigned int live = 0;
        unsigned int dead = 0;
        unsigned int total = 0;

        vector<std::set<Refable*>::iterator> erase;
        for (auto it = objHeap.begin();
             it != objHeap.end();
             ++it) {
            Refable* obj = (*it);
            total++;// don't know if I need to move this down a line :/
            if (obj != nullptr) {
                if (obj->marked) {
                    obj->marked = false;
                    ++live;
                } else {
                    erase.push_back(it);
                }
            }
        }

        dead = erase.size();
        for (auto it = erase.begin();
             it != erase.end();
             ++it) {
            Refable* obj = **it;
            objHeap.erase(obj);
        }

        //cout << "GC: " << live << " objects live after sweep" << endl;
        //cout << "GC: " << dead << " objects dead after sweep" << endl;
    }

    int GarbageCollector::getHeapObjectsNumber() {
        return (int) objHeap.size();
    }


}