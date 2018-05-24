%token c d

%start S
%%

S
    : C C
    ;

C
    : c C
    | d
    ;

%%
#include <stdio.h>