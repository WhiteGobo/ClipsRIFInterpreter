#include "crifi_raptor.h"
#include "info_query.h"
#include <clips.h>

typedef enum {
	CNTXT_NOERROR = 0,
	ASSERT_IN_GRAPH_SUBJECT_CONVERT,
	ASSERT_IN_GRAPH_PREDICATE_CONVERT,
	ASSERT_IN_GRAPH_OBJECT_CONVERT,
	ASSERT_IN_GRAPH_SUBJECT_ASSERT,
	ASSERT_IN_GRAPH_PREDICATE_ASSERT,
	ASSERT_IN_GRAPH_OBJECT_ASSERT,
	ASSERT_IN_GRAPH_UNKNOWN_ERROR
} ContextError;

typedef struct {
	ContextError err;
	crifi_graph *graph;
	raptor_parser *rdf_parser;
	raptor_avltree* bnode_lookup;
} ParsingContext;

typedef struct {
	raptor_term* id;
	CLIPSValue clipsnode;
} BNodeEntry;

static int compare_bnode_entry(const BNodeEntry* new, const BNodeEntry* old){
	if (new == NULL || old == NULL){
		return 0;
	}
	return raptor_term_compare(new->id, old->id);
}

static void free_bnode_entry(BNodeEntry* n){
	raptor_free_term(n->id);
	free(n);
}

static int new_bnode_entry(raptor_avltree* bnode_lookup, raptor_term* id, CLIPSValue* value){
	int err;
	if (bnode_lookup == NULL || id == NULL){
		return 1;
	}
	BNodeEntry *ret = malloc(sizeof(BNodeEntry));
	if (ret == NULL){
		return 1;
	}
	ret->id = raptor_term_copy(id);
	ret->clipsnode.value = value->value;

	err = raptor_avltree_add(bnode_lookup, ret);
	if (err != 0) free(ret);
	return err;
}

static int retrieve_blanknode(crifi_graph *graph, raptor_term *term, raptor_avltree* bnode_lookup, CLIPSValue* retval){
	int err;
	//BNodeEntry searcher = {.id = term};
	raptor_term *qq = term;//raptor_new_term_from_blank(term->world, "brubru");
	raptor_term_compare(qq, qq);
	BNodeEntry searcher = {.id = qq};
	BNodeEntry* existing;

	existing = (BNodeEntry*) raptor_avltree_search(bnode_lookup, &searcher);
	if (existing == NULL){
		err = new_blanknode(graph, retval);
		if (err != 0) return err;
		err = new_bnode_entry(bnode_lookup, term, retval);
		if (err != 0){
			return err;
		}
	} else {
		retval->value = existing->clipsnode.value;
		//retval->lexemeValue = CreateSymbol(graph, "<http://already.found>");
		//err = new_blanknode(graph, retval);
	}
	return 0;
}

static int term_to_clipsvalue(crifi_graph *graph, raptor_term *term, raptor_avltree* bnode_lookup, CLIPSValue* retval){
	int err;
	unsigned char* tmpuri;
	size_t tmplen = 0;
	raptor_uri *as_uri;
	raptor_term_literal_value as_literal;
	raptor_term_blank_value as_bnode;
	switch(term->type){
		case RAPTOR_TERM_TYPE_URI:
			as_uri = term->value.uri;
			tmpuri = raptor_uri_as_counted_string(as_uri, &tmplen);
			err = uri_to_clipsvalue(graph,
						tmpuri, strlen(tmpuri),
						retval);
			if (err != 0) return 1;
			break;
		case RAPTOR_TERM_TYPE_LITERAL:
			as_literal = term->value.literal;
			if (as_literal.language != NULL){
				err = value_and_lang_to_clipsvalue(graph,
						as_literal.string,
						as_literal.string_len,
						as_literal.language,
						as_literal.language_len,
						retval);
			} else {
				as_uri = as_literal.datatype;
				if (as_uri != NULL){
					tmpuri = raptor_uri_as_counted_string(
							as_uri, &tmplen);
					if (tmpuri == NULL) return 1;
				} else {
					tmpuri = NULL;
					tmplen = 0;
				}
				err = value_and_datatype_to_clipsvalue(graph,
						as_literal.string,
						strlen(as_literal.string),
						//as_literal.string_len,
						tmpuri, tmplen,
						retval);
			}
			if (err != 0) return 1;
			break;
		case RAPTOR_TERM_TYPE_BLANK:
			err = retrieve_blanknode(graph, term,
					bnode_lookup, retval);
			if (err != 0){
				return 1;
			}
			break;
		case RAPTOR_TERM_TYPE_UNKNOWN:
		default:
			return 2;
	}
	return 0;
}




