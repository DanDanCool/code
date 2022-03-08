#pragma once

#include <stdlib.h>

template<typename T>
struct Stack
{
    using Type = T;

    Type* Memory;
    size_t Size;
    size_t Index;

    Stack()
        : Memory(nullptr)
        , Size(0)
        , Index(0)
    {

    }

    void Init(size_t count)
    {
        Size = count;
        Memory = (Type*)malloc(sizeof(Type) * count);
        memset(Memory, 0, sizeof(Type) * count);
    }

    void Shutdown()
    {
        free(Memory);
        Memory = nullptr;
        Size = 0;
        Index = 0;
    }

    void Push(const Type& val)
    {
        Memory[Index] = val;
        Index++;
    }

    Type Pop(const Type& val)
    {
        return Memory[--Index];
    }

    Type& Peek()
    {
        return Memory[Index - 1];
    }
}
