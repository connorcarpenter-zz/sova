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