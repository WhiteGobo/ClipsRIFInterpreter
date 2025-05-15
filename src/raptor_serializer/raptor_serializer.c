#include "raptor_serializer.h"
#include <stdio.h>
#include "info_query.h"
#include "crifi_raptor_interface.h"
#include "ffi_constants.h"
#include "crifi_lists.h"

static const char *testinput ="\n"
"@prefix ex: <http://example.com/> .\n"
"ex:a ex:b ex:c .\n";

#define NS_ "http://example.com/"
enum {
	SAT_NOERROR,
	SAT_SUBJ,
	SAT_PRED,
	SAT_OBJ,
	SAT_LISTITEMS,
	SAT_LISTIDFAILED,
	SAT_LISTELEMENTFAILED,
	SAT_SERIALIZEFAILED
};

static void errprint_clips_value(CLIPSValue *val){
        switch (val->header->type) {
		case FLOAT_TYPE:
			fprintf(stderr, "%f\n", val->floatValue->contents);
			break;
		case INTEGER_TYPE:
			fprintf(stderr, "%d\n", val->integerValue->contents);
			break;
		case STRING_TYPE:
			fprintf(stderr, "string: \"%s\"\n", val->lexemeValue->contents);
			break;
                case SYMBOL_TYPE:
			fprintf(stderr, "symbol: \"%s\"\n", val->lexemeValue->contents);
			break;
		case FACT_ADDRESS_TYPE:
			fprintf(stderr, "factaddress\n");
			break;
		default:
			fprintf(stderr, "errprint_clips_value failed\n");
	}
}

static bool serialize_triple(raptor_world *world, const raptor_term *subj, const raptor_term *pred, const raptor_term *obj, raptor_serializer *my_serializer){
	int err;
	raptor_statement *triple = raptor_new_statement_from_nodes(world,
						subj, pred, obj, NULL);
	if (triple == NULL){
		return false;
	}
	err = raptor_serializer_serialize_statement(my_serializer, triple);
	// This would free all raptor_terms which is not ok
	//raptor_free_statement(triple);
	return (err == 0);
}

static int serialize_list(raptor_world *world, crifi_graph *graph, Fact *l, raptor_serializer *my_serializer){
	int err, length;
	bool success;
	raptor_term *first = raptor_new_term_from_uri_string(world,_RDF_first_);
	raptor_term *rest = raptor_new_term_from_uri_string(world, _RDF_rest_);
	raptor_term *nil = raptor_new_term_from_uri_string(world, _RDF_nil_);
	raptor_term *last = NULL;
	raptor_term *current = NULL;
	raptor_term *element = NULL;
	CLIPSValue l_val = {.factValue = l};
	CLIPSValue list_iterator_node = {.voidValue = VoidConstant(graph)};
	CLIPSValue *tmpval;// = {.voidValue = VoidConstant(graph)};
	Multifield *items;
	CLIPSValue clipsval_list = {.factValue = l};
	length = crifi_list_count(graph, &clipsval_list);
	if (length == 0){ //no further serializing needed
		return SAT_NOERROR;
	}
	items = retrieve_items(graph, l_val);
	if (items == NULL){
		return SAT_LISTITEMS;
	}
	
	for (int i = 0; i<length; i++){
		if (!crifi_list_as_identifier(graph, &l_val, i, &list_iterator_node)){
			return SAT_LISTIDFAILED;
		}
		current = clipsvalue_to_raptorterm(world, graph, list_iterator_node);
		if (current == NULL){
			return CRIFI_SERIALIZE_SCRIPT_OBJECT;
		}
		tmpval = items->contents + i;
		element = clipsvalue_to_raptorterm(world, graph, *tmpval);
		if (element == NULL){
			return SAT_LISTELEMENTFAILED;
		}
		if(!serialize_triple(world, current, first, element, my_serializer)){
			return SAT_SERIALIZEFAILED;
		}
		if (last != NULL){
			if(!serialize_triple(world, last, rest, current, my_serializer)){
				return SAT_SERIALIZEFAILED;
			}
			raptor_free_term(last);
		}
		last = current;
		current = NULL;
	}
	success = true;
	if (last != NULL){
		success = serialize_triple(world, last, rest, nil, my_serializer);
		raptor_free_term(last);
		last = NULL;
	}
	if (success){
		return SAT_NOERROR;
	} else {
		return SAT_SERIALIZEFAILED;
	}
}

