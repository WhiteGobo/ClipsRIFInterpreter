#include "raptor_serializer.h"
#include <stdio.h>

static const char *testinput ="\n"
"@prefix ex: <http://example.com/> .\n"
"ex:a ex:b ex:c .\n";

#define NS_ "http://example.com/"

char *toot(){
	raptor_world *world = raptor_new_world();
	int err;
	raptor_serializer* rdf_serializer;
	raptor_statement *triple;
	raptor_uri *uri = raptor_new_uri(world, "http://example.com/testbaseuri");
	rdf_serializer = raptor_new_serializer(world, "rdfxml-abbrev");

	raptor_serializer_start_to_file_handle(rdf_serializer, uri, stdout);
	//err = raptor_serializer_start_to_string(rdf_serializer, uri,
        //                           void **string_p,
        //                           size_t *length_p);
	//if (err != 0) return NULL;
	raptor_term *subj, *pred, *obj;
	subj = raptor_new_term_from_uri_string(world, NS_ "a");
	pred = raptor_new_term_from_uri_string(world, NS_ "b");
	obj = raptor_new_term_from_uri_string(world, NS_ "c");
	triple = raptor_new_statement_from_nodes(world, subj, pred, obj, NULL);
	raptor_serializer_serialize_statement(rdf_serializer, triple);
	raptor_serializer_serialize_end(rdf_serializer);

	raptor_free_serializer(rdf_serializer);

	raptor_free_uri(uri);
	raptor_free_world(world);
	//raptor_free_memory(uri_string);
	return NULL;
}

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