static void assert_statements_in_graph(ParsingContext *cntxt,
					raptor_statement *statement)
{
	CrifiAssertTripleError err;
	CLIPSValue crifi_subj, crifi_pred, crifi_obj;
	err = term_to_clipsvalue(cntxt->graph, statement->subject,
					cntxt->bnode_lookup, &crifi_subj);
	if (err != 0) {
		raptor_parser_parse_abort(cntxt->rdf_parser);
		cntxt->err = ASSERT_IN_GRAPH_SUBJECT_CONVERT;
		return;
	}
	err = term_to_clipsvalue(cntxt->graph, statement->predicate,
					cntxt->bnode_lookup, &crifi_pred);
	if (err != 0) {
		raptor_parser_parse_abort(cntxt->rdf_parser);
		cntxt->err = ASSERT_IN_GRAPH_PREDICATE_CONVERT;
		return;
	}
	err = term_to_clipsvalue(cntxt->graph, statement->object,
					cntxt->bnode_lookup, &crifi_obj);
	if (err != 0) {
		raptor_parser_parse_abort(cntxt->rdf_parser);
		cntxt->err = ASSERT_IN_GRAPH_OBJECT_CONVERT;
		return;
	}

	err = assert_triple(cntxt->graph, &crifi_subj, &crifi_pred, &crifi_obj);
	switch (err){
		case CRIFI_ASSTR_NO_ERROR:
			break;
		case CRIFI_ASSTR_SUBJECT:
			cntxt->err = ASSERT_IN_GRAPH_SUBJECT_ASSERT;
			break;
		case CRIFI_ASSTR_PREDICATE:
			cntxt->err = ASSERT_IN_GRAPH_PREDICATE_ASSERT;
			break;
		case CRIFI_ASSTR_OBJECT:
			cntxt->err = ASSERT_IN_GRAPH_OBJECT_ASSERT;
			break;
		case CRIFI_ASSTR_UNKNOWN:
		default:
			cntxt->err = ASSERT_IN_GRAPH_UNKNOWN_ERROR;
			break;
	}
}

static ParsingContext init_context(crifi_graph* graph, raptor_parser* parser){
	ParsingContext cntxt = {
		.err = CNTXT_NOERROR,
		.graph = graph,
		.rdf_parser = parser,
	};
	cntxt.bnode_lookup = raptor_new_avltree(
			(raptor_data_compare_handler) compare_bnode_entry,
			(raptor_data_free_handler) free_bnode_entry,
			0);
	return cntxt;
}

CRIFI_PARSE_RET crifi_parse_to_triples(crifi_graph* graph,
					FILE *filehandle,
					const char* format, const char* base)
{
	int err;
	ParsingContext cntxt;
	raptor_uri *base_uri;
	raptor_parser* parser;
	raptor_world *world = raptor_new_world();
	if(world == NULL){
		return CRIFI_PARSE_INITERROR;
	}
	parser = raptor_new_parser(world, format);
	if(parser == NULL){
		raptor_free_world(world);
		return CRIFI_PARSE_INITERROR;
	}
	base_uri = raptor_new_uri(world, base);
	if(base_uri == NULL){
		raptor_free_parser(parser);
		raptor_free_world(world);
		return CRIFI_PARSE_BASEERROR;
	}
	cntxt = init_context(graph, parser);
	raptor_parser_set_statement_handler(
			parser, &cntxt,
			(raptor_statement_handler) assert_statements_in_graph);
	raptor_parser_parse_file_stream(parser, filehandle, "nofile", base_uri);

	raptor_free_avltree(cntxt.bnode_lookup);
	raptor_free_parser(parser);
	raptor_free_uri(base_uri);
	raptor_free_world(world);
	switch(cntxt.err){
		case CNTXT_NOERROR:
			return CRIFI_PARSE_NOERROR;
		case ASSERT_IN_GRAPH_SUBJECT_CONVERT:
		case ASSERT_IN_GRAPH_SUBJECT_ASSERT:
		case ASSERT_IN_GRAPH_PREDICATE_CONVERT:
		case ASSERT_IN_GRAPH_PREDICATE_ASSERT:
		case ASSERT_IN_GRAPH_OBJECT_CONVERT:
		case ASSERT_IN_GRAPH_OBJECT_ASSERT:
			return CRIFI_PARSE_TERM_CONVERT; break;
		default:
			return CRIFI_PARSE_UNKNOWN;
	}
}
