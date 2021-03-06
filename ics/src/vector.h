#pragma once

#include <stdlib.h>
#include <string.h>

template<typename T>
struct Vector
{
    using Type = T;

    Type* Data;
    size_t Size;
    size_t Index;

    Vector()
        : Data(nullptr)
        , Size(0)
        , Index(0)
    {}

    void Init(size_t count)
    {
        Data = (Type*)malloc(sizeof(Type) * count);
        memset(Data, 0, sizeof(Type) * count);
        Size = count;
    }

    void Add(const Type& val)
    {
        Data[Index] = val;
        Index++;
    }

    void Resize(size_t sz)
    {
        Data = (Type*)realloc(Data, sz * sizeof(Type));
        Size = sz;
    }
};
