#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funcs.h"
#include "allocatedMemory.h"

// Initialization of memory structure: 1-element block, initial value is '0'
void initMem(allocatedMemory* pMem) {
  pMem->m_ptr = (int*)malloc(sizeof(int));
  pMem->m_size = pMem->m_capacity = 1;
  (pMem->m_ptr)[0] = 0;
  pMem->m_pos = 0;
}

// selects previous memory cell
// does nothing in case cell Nr.0 is the current one
void stepback(allocatedMemory* pMem) {
  if(pMem->m_pos > 0)
    --(pMem->m_pos);
}

// selects the next memory cell
void stepforward(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  int pos = pMem->m_pos;
  int size = pMem->m_size;
  int capacity = pMem->m_capacity;

  if(pos < (capacity-1))
    ++pos;
  // dynamically expands allocated memory
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

// increases the value in the current cell by 1
void increment(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  ++(ptr[pos]);
}

// decreases the value in the current cell by 1
void decrement(allocatedMemory* pMem) {
  int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  --(ptr[pos]);
}

// prints hex address of the current memory cell
void printMemoryPos(const allocatedMemory* pMem) {
  const int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  printf("Current memory position: %p\n", ptr+pos);
}

// prints the integer value in the current cell
void printValue(const allocatedMemory* pMem) {
  const int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  printf("Value in the current cell: %d\n", ptr[pos]);
}

// schematically shows allocated memory with values in each cell
// plus current position is highlighed with arrows: ">[num]<"
//
// Note: best visualization only for 1-digit positive values, but also
// applicable in othe cases
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

// Checks if the given string is a signed integer
// Note: used in readValue() - see below
const int isStringNumber(const char* str) {
  int flag = 1;

  // if empty string, return false
  if(!str)
    return 0;
  // if first symbol neither digit, nor sign, return false
  if(!isdigit(str[0]) & (str[0] != '+') & (str[0] != '-'))
    return 0;
  // if first and only symbol in string is a sign, return false
  if (((str[0] == '+') | (str[0] == '-')) & (strlen(str) == 1))
    return 0;

  // check the rest of the symbols in the string otherwise
  int i = 1;
  while(str[i])
    if(!isdigit(str[i++])) {
      flag = 0;
      break;
    }

  return flag;
}

// reads integer value from stdin and writes it to the current cell
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

// set the value in the current cell to '0'
void clear(allocatedMemory* pMem){
  int* ptr = pMem->m_ptr;
  const int pos = pMem->m_pos;

  ptr[pos] = 0;
}
