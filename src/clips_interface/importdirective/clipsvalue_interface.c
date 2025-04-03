#include "clipsvalue_interface.h"

#include "interpretations.h"
#include "info_query.h"

int value_suffix_to_clipsvalue(ImportProcess *process,
		const char *value, const char *suffix, IMPORT_TERM_TYPE type,
		CLIPSValue *retval)
{
	int err = 0;
	size_t suffix_length;
	crifi_graph *graph = process->graph;
	BNodeLookup *bnode_lookup = process->bnode_lookup;
	if (value == NULL) return 1;
	if (suffix != NULL){
		suffix_length = strlen(suffix);
	} else {
		suffix_length = 0;
	}
	switch(type){
		case CRIFI_IMPORT_TERM_URI:
			err = uri_to_clipsvalue(graph,
						value, strlen(value),
						retval);
			return err;
		case CRIFI_IMPORT_TERM_BNODE:
			err = retrieve_blanknode(graph, value,
						bnode_lookup, retval);
			return err;
		case CRIFI_IMPORT_TERM_LANGLITERAL:
			err = value_and_lang_to_clipsvalue(graph,
						value, strlen(value),
						suffix, suffix_length,
						retval);
			return err;
		case CRIFI_IMPORT_TERM_TYPEDLITERAL:
			err = value_and_datatype_to_clipsvalue(graph,
						value, strlen(value),
						suffix, suffix_length,
						retval);
			return err;
		case CRIFI_IMPORT_TERM_UNKNOWN:
		default:
			break;
	}
	return 1;
}
