%{
#include "funcs.h"
#include "allocatedMemory.h"
#include "mooanalyzer.tab.h"

void yyerror(char* s);
int yylex();
%}


%%

"moo"         {return ENDWHILE;}
"mOo"         {return STEPBACK;}
"moO"         {return STEPFORWARD;}
"mOO"         {return EXECUTE;}
"Moo"         {return PRINTORREAD;}
"MOo"         {return DECREMENT;}
"MoO"         {return INCREMENT;}
"MOO"         {return WHILE;}
"OOO"         {return CLEAR;}
"MMM"         {return REGISTER;}
"OOM"         {return PRINT;}
"oom"         {return READ;}

[ \t\n]       ;
.             {ECHO; yyerror("Error: unexpected character");}

%%

int yywrap()
{
  return 1;
}
