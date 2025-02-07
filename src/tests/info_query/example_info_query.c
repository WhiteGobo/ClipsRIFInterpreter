/** \anchor example_info_query
 */
#include "example_info_query.h"
#include "info_query.h"

typedef enum {
	ErrorType,
	UriType,
	BNodeType,
	LiteralType
} ExampleTermType;

typedef struct exampleTermInfo_ {
	ExampleTermType type;
	union {
		char *uri;
		char *bnode_id;
		char *lexical;
		char *q;
	};
	union {
		char *datatype;
		char *lang;
		char *q2;
	};
} TermInfo;

static TermInfo print_valuetype(crifi_graph* graph, CLIPSValue val){
	TermInfo retval = {
		.type = ErrorType,
		.q = NULL,
		.q2 = NULL
	};
	if (clipsvalue_is_uri(graph, val)){
		retval.type = UriType;
		retval.uri = extract_uri(graph, val.header);
		printf("Found uri: <%s>\n", retval.uri);
	} else if (clipsvalue_is_literal(graph, val)){
		retval.lexical = extract_lexical(graph, val.header);
		retval.lang = extract_lang(graph, val.header);
		if (retval.lang == NULL){
			retval.datatype = extract_datatype(graph, val.header);
			printf("Found literal: \"%s\"^^<%s>\n",
					retval.lexical, retval.datatype);
		} else {
			printf("Found literal: \"%s\"@%s\n",
					retval.lexical, retval.lang);
		}
		retval.type = LiteralType;
	} else if (clipsvalue_is_bnode(graph, val)){
		retval.type = BNodeType;
		retval.bnode_id = extract_bnodeid(graph, val.header);
		printf("Found bnode: _:%s\n", retval.bnode_id);
	} else {
		printf("strange error\n");
	}
	return retval;
}

int example_info_query(crifi_graph* graph){
	CLIPSValue tmpValue;
	TermInfo term;
	int found_triples = 0;
	for(Fact *f = get_next_triple(graph, NULL);
			f != NULL;
			f = get_next_triple(graph, f))
	{
		found_triples++;

		GetFactSlot(f, TRIPLESLOTSUBJECT, &tmpValue);
		term = print_valuetype(graph, tmpValue);
		if (term.type == ErrorType) return -1;
		free(term.q);
		free(term.q2);

		GetFactSlot(f, TRIPLESLOTPREDICATE, &tmpValue);
		term = print_valuetype(graph, tmpValue);
		if (term.type == ErrorType) return -1;
		free(term.q);
		free(term.q2);

		GetFactSlot(f, TRIPLESLOTOBJECT, &tmpValue);
		term = print_valuetype(graph, tmpValue);
		if (term.type == ErrorType) return -1;
		free(term.q);
		free(term.q2);
	}
	return found_triples;
}
