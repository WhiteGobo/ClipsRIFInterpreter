#include "raptor_serializer.h"
#include <stdio.h>
#include "info_query.h"
#include "crifi_raptor_interface.h"

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

