#pragma once

//
// Created by connor on 7/9/18.
//
#include <Sova/References/Refable.h>

namespace Sova
{
    template<class T>
    class ListNode : public Refable
    {

    public:

        explicit ListNode(Ref<T> item)
        {
            this->item = item;
        }

        virtual const char* getClassName() { return "ListNode"; }

        Ref<T> item = NullRef<T>();
        Ref<ListNode<T>> next = NullRef<ListNode<T>>();
    };

    template<class T>
    class ListIterator : public Refable
    {
    public:

        explicit ListIterator(Ref<ListNode<T>> headNode)
        {
            this->currentNode = headNode;
        }

        virtual const char* getClassName() { return "ListIterator"; }

        Ref<T> Get()
        {
            return currentNode->item;
        }

        void Next()
        {
            this->currentNode = this->currentNode->next;
        }

        bool Valid()
        {
            return (this->currentNode != nullptr);
        }

    private:

        Ref<ListNode<T>> currentNode = NullRef<ListNode<T>>();
    };

    template<class T>
    class List : public Refable
    {
    public:

        List() = default;
        virtual const char* getClassName() { return "List"; }

        void Add(Ref<T> item)
        {
            Ref<ListNode<T>> newNode = NewRef<ListNode<T>>(item);

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
                size = 1;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
                size += 1;
            }
        }

        void Remove(Ref<T> removeItem)
        {
            if (head->item == removeItem)
            {
                if (head->next == nullptr)
                {
                    //there's only 1 node in this list
                    head = nullptr;
                    tail = nullptr;
                    size = 0;
                    return;
                }

                auto headNext = head->next; //important that this is executed before the next line (idk why yet :/)
                head = headNext;
                size -= 1;
                return;
            }

            auto previous = head;
            while (previous->next != nullptr && previous->next->item != removeItem)
                previous = previous->next;

            if (previous->next == nullptr)
            {
                // node is not in linked list
                return;
            }

            //cut item out of the linked list
            auto nextNext = previous->next->next; //important that this is executed before the next line (idk why yet :/)
            previous->next = nextNext;
            size -= 1;
        }

        int Size() const
        {
            return size;
        }

        Ref<ListIterator<T>> GetIterator()
        {
            return NewRef<ListIterator<T>>(head);
        }

    private:

        Ref<ListNode<T>> head = NullRef<ListNode<T>>();
        Ref<ListNode<T>> tail = NullRef<ListNode<T>>();
        int size = 0;
    };
}