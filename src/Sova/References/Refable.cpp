//
// Created by connor on 7/9/18.
//

#include "Refable.h"
#include "IRef.h"

namespace Sova
{
    void Refable::Mark()
    {
        if (!marked)
        {
            //int size = refs.size();
            //int count = 0;
            //cout << "GC: marking object " << this->getClassName() << ", # of refs: " << size << endl;

            marked = true;
            for (auto it = refs.begin();
                 it != refs.end();
                 ++it) {

                //count += 1;
                //cout << "GC: inside iterator of " << this->getClassName() << ". Ref # " << count << " of " << size << "" << endl;

                IRef* ref = (*it);

                //cout << "GC: de-reffed good" << endl;

                if (ref != nullptr) {
                    //cout << "GC: before getobj: " << ref << endl;
                    Refable *obj = ref->getObj();
                    //cout << "GC: after getobj" << endl;

                    if (obj != nullptr) {
                        //cout << "GC: inside iterator marking child: " << obj->getClassName() << "" << endl;
                        obj->Mark();
                    }
                }
            }
        }
        else
        {
            //cout << "GC: already marked " << this->getClassName() << "" << endl;
        }
    }

    void Refable::Hold() {
        refCounter->Hold();
    }

    int Refable::Release() {
        return refCounter->Release();
    }

    Refable::~Refable() {
        delete refCounter;
    }

    const char* Refable::getClassName() {
        return "DefaultRefable";
    }
}