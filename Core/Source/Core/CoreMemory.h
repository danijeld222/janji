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

COREAPI void* CoreAllocate(u64 size, MemoryTag tag);
COREAPI void CoreFree(void* block, u64 size, MemoryTag tag);
COREAPI void* CoreZeroMemory(void* block, u64 size);
COREAPI void* CoreCopyMemory(void* destination, const void* source, u64 size);
COREAPI void* CoreSetMemory(void* destination, i32 value, u64 size);

COREAPI char* GetMemoryUsage();