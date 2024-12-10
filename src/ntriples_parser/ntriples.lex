%{
#include <stdio.h>
#include "ntriples.yacc.h"
%}
%%
_:[a-zA-Z][a-zA-Z0-9]* {
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return BNODE;
		}
\"[^"]*\"       {
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return LITERAL;
		}
\'[^'"]*\'      {        
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return LITERAL;
		}
\"[^"]*\"@[a-zA-Z-]+    {
		yylval.string=malloc(yyleng+1); 
		sprintf(yylval.string,"%s",yytext);
		return LITERAL;
		}
\'[^'"]*\'@[a-zA-Z-]+   {
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return LITERAL;
		}
\<[a-zA-Z0-9:\/.#\-]+\> {
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return URIREF;
		}
[.]                     return EOT;
\^\^                    return LITERALTYPING;
\n                      /* ignore end of line */;
[ \t]+                  /* ignore whitespace */;
%%
