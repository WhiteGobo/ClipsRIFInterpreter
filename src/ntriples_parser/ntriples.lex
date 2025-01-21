%{
#include <stdio.h>
#include "ntriples.yacc.h"
%}
%%
_:[a-zA-Z0-9_][a-zA-Z0-9_\x{00B7}\x{0300}\x{036F}\x{203F}\x{2040}.]*[a-zA-Z0-9_\x{00B7}\x{0300}\x{036F}\x{203F}\x{2040}] {
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
\"([^\\"]|(\\.))*\"@[a-zA-Z\-]+    {
		yylval.string=malloc(yyleng+1); 
		sprintf(yylval.string,"%s",yytext);
		return LITERAL;
		}
\'([^\\"']|(\\.))*\'@[a-zA-Z\-]+   {
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return LITERAL;
		}
\<[^<>\n\t\r\ ]+\> {
		yylval.string=malloc(yyleng+1);
		sprintf(yylval.string,"%s",yytext);
		return URIREF;
		}
[.]                     return EOT;
\^\^                    return LITERALTYPING;
\n                      /* ignore end of line */;
[ \t]+                  /* ignore whitespace */;
%%
