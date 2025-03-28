#include "direct_interpretation.h"


static int brubru(ImportProcess *process,
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
		case CRIFI_IMPORT_TERM_UNKOWN:
		default:
			break;
	}
	return 1;
}

CRIFI_IMPORT_ASSERT_RET assert_frame_direct(ImportProcess *process,
		const char *object, const char *object_suffix,
		IMPORT_TERM_TYPE object_type,
		const char *slotkey, const char *slotkey_suffix,
		IMPORT_TERM_TYPE slotkey_type,
		const char *slotvalue, const char *slotvalue_suffix,
		IMPORT_TERM_TYPE slotvalue_type)
{
	int err;
	CLIPSValue object_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotkey_cv = {.voidValue = VoidConstant(process->graph)};
	CLIPSValue slotvalue_cv = {.voidValue = VoidConstant(process->graph)};
	err = brubru(process, object, object_suffix, object_type, &object_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = brubru(process, slotkey, slotkey_suffix, slotkey_type, &slotkey_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = brubru(process, slotvalue, slotvalue_suffix, slotvalue_type, &slotvalue_cv);
	if (err != 0){
		return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	err = assert_triple(process->graph, &object_cv, &slotkey_cv, &slotvalue_cv);
	switch (err){
		case CRIFI_ASSTR_NO_ERROR:
			break;
		case CRIFI_ASSTR_SUBJECT:
		case CRIFI_ASSTR_PREDICATE:
		case CRIFI_ASSTR_OBJECT:
		case CRIFI_ASSTR_UNKNOWN:
		default:
			return CRIFI_IMPORT_ASSERT_UNHANDLED_ERROR;
	}
	return CRIFI_IMPORT_ASSERT_NOERROR;
}
