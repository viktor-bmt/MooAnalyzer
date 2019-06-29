%{
#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include "allocatedMemory.h"

void yyerror(char* s);
int yylex();
extern FILE * yyin;

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
        |   STEPBACK      {printf("Step Back\n");     stepback(&mem);   }
        |   STEPFORWARD   {printf("Step forward\n");  stepforward(&mem);}
        |   EXECUTE       ;
        |   PRINTORREAD   ; 
        |   DECREMENT     {printf("Decrement\n"); decrement(&mem);} 
        |   INCREMENT     {printf("Increment\n"); increment(&mem);}
        |   WHILE         ;
        |   CLEAR         {printf("Clear\n"); clear(&mem);}
        |   REGISTER      ;
        |   PRINT         {printf("Print\n"); printValue(&mem); }
        |   READ          {printf("Read\n");  readValue(&mem);  }
 
        ;

%%

int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("Wrong number of arguments\nPlease, run the program as follows: ./mooanalyzer [filename]\n");
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if(!yyin) {
    printf("File %s does not exist\n", argv[1]);
    return 1;
  }
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
