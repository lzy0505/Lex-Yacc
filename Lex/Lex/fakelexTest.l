%{
#include <stdio.h>
#include "y.tab.h"

void count(void);
%}


D			[0-9]
L			[a-z]

%%

{D}{L}{L}	{
			count();
			return (DLL);
			}
{D}{D}{L}	{
			return(DDL);
			}
{L}{D}{D}				{
			count();
			return(LDD);
			}


%%

int yywrap()
{
return 1; /* tell scanner no further files need to be processed */
}

