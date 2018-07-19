#pragma once

//
// Created by connor on 7/13/18.
//

#include <Sova/Graphics/Container.h>
#include <Modules/Core/Containers/Set.h>

namespace Sova
{
    class InternalDestructionManager
    {
    public:
        void QueueForDestruction(Container* container);
        void FinalizeDestruction();
    private:
        Oryol::Set<Container*> destructionQueue = Oryol::Set<Container*>();
    };
}
