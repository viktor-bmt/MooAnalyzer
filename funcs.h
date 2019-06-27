#ifndef _FUNCS_H_
#define _FUNCS_H_

#include "allocatedMemory.h"

void initMem(allocatedMemory* pMem); 

void stepback(allocatedMemory* pMem);
void stepforward(allocatedMemory* pMem);
void printMemoryPos(allocatedMemory* pMem);
 
#endif
