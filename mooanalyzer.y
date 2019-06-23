%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char* s);
int yylex();
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


line    :   line ENDWHILE      {printf("endwhile\n");}
        |   line STEPBACK      {printf("step back\n");}
        |   line STEPFORWARD   {printf("step forward\n");}
        |   line EXECUTE       {printf("execute\n");}
        |   line PRINTORREAD   {printf("print or read\n");}
        |   line DECREMENT     {printf("decrement\n");}
        |   line INCREMENT     {printf("increment\n");}
        |   line WHILE         {printf("while\n");}
        |   line CLEAR         {printf("clear\n");}
        |   line REGISTER      {printf("register\n");}
        |   line PRINT         {printf("print\n");}
        |   line READ          {printf("read\n");}
        |   ENDWHILE      {printf("endwhile\n");}
        |   STEPBACK      {printf("step back\n");}
        |   STEPFORWARD   {printf("step forward\n");}
        |   EXECUTE       {printf("execute\n");}
        |   PRINTORREAD   {printf("print or read\n");}
        |   DECREMENT     {printf("decrement\n");}
        |   INCREMENT     {printf("increment\n");}
        |   WHILE         {printf("while\n");}
        |   CLEAR         {printf("clear\n");}
        |   REGISTER      {printf("register\n");}
        |   PRINT         {printf("print\n");}
        |   READ          {printf("read\n");}
 
        ;

%%

int main()
{
  return yyparse();
}

void yyerror(char* s)
{
  fprintf(stderr, "%s\n", s);
}
