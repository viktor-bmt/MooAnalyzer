%{
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "allocatedMemory.h"

void yyerror(char* s);
int yylex();

allocatedMemory mem;

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
        |   STEPBACK      {stepback(&mem);    printf("Step Back\n");    printMemoryPos(&mem);}
        |   STEPFORWARD   {stepforward(&mem); printf("Step forward\n"); printMemoryPos(&mem);}
        |   EXECUTE       ;
        |   PRINTORREAD   ; 
        |   DECREMENT     {decrement(&mem); printf("Decrement\n"); printValue(&mem);} 
        |   INCREMENT     {increment(&mem); printf("Increment\n"); printValue(&mem);}
        |   WHILE         ;
        |   CLEAR         ;
        |   REGISTER      ;
        |   PRINT         ;
        |   READ          ;
 
        ;

%%

int main()
{
  initMem(&mem);

  int returnCode = yyparse();

  showAllocatedMemory(&mem);

  free(mem.m_ptr);
  return returnCode;
}

void yyerror(char* s)
{
  fprintf(stderr, "%s \n", s);
}
