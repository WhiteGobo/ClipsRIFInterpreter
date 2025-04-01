#include "crifi_import.h"
#include "import_from_file.h"
#include "crifi_raptor.h"
#include <raptor.h>

typedef enum {
	CNTXT_NOERROR = 0,
	CNTXT_UNKNOWN_ERROR
} ContextError;


typedef struct myContext{
	crifi_graph *graph;
	ImportProcess *process;
	ContextError err;
} MyContext;

struct term_info {
	const char *value;
	const char *suffix;
	IMPORT_TERM_TYPE type;
};

static struct term_info extract_term_info(raptor_term *term){
	struct term_info ret = {.value = NULL, .suffix = NULL, .type = CRIFI_IMPORT_TERM_UNKOWN};
	size_t tmplen = 0;
	raptor_term_literal_value as_literal;
	raptor_term_blank_value as_bnode;
	switch(term->type){
		case RAPTOR_TERM_TYPE_URI:
			ret.value = raptor_uri_as_counted_string(term->value.uri, NULL);
			ret.type = CRIFI_IMPORT_TERM_URI;
			break;
		case RAPTOR_TERM_TYPE_LITERAL:
			as_literal = term->value.literal;
			ret.value = as_literal.string;
			if (as_literal.language != NULL){
				ret.suffix = as_literal.language;
				ret.type = CRIFI_IMPORT_TERM_LANGLITERAL;
			} else if (as_literal.datatype != NULL) {
				ret.suffix = raptor_uri_as_counted_string(
							as_literal.datatype,
							&tmplen);
				if (ret.suffix == NULL){
					ret.value = NULL;
				}
				ret.type = CRIFI_IMPORT_TERM_TYPEDLITERAL;
			}
			break;
		case RAPTOR_TERM_TYPE_BLANK:
			as_bnode = term->value.blank;
			ret.value = as_bnode.string;
			ret.type = CRIFI_IMPORT_TERM_BNODE;
			break;
		case RAPTOR_TERM_TYPE_UNKNOWN:
		default:
			break;
	}
	return ret;
}

static void my_assert_triple_handler(
		MyContext *cntxt,
		raptor_statement *statement)
{
	CRIFI_IMPORT_ASSERT_RET err;
	IMPORT_TERM_TYPE object_type;
	IMPORT_TERM_TYPE slotkey_type;
	IMPORT_TERM_TYPE slotvalue_type;
	const char *object = NULL;
	const char *object_suffix = NULL;
	const char *slotkey = NULL;
	const char *slotkey_suffix = NULL;
	const char *slotvalue = NULL;
	const char *slotvalue_suffix = NULL;
	struct term_info tmpterminfo = {.value = NULL, .suffix = NULL,
					.type = CRIFI_IMPORT_TERM_UNKOWN};

	tmpterminfo = extract_term_info(statement->subject);
	object = tmpterminfo.value;
	object_suffix = tmpterminfo.suffix;
	object_type = tmpterminfo.type;

	tmpterminfo = extract_term_info(statement->predicate);
	slotkey = tmpterminfo.value;
	slotkey_suffix = tmpterminfo.suffix;
	slotkey_type = tmpterminfo.type;

	tmpterminfo = extract_term_info(statement->object);
	slotvalue = tmpterminfo.value;
	slotvalue_suffix = tmpterminfo.suffix;
	slotvalue_type = tmpterminfo.type;

	if (object != NULL && slotkey != NULL && slotvalue != NULL){
		err = assert_frame(cntxt->process,
			object, object_suffix, object_type,
			slotkey, slotkey_suffix, slotkey_type,
			slotvalue, slotvalue_suffix, slotvalue_type);
		switch (err){
			case CRIFI_IMPORT_ASSERT_NOERROR:
				break;
			case CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR:
			default:
				cntxt->err = CNTXT_UNKNOWN_ERROR;
		}
	} else {
		cntxt->err = CNTXT_UNKNOWN_ERROR;
	}
}

RET_CRIFI_IMPORT import_data_from_file(crifi_graph *graph,
		FILE *inputfile, const char *filename,
		ImportProcess *process, const char *syntax_uri){
	int err = 0;
	MyContext cntxt = {.graph = graph, .err=CNTXT_NOERROR, .process=process};
	CLIPSValue inputinterpretation = {.voidValue = VoidConstant(graph)};
	//`https://www.w3.org/ns/formats/`_

	CRIFI_PARSE_RET parse_err = crifi_parse(
			(raptor_statement_handler) my_assert_triple_handler,
			&cntxt,
			inputfile, filename, syntax_uri,
			"http://example.com/somebase.ttl");

	switch(parse_err){
		case CRIFI_PARSE_NOERROR:
			break;
		case CRIFI_PARSE_PARSING_ERROR:
			fprintf(stderr, "parsing of \"%s\" failed with parser for syntax \"%s\".\n", filename, syntax_uri);
			return RET_CRIFI_IMPORT_UNKNOWN_ERROR;
		case CRIFI_PARSE_INITERROR:
		case CRIFI_PARSE_BASEERROR:
		case CRIFI_PARSE_TERM_CONVERT:
		case CRIFI_PARSE_UNKNOWN:
		default:
			return RET_CRIFI_IMPORT_UNKNOWN_ERROR;
	}
	switch(cntxt.err){
		case CNTXT_NOERROR:
			break;
		default:
			return RET_CRIFI_IMPORT_UNKNOWN_ERROR;
	}
	return RET_CRIFI_IMPORT_NOERROR;
}
