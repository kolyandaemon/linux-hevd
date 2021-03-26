
#pragma once

#ifndef __BUFFER_OVERFLOW_STACK_H__
#define __BUFFER_OVERFLOW_STACK_H__

#include "Common.h"



int trigger_buffer_overflow_stack(void *user_buffer, size_t size);

#endif  
