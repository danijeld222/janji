#pragma once

#include "Defines.h"

enum MemoryTag
{
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,
    MEMORY_TAG_MAX
};

COREAPI void InitializeMemoryStats();
COREAPI void ShutdownMemoryStats();

COREAPI void* CoreAllocate(u64 Size, MemoryTag Tag);
COREAPI void CoreFree(void* Block, u64 Size, MemoryTag Tag);
COREAPI void* CoreZeroMemory(void* Block, u64 Size);
COREAPI void* CoreCopyMemory(void* Destination, const void* Source, u64 Size);
COREAPI void* CoreSetMemory(void* Destination, i32 Value, u64 Size);

COREAPI char* GetMemoryUsage();