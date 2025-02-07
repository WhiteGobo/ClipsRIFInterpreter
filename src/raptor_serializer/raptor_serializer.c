#include "raptor_serializer.h"
#include <stdio.h>
#include "info_query.h"

static const char *testinput ="\n"
"@prefix ex: <http://example.com/> .\n"
"ex:a ex:b ex:c .\n";

#define NS_ "http://example.com/"
enum {
	SAT_NOERROR,
	SAT_SUBJ,
	SAT_PRED,
	SAT_OBJ
};

static raptor_term* clipsvalue_to_raptorterm(raptor_world *world, crifi_graph* graph, CLIPSValue val)
{
	raptor_term *retval;
	char *uri, *lexical, *lang, *datatype, *bnodeid;
	raptor_uri *dt_uri;
	if (clipsvalue_is_uri(graph, val)){
		uri = extract_uri(graph, val.header);
		retval = raptor_new_term_from_uri_string(world, uri);
		free(uri);
		return retval;
	} else if (clipsvalue_is_literal(graph, val)){
		lexical = extract_lexical(graph, val.header);
		lang = extract_lang(graph, val.header);
		if (lang != NULL){
			retval = raptor_new_term_from_literal(world, lexical,
								NULL, lang);
			free(lang);
		} else {
			datatype = extract_datatype(graph, val.header);
			if (datatype == NULL){
				free(lexical);
				return NULL;
			}
			dt_uri = raptor_new_uri(world, datatype);
			retval = raptor_new_term_from_literal(world, lexical,
								dt_uri, NULL);
			raptor_free_uri(dt_uri);
			free(datatype);
		}
		free(lexical);
		return retval;
	} else if (clipsvalue_is_bnode(graph, val)){
		bnodeid = extract_bnodeid(graph, val.header);
		retval = raptor_new_term_from_blank(world, bnodeid);
		free(bnodeid);
		return retval;
	}
	return NULL;
}

static int serialize_all_triples(raptor_world *world, crifi_graph* graph, raptor_serializer *my_serializer){
	if (world == NULL || my_serializer == NULL){
		return -2;
	}
	CLIPSValue tmpValue;
	raptor_statement *triple;
	raptor_term *subj, *pred, *obj;
	for(Fact *f = get_next_triple(graph, NULL);
			f != NULL;
			f = get_next_triple(graph, f))
	{
		GetFactSlot(f, TRIPLESLOTSUBJECT, &tmpValue);
		subj = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (subj == NULL) return SAT_SUBJ;

		GetFactSlot(f, TRIPLESLOTPREDICATE, &tmpValue);
		pred = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (pred == NULL){
			raptor_free_term(subj);
			return SAT_PRED;
		}

		GetFactSlot(f, TRIPLESLOTOBJECT, &tmpValue);
		obj = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (obj == NULL){
			raptor_free_term(subj);
			raptor_free_term(pred);
			return SAT_OBJ;
		}
		triple = raptor_new_statement_from_nodes(world,
							subj, pred, obj, NULL);

		raptor_serializer_serialize_statement(my_serializer, triple);
		raptor_free_statement(triple);
	}
	return SAT_NOERROR;
}

CRIFI_SERIALIZE_RET crifi_serialize_all_triples(crifi_graph* graph,
					FILE *filehandle,
					const char* format, const char* base)
{
	if (format == NULL) return CRIFI_SERIALIZE_MISSING_FORMAT;
	if (base == NULL) return CRIFI_SERIALIZE_MISSING_BASE;
	int err;
	raptor_serializer* rdf_serializer;
	raptor_statement* triple;
	raptor_world *world = raptor_new_world();
	raptor_uri *uri= raptor_new_uri(world, base);
	rdf_serializer = raptor_new_serializer(world, format);

	raptor_serializer_start_to_file_handle(rdf_serializer, uri, filehandle);
	err = serialize_all_triples(world, graph, rdf_serializer);
	if (err!=SAT_NOERROR) return CRIFI_SERIALIZE_TERM;
	raptor_serializer_serialize_end(rdf_serializer);

	raptor_free_serializer(rdf_serializer);

	raptor_free_uri(uri);
	raptor_free_world(world);
	return CRIFI_SERIALIZE_NOERROR;
}

/*
char *toot2(){
	char *ret;
	raptor_world *world = NULL;
	raptor_parser* rdf_parser = NULL;
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
	FILE *qq;

	qq = fmemopen(testinput, strlen(testinput), "r");

	world = raptor_new_world();
	rdf_parser = raptor_new_parser(world, "turtle");
	//rdf_parser = raptor_new_parser(world, "ntriples");
	if (rdf_parser == NULL){
		return NULL;
	}
	//raptor_parser_set_statement_handler(rdf_parser, NULL, print_triple);

	//base_uriuri_string = raptor_uri_filename_to_uri_string(argv[1]);
	base_uri = raptor_new_uri(world, "http://example.com/testbaseuri");

	printf("qwertz\n");
	raptor_parser_parse_file_stream(rdf_parser, qq, "nofile", base_uri);
	fclose(qq);
	raptor_free_parser(rdf_parser);
	raptor_free_uri(base_uri);

	//ret = myserializing(world);

	raptor_free_world(world);
	return NULL;
}
*/
