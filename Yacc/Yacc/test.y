%token i

%left '+' '*'

%start E
%%

E
    : E '+' E
    | E '*' E
    | '(' E ')'
    | i
    ;

T
    : T '*' F
    | F
    ;

F
    : '(' E ')'
    | i
    ;

%%
#include <stdio.h>