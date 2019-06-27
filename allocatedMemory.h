#ifndef _ALLOCATEDMEMORY_H_
#define _ALLOCATEDMEMORY_H_

struct allocatedMemory
{
  int* m_ptr;
  int m_size;
  int m_capacity;
  int m_pos;
} typedef allocatedMemory;

#endif
