#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "allocatedMemory.h"

void initMem(allocatedMemory* pMem) {
  pMem->m_ptr = (int*)malloc(sizeof(int));
  pMem->m_size = pMem->m_capacity = 1;
  (pMem->m_ptr)[0] = 0;
  pMem->m_pos = 0;
}

void stepback(allocatedMemory* pMem) {
  if(pMem->m_pos > 0)
    --(pMem->m_pos);
}

void stepforward(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  int pos = pMem->m_pos;
  int size = pMem->m_size;
  int capacity = pMem->m_capacity;

  if(pos < (capacity-1))
    ++pos;
  else {
    capacity *= 2;
    ptr = realloc(ptr, capacity*sizeof(int));
    for(int i=size; i<capacity; ++i)
      *ptr = 0;
    ++pos;
  }
  if(pos == size)
    ++size;

  pMem->m_ptr = ptr;
  pMem->m_pos = pos;
  pMem->m_size = size;
  pMem->m_capacity = capacity;
}

void printMemoryPos(allocatedMemory* pMem) {
  printf("Current memory position: %p\n", (pMem->m_ptr)+(pMem->m_pos));
}
