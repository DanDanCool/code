#pragma once

#include <stdlib.h>
#include <string.h>

template<typename T>
struct Vector
{
    using Type = T;

    Type* Memory;
    size_t Size;
    size_t Index;

    Vector()
        : Memory(nullptr)
        , Size(0)
        , Index(0)
    {}

    void Init(size_t count)
    {
        Memory = (Type*)malloc(sizeof(Type) * count);
        memset(Memory, 0, sizeof(Type) * count);
        Size = count;
    }

    void Add(const Type& val)
    {
        Memory[Index] = val;
        Index++;
    }
};
