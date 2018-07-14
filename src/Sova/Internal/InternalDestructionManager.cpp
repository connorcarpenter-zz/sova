//
// Created by connor on 7/13/18.
//

#include "InternalDestructionManager.h"

namespace Sova
{

    void InternalDestructionManager::QueueForDestruction(Container* container) {
        if(!destructionQueue.Contains(container))
            destructionQueue.Add(container);
    }

    void InternalDestructionManager::FinalizeDestruction() {
        for (auto container : destructionQueue){
            container->SetParent(nullptr);
        }

        destructionQueue.Clear();
    }
}