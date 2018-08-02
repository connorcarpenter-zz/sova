

//
// Created by connor on 7/31/18.
//

#include <Sova/References/Refable.h>
#include "String.h"

namespace Sova {
    class Int : public Refable {
    public:
        Int(int i);
        Ref<Sova::String> ToString();
    private:
        int value;
    };
}