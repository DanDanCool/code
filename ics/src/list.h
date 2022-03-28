#pragma once

#include "memarena.h"

template<typename T>
struct List
{
    using Type = T;

    struct Node
    {
        Node* Next;
        Type Val;
    };

    Node* First;
    Node* Last;
    Arena Memory;

    List()
        : Memory()
        , First(nullptr)
        , Last(nullptr)
    {

    }

    void Init(size_t count)
    {
        Memory.Init(sizeof(Node), count + 1);
        First = (Node*)Memory.Mem;
        Last = (Node*)Memory.Alloc();
    }

    void Shutdown()
    {
        Memory.Shutdown();
        First = nullptr;
        Last = nullptr;
    }

    void Add(const Type& val)
    {
        Last->Val = val;
        Last->Next = (Node*)Memory.Allocate();
        Last = Last->Next;
    }

    void Resize(size_t count)
    {
        Memory.Resize(count + 1);
    }
};
