//
// Created by connor on 7/8/18.
//

#include "Container.h"
#include "Point.h"

namespace Sova
{
    Container::Container()
    {
        this->children = NewRef<List<Container>>();
    }

    void Container::AddChild(Ref<Container> container)
    {
        this->children->Add(container);

        container->SetParent(ThisRef<Container>());
    }

    void Container::RemoveChild(Ref<Container> container)
    {
        this->children->Remove(container);

        container->SetParent(NullRef<Container>());
    }

    void Container::OnUpdate(std::function<void()> updateFunction)
    {
        this->UpdateFunction = updateFunction;
    }

    void Container::UpdateChildren()
    {
        if (this->destroyed) return;

        for (auto iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            if (childContainer->UpdateFunction != nullptr)
                childContainer->UpdateFunction();
            childContainer->UpdateChildren();
        }
    }

    void Container::Draw(int xoffset, int yoffset)
    {
        if (this->destroyed) return;

        this->drawSelf(xoffset, yoffset);

        //Draw children
        for (auto iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->Draw(xoffset + this->position->x, yoffset + this->position->y);
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
        SetParent(NullRef<Container>());

        this->UpdateFunction = nullptr;

        this->destroyed = true;
    }
}