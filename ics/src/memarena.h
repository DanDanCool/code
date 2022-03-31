#pragma once

#include <stdint.h>

struct Handle
{
    uint32_t Index;

    Handle();

    Handle& operator=(uint32_t handle);

    Handle& operator+=(const Handle& handle);
    Handle& operator+=(uint32_t handle);
    Handle& operator-=(const Handle& handle);
    Handle& operator-=(uint32_t handle);

    operator bool();
};

Handle operator+(const Handle& h1, const Handle& h2);
Handle operator+(uint32_t h1, const Handle& h2);
Handle operator+(const Handle& h1, uint32_t h2);

Handle operator-(const Handle& h1, const Handle& h2);
Handle operator-(uint32_t h1, const Handle& h2);
Handle operator-(const Handle& h1, uint32_t h2);

struct Arena
{
    size_t BlockSz;
    size_t Count;
    size_t* FreeList;
    uint8_t* Data;

    Arena();

    void Init(size_t blocksz, size_t count);
    void Shutdown();

    void Resize(size_t count);

    void* Alloc();
    void Alloc(Handle& handle);
    void Free(void* mem);
    void Free(Handle handle);

    uint8_t* operator[](Handle handle);
};
