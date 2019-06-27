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
        |   STEPBACK      {stepback(&mem); printMemoryPos(&mem);}
        |   STEPFORWARD   {stepforward(&mem); printMemoryPos(&mem);}
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

#include "funcs.h"
#include "allocatedMemory.h"

int main()
{
  initMem(&mem);

  int returnCode = yyparse();

  free(mem.m_ptr);
  return returnCode;
}

void yyerror(char* s)
{
  fprintf(stderr, "%s \n", s);
}
