%option noyywrap
%option header-file="pt.l.h"

%%
[[:digit:]]+	{ return 0; }
[[:alpha:]][[:alpha:]]?	{ return 1; }
[[:alpha:]]+	{ return 2; }

[ \t\n]	{ /* ignore whitespace */ }
<<EOF>>	{ return -1; }
%%
