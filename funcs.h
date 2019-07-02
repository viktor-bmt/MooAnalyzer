#ifndef _FUNCS_H_
#define _FUNCS_H_

#include "allocatedMemory.h"
#include "register.h"

void initMem(allocatedMemory* pMem); 
void initReg(reg* pReg);

void stepback(allocatedMemory* pMem);
void stepforward(allocatedMemory* pMem);
void increment(allocatedMemory* pMem);
void decrement(allocatedMemory* pMem);
void printValue(const allocatedMemory* pMem);
void readValue(allocatedMemory* pMem);
void clear(allocatedMemory* pMem);
void executeInstruction(allocatedMemory* pMem);
void printorread(allocatedMemory* pMem);
void registerOper(allocatedMemory* pMem, reg* pReg);

void printMemoryPos(const allocatedMemory* pMem);
void showAllocatedMemory(const allocatedMemory* pMem);
 
#endif
