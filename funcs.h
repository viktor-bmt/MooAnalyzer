#ifndef _FUNCS_H_
#define _FUNCS_H_

#include "allocatedMemory.h"

void initMem(allocatedMemory* pMem); 

void stepback(allocatedMemory* pMem);
void stepforward(allocatedMemory* pMem);
void increment(allocatedMemory* pMem);
void decrement(allocatedMemory* pMem);
void printValue(const allocatedMemory* pMem);
void readValue(allocatedMemory* pMem);
void clear(allocatedMemory* pMem);

void printMemoryPos(const allocatedMemory* pMem);
void showAllocatedMemory(const allocatedMemory* pMem);
 
#endif
