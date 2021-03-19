#pragma once

#ifndef __ARBITRARY_WRITE_H__
#define __ARBITRARY_WRITE_H__

#include "Common.h"


typedef struct _WRITE_WHAT_WHERE
{
    void *What;
    void *Where;
} WRITE_WHAT_WHERE, *PWRITE_WHAT_WHERE;



int trigger_arbitrary_write(PWRITE_WHAT_WHERE user_write_what_where);

#endif 
