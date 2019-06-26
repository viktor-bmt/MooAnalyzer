%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char* s);
int yylex();
void stepback();
void stepforward();

struct allocatedMemory
{
  int* m_ptr;
  int m_size;
  int m_capacity;
  int m_pos;
} typedef allocatedMemory;

allocatedMemory allocMem;

%}

%start line

%token ENDWHILE
%token STEPBACK
%token STEPFORWARD
%token EXECUTE
%token PRINTORREAD
%token DECREMENT
%token INCREMENT
%token WHILE
%token CLEAR
%token REGISTER
%token PRINT
%token READ

%%

line    :   line command        {;}
        |   command             {;}

command :   ENDWHILE      ;
        |   STEPBACK      {stepback(); printf("Step Back\nCurrent Pointer Pos: %p\n",allocMem.m_ptr+allocMem.m_pos);}
        |   STEPFORWARD   {stepforward();printf("Step Forward\nCurrent Pointer Pos: %p\n",allocMem.m_ptr+allocMem.m_pos);}
        |   EXECUTE       ;
        |   PRINTORREAD   ; 
        |   DECREMENT     ;
        |   INCREMENT     ;
        |   WHILE         ;
        |   CLEAR         ;
        |   REGISTER      ;
        |   PRINT         ;
        |   READ          ;
 
        ;

%%

void stepback() {
  if(allocMem.m_pos > 0)
    --allocMem.m_pos;
}

void stepforward() {
  int pos = allocMem.m_pos;
  int capacity = allocMem.m_capacity;
  int size = allocMem.m_size;
  int* ptr = allocMem.m_ptr;

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

  allocMem.m_ptr = ptr;
  allocMem.m_pos = pos;
  allocMem.m_capacity = capacity;
}

int main()
{
  allocMem.m_size = allocMem.m_capacity = 1;
  allocMem.m_ptr = (int*)malloc(sizeof(int));
  allocMem.m_pos = 0;

  printf("Initial Memory Position: %p\n", allocMem.m_ptr);

  int returnCode = yyparse();
  free(allocMem.m_ptr);
  return returnCode;
}

void yyerror(char* s)
{
  fprintf(stderr, "%s \n", s);
}
