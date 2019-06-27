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

void increment(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  ++(ptr[pos]);
}

void decrement(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  --(ptr[pos]);
}

void printMemoryPos(const allocatedMemory* pMem) {
  const int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  printf("Current memory position: %p\n", ptr+pos);
}

void printValue(const allocatedMemory* pMem) {
  const int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  printf("Value in the current cell: %d\n", ptr[pos]);
}

void showAllocatedMemory(const allocatedMemory* pMem) {
  printf("\nMemory Allocation Scheme:\n");

  const int size = pMem->m_size;
  const int pos = pMem->m_pos;
  const int* ptr = pMem->m_ptr;

  for(int i=0; i<size; ++i)
    printf("|_%d_|", ptr[i]);

  printf("\n");

  for(int i=0; i<size; ++i)
    if(ptr[i]<0)
      printf("  -%d- ", i);
    else
      printf(" -%d- ", i);

  printf("\n");
}
