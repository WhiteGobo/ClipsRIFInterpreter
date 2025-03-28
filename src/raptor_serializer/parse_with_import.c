#include "crifi_raptor.h"
#include "parse_with_import.h"


CRIFI_PARSE_RET crifi_parse(raptor_statement_handler assert_triple_handler,
					void *assert_triple_context,
					FILE *filehandle, const char *filepath,
					const char* syntax_uri,
					const char* base){

	if (syntax_uri == NULL || filehandle == NULL){
		return CRIFI_PARSE_INITERROR;
	}
	int err;
	raptor_uri *base_uri, *r_syntax_uri;
	raptor_parser* parser;
	raptor_world *world = raptor_new_world();
	if(world == NULL){
		return CRIFI_PARSE_INITERROR;
	}

	r_syntax_uri = raptor_new_uri(world, syntax_uri);
	if (r_syntax_uri == NULL){
		raptor_free_world(world);
		return CRIFI_PARSE_UNKNOWN;
	}
	parser = raptor_new_parser_for_content(world, r_syntax_uri,
						NULL, NULL, 0, NULL);
	//parser = raptor_new_parser(world, "turtle");
	if(parser == NULL){
		fprintf(stderr, "crifi_parse failed. Dont have parser for "
				"rdf in syntax: %s\n", syntax_uri);
		raptor_free_world(world);
		return CRIFI_PARSE_UNKNOWN;
	}
	base_uri = raptor_new_uri(world, base);
	if(base_uri == NULL){
		raptor_free_parser(parser);
		raptor_free_world(world);
		return CRIFI_PARSE_BASEERROR;
	}
	raptor_parser_set_statement_handler(parser,
			assert_triple_context, assert_triple_handler);

	err = raptor_parser_parse_file_stream(parser, filehandle, NULL, base_uri);
	//err = raptor_parser_parse_file_stream(parser, filehandle, filepath, base_uri);

	raptor_free_parser(parser);
	raptor_free_uri(base_uri);
	raptor_free_world(world);
	if (err != 0){
		return CRIFI_PARSE_PARSING_ERROR;
	}
	return CRIFI_PARSE_NOERROR;
	/*
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
	}*/
}
