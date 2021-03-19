
#ifndef __UNINITIALIZED_MEMORY_STACK_H__
#define __UNINITIALIZED_MEMORY_STACK_H__

#include "Common.h"



typedef struct _UNINITIALIZED_MEMORY_STACK
{
    unsigned long Value;
    FunctionPointer Callback;
    unsigned long Buffer[58];
} UNINITIALIZED_MEMORY_STACK, *PUNINITIALIZED_MEMORY_STACK;


void
UninitializedMemoryStackObjectCallback(void);

int trigger_uninitialized_memory_stack(void *user_buffer, size_t size);

#endif
