%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "ntriples.lex.h"
#include "ntriplesParser.h"
 
int yylex();
void yyerror(struct TriplesLinkedList **mylist, const char *str);

bool _parse_error;

%}

%parse-param {struct TriplesLinkedList **mylist}

%union{
	char *string;
}

%token <string> URIREF BNODE LITERAL LITERALTYPING
%token EOT
%type <string> node typedliteral

%union{
	struct TriplesLinkedList *triplelist;
}
%type <triplelist> triple triples

%destructor { free ($$); } <string>
%destructor { free ($$); } URIREF BNODE LITERAL LITERALTYPING
%destructor {} <triplelist>

%%
triples: /* empty */ {$$=NULL;}
        | triples triple
	{
		if ($1 == NULL){
			$$ = $2;
		} else {
			concatenate_triples($1, $2);
			$$ = $1;
		}
		*mylist = $$;
	}
        ;

triple:
        node node node EOT
        {
		struct TriplesLinkedList *new = append_triple(NULL, $1, $2, $3);
		free($1);
		free($2);
		free($3);
		$$ = new;
        }
        ;

typedliteral:
        LITERAL LITERALTYPING URIREF
	{
		size_t t = sizeof("^^");
		$$ = malloc(5000+(strlen($1) + t + strlen($3) + 2) * sizeof(char));
		sprintf($$, "%s^^%s", $1, $3);
		//printf("found typedliteral :%s\n", $$);
		free($1);
		free($3);
	}
        ;

node:
        URIREF | BNODE | LITERAL | typedliteral
        ;
%%

void yyerror(struct TriplesLinkedList **myerror, const char *str)
{
	_parse_error = true;
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 

NTRIPLESPARSER_INTERFACE RET_NTRIPLESPARSE ntriples_parse_f(
		struct clips_graph_container *graph,
		FILE *input, int debug){
	if (input == NULL) return NTP_INPUT_ERROR;
	CRI_RET_BUILDTRIPLE assert_err;
	yyset_debug(debug);
	yyin = input;
	_parse_error = false;
	struct TriplesLinkedList *retFacts;
	yyparse(&retFacts);
	yylex_destroy(); //?
	FOREACH_TRIPLE(retFacts, current){
		assert_err = assert_fact(*graph, current->subject, current->predicate, current->object, "");
		if (assert_err != CRI_RET_BUILDTRIPLE_NOERROR){
			free_linked_list(retFacts);
			return NTP_INTERNAL_ERROR;
		}
	}
	free_linked_list(retFacts);
	if (_parse_error){
		return NTP_PARSE_ERROR;
	} else {
		return NTP_NO_ERROR;
	}
}

NTRIPLESPARSER_INTERFACE RET_NTRIPLESPARSE ntriples_parse(
		struct clips_graph_container *graph,
		const char *input, size_t length, int debug){
	if (input == NULL) return NTP_INPUT_ERROR;
	FILE *in = fmemopen((void*) input, length, "r");
	RET_NTRIPLESPARSE ret = ntriples_parse_f(graph, in, debug);
	fclose(in);
	return ret;
}

NTRIPLESPARSER_INTERFACE struct TriplesLinkedList* ntriples_parse_triples_f(
		FILE *input, int debug){
	if (input == NULL){ return NULL;}
	yyset_debug(debug);
	struct TriplesLinkedList *retFacts;
	yyin = input;
	_parse_error = false;
	yyparse(&retFacts);
	yylex_destroy(); //?
	if (_parse_error){
		//printf("parse error\n");
		return NULL;
		//return NTP_PARSE_ERROR;
	} else {
		//printf("no parse error\n");
		return retFacts;
		//return NTP_NO_ERROR;
	}
}

/*
NTRIPLESPARSER_INTERFACE RET_NTRIPLESPARSE ntriples_parse_triples(
		struct TriplesLinkedList** triplepointer,
		const char *input, size_t length, int debug){
	yyin = fmemopen((void*) input, length, "r");
	return ntriples_parse_triples_f(triplepointer, yyin, debug);
}
*/
