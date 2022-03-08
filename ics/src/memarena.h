#pragma once

#include <stdint.h>

struct MemoryArena
{
    size_t BlockSize;
    size_t Count;
    uint64_t* FreeList;
    uint8_t* Mem;

    MemoryArena();

    void Init(size_t blocksz, size_t count);
    void Shutdown();

    void Resize(size_t count);

    void* Allocate();
    void Free(void* mem);
};
