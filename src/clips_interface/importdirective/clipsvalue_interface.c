#include "clipsvalue_interface.h"

#include "interpretations.h"
#include "info_query.h"
#include "node_retriever.h"

int value_suffix_to_clipsvalue(
		ImportProcess *process,
		ClipsvalueRetriever* node_retriever,
		const char *value, const char *suffix, IMPORT_TERM_TYPE type,
		CLIPSValue *retval)
{
	int err = 0;
	CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_RET err_special;
	size_t suffix_length;
	if (value == NULL) return 1;
	for (ClipsvalueRetriever* retriever = node_retriever;
			retriever != NULL;
			retriever = retriever->next)
	{
		err_special = retriever->function(process, node_retriever,
						value, suffix, type,
						retriever->context, retval);
		switch (err_special){
			case CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_NOTFOUND:
				break;
			case CRIFI_IMPORT_CLIPSVALUE_RETRIEVE_SUCCESS:
				return 0;
			default:
				return 1;
		}
	}
	if (suffix != NULL){
		suffix_length = strlen(suffix);
	} else {
		suffix_length = 0;
	}
	switch(type){
		case CRIFI_IMPORT_TERM_URI:
			err = uri_to_clipsvalue(process->graph,
						value, strlen(value),
						retval);
			return err;
		//case CRIFI_IMPORT_TERM_BNODE:
		//	err = retrieve_blanknode(graph, value,
		//				bnode_lookup, retval);
		//	return err;
		case CRIFI_IMPORT_TERM_LANGLITERAL:
			err = value_and_lang_to_clipsvalue(process->graph,
						value, strlen(value),
						suffix, suffix_length,
						retval);
			return err;
		case CRIFI_IMPORT_TERM_TYPEDLITERAL:
			err = value_and_datatype_to_clipsvalue(process->graph,
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