static int serialize_all_triples(raptor_world *world, crifi_graph* graph, raptor_serializer *my_serializer){
	int err;
	bool success;
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
		if (subj == NULL){
			fprintf(stderr, "subject: ");
			errprint_clips_value(&tmpValue);
			return SAT_SUBJ;
		}

		GetFactSlot(f, TRIPLESLOTPREDICATE, &tmpValue);
		pred = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (pred == NULL){
			fprintf(stderr, "predicate: ");
			errprint_clips_value(&tmpValue);
			raptor_free_term(subj);
			return SAT_PRED;
		}

		GetFactSlot(f, TRIPLESLOTOBJECT, &tmpValue);
		obj = clipsvalue_to_raptorterm(world, graph, tmpValue);
		if (obj == NULL){
			fprintf(stderr, "object: ");
			errprint_clips_value(&tmpValue);
			raptor_free_term(subj);
			raptor_free_term(pred);
			return SAT_OBJ;
		}
		success = serialize_triple(world, subj, pred, obj, my_serializer);
		raptor_free_term(subj);
		raptor_free_term(pred);
		raptor_free_term(obj);
		if (!success){
			return SAT_SERIALIZEFAILED;
		}
	}
	for(Fact *l = get_next_list(graph, NULL);
			l != NULL;
			l = get_next_list(graph, l))
	{
		err = serialize_list(world, graph, l, my_serializer);
		if (err != SAT_NOERROR){
			fprintf(stderr, "convert list failed\n");
			return err;
		}
	}
	return SAT_NOERROR;
}

CRIFI_SERIALIZE_RET crifi_serialize_all_triples(crifi_graph* graph,
					FILE *filehandle,
					const char* format, const char* base)
{
	raptor_term *rif_ns, *clips_ns, *ex_ns, *xs_ns;
	if (format == NULL) return CRIFI_SERIALIZE_MISSING_FORMAT;
	if (base == NULL) return CRIFI_SERIALIZE_MISSING_BASE;
	int err;
	raptor_serializer* rdf_serializer;
	raptor_statement* triple;
	raptor_world *world = raptor_new_world();
	raptor_uri *uri= raptor_new_uri(world, base);
	rdf_serializer = raptor_new_serializer(world, format);
	rif_ns = raptor_new_term_from_uri_string(world, _RIF_);
	clips_ns = raptor_new_term_from_uri_string(world, "http://clips.script/");
	ex_ns = raptor_new_term_from_uri_string(world, "http://example.com/");
	xs_ns = raptor_new_term_from_uri_string(world, _XML_);
	raptor_serializer_set_namespace(rdf_serializer, rif_ns->value.uri, "rif");
	raptor_serializer_set_namespace(rdf_serializer, clips_ns->value.uri, "cs");
	raptor_serializer_set_namespace(rdf_serializer, ex_ns->value.uri, "ex");
	raptor_serializer_set_namespace(rdf_serializer, xs_ns->value.uri, "xs");


	raptor_serializer_start_to_file_handle(rdf_serializer, uri, filehandle);
	err = serialize_all_triples(world, graph, rdf_serializer);
	if (err!=SAT_NOERROR) return CRIFI_SERIALIZE_TERM;
	raptor_serializer_serialize_end(rdf_serializer);

	raptor_free_serializer(rdf_serializer);

	raptor_free_uri(uri);
	raptor_free_world(world);
	return CRIFI_SERIALIZE_NOERROR;
}

