//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/OryolApp.h>
#include "Container.h"
#include "Sova/Math/Point.h"

namespace Sova
{
    Container::Container()
    {
        this->children = New<List<Container>>();
    }

    void Container::AddChild(Ref<Container> container)
    {
        this->children->Add(container);

        container->SetParent(ThisRef<Container>());
    }

    void Container::RemoveChild(Ref<Container> container)
    {
        this->children->Remove(container);

        container->SetParent(nullptr);
    }

    void Container::OnUpdate(std::function<void()> updateFunction)
    {
        this->UpdateFunction = updateFunction;
    }

    void Container::Update(){
        if (this->UpdateFunction != nullptr)
            this->UpdateFunction();
    }

    void Container::UpdateChildren()
    {
        if (this->destroyed) return;

        for (auto iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->Update();
            childContainer->UpdateChildren();
        }
    }

    void Container::Draw(Ref<Camera> camera, int xoffset, int yoffset)
    {
        if (this->destroyed) return;

        this->drawSelf(camera, xoffset, yoffset);

        //Draw children
        for (auto iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->Draw(camera, xoffset + this->position->x - this->anchor->x, yoffset + this->position->y - this->anchor->y);
        }
    }

    void Container::SetParent(std::nullptr_t)
    {
        auto oldParent = this->parent;
        this->parent = nullptr;

        if (oldParent != nullptr)
        {
            oldParent->RemoveChild(ThisRef<Container>());
        }
    }

    void Container::SetParent(Ref<Container> newParent)
    {
        auto oldParent = this->parent;
        this->parent = newParent;

        if (oldParent != nullptr)
        {
            oldParent->RemoveChild(ThisRef<Container>());
        }
    }

    void Container::Destroy()
    {
        OryolApp::getOryolApp()->destructionManager.QueueForDestruction(this);
        this->UpdateFunction = nullptr;
        this->destroyed = true;
    }
}