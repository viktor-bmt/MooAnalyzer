#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
      ptr[i] = 0;
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
    if(i==pos)
      printf(" >%d< ", i);
    else
      printf(" -%d- ", i);

  printf("\n");
}

const int isStringNumber(const char* str) {
  int flag = 1;

  if(!str)
    return 0;
  if(!isdigit(str[0]) & (str[0] != '+') & (str[0] != '-'))
    return 0;
  if (((str[0] == '+') | (str[0] == '-')) & (strlen(str) == 1))
    return 0;

  int i = 1;
  while(str[i])
    if(!isdigit(str[i++])) {
      flag = 0;
      break;
    }

  return flag;
}

void readValue(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  char* str = NULL;

  printf("Enter a number: ");
  scanf("%ms", &str);

  while(!isStringNumber(str)) {
    free(str);
    str = NULL;
    printf("The input must contain only digits. Try again: ");
    scanf("%ms", &str);
  }

  int num = atoi(str);
  free(str);

  ptr[pos] = num;
}
