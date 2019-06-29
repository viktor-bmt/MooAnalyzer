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
        |   STEPBACK      {printf("Step Back\n");     stepback(&mem);       showAllocatedMemory(&mem);}
        |   STEPFORWARD   {printf("Step forward\n");  stepforward(&mem);    showAllocatedMemory(&mem);}
        |   EXECUTE       ;
        |   PRINTORREAD   ; 
        |   DECREMENT     {printf("Decrement\n"); decrement(&mem);  printValue(&mem); showAllocatedMemory(&mem);} 
        |   INCREMENT     {printf("Increment\n"); increment(&mem);  printValue(&mem); showAllocatedMemory(&mem);}
        |   WHILE         ;
        |   CLEAR         ;
        |   REGISTER      ;
        |   PRINT         {printf("Print\n"); printValue(&mem);}
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
